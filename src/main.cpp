#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v): val(v), left(nullptr), right(nullptr) {}
};

void insertBST(Node*& root, int v) {
    if (!root) {
        root = new Node(v);
        return;
    }
    Node* cur = root;
    while (true) {
        if (v < cur->val) {
            if (cur->left) cur = cur->left;
            else { cur->left = new Node(v); break; }
        } else if (v > cur->val) {
            if (cur->right) cur = cur->right;
            else { cur->right = new Node(v); break; }
        } else {
            break;
        }
    }
}

int kthLargest(Node* root, int k) {
    int count = 0;
    int ans = -1;
    Node* cur = root;
    vector<Node*> st; st.reserve(16);
    while (cur || !st.empty()) {
        while (cur) { st.push_back(cur); cur = cur->right; }
        cur = st.back(); st.pop_back();
        if (++count == k) { ans = cur->val; break; }
        cur = cur->left;
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
    Node* root = nullptr;
    for (int i = 0; i < 7; ++i) {
        insertBST(root, (int)nums[i]);
    }
    int cnt = (int)nums[7];
    int res = kthLargest(root, cnt);
    if (res != -1) cout << res;
    return 0;
}
