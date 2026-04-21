#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
    explicit Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

static void insertBST(unique_ptr<Node>& root, int v) {
    if (!root) {
        root = make_unique<Node>(v);
        return;
    }
    Node* cur = root.get();
    while (true) {
        if (v < cur->val) {
            if (cur->left) {
                cur = cur->left.get();
            } else {
                cur->left = make_unique<Node>(v);
                break;
            }
        } else if (v > cur->val) {
            if (cur->right) {
                cur = cur->right.get();
            } else {
                cur->right = make_unique<Node>(v);
                break;
            }
        } else {
            // Values are unique per statement; ignore duplicates defensively
            break;
        }
    }
}

static int kthLargest(const unique_ptr<Node>& root, int k) {
    int count = 0;
    int ans = -1;
    Node* cur = root.get();
    vector<Node*> st;
    st.reserve(16);
    while (cur || !st.empty()) {
        while (cur) {
            st.push_back(cur);
            cur = cur->right.get();
        }
        cur = st.back();
        st.pop_back();
        if (++count == k) {
            ans = cur->val;
            break;
        }
        cur = cur->left.get();
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> nums;
    nums.reserve(8);
    long long x;
    while (nums.size() < 8 && (cin >> x)) {
        nums.push_back(x);
    }
    if (nums.size() < 8) return 0;

    unique_ptr<Node> root;
    for (int i = 0; i < 7; ++i) {
        insertBST(root, static_cast<int>(nums[i]));
    }
    int cnt = static_cast<int>(nums[7]);
    int res = kthLargest(root, cnt);
    if (res != -1) cout << res;
    return 0;
}
