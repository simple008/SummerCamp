/*
题目大意：
给定一个n，和k。
求出1-n数字的所有的k个数字的组合。

解题思路：
回溯。

遇到的问题：
无。

再次阅读：
没有问题。代码也还好。
*/
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> cur;
        sub(ans, cur, n, 1, k);
        return ans;
    }

    void sub(vector<vector<int>> &ans, vector<int> &cur, int n, int i, int k){
        if(k == 0){
            ans.push_back(cur);
            return;
        }
        if(n-i+1 < k)return;
        cur.push_back(i);
        sub(ans, cur, n , i+1, k-1);
        cur.pop_back();
        sub(ans, cur, n, i+1, k);
    }
};
/*
第二次做：
还可以，比较简单。
*/
class Solution {
    void dfs(vector<vector<int> > &ans, vector<int> &cur, int n, int k, int now) {
        if (cur.size() == k) {
            ans.push_back(cur);
            return;
        }
        if (n-now+1 < k-cur.size()) return;

        cur.push_back(now);
        dfs(ans, cur, n, k, now+1);
        cur.pop_back();
        dfs(ans, cur, n, k, now+1);
    }
public:
    vector<vector<int>> combine(int n, int k) {
        assert(n >= k && k > 0);

        vector<vector<int> > ans;
        vector<int> cur;
        dfs(ans, cur, n, k, 1);

        return ans;
    }
};
/*
 * almost there
 */
class Solution {
private:
    void dfs(vector<vector<int>> &ans, vector<int> &now, int i, int n, int k) {
        if (i > n) {
            if (now.size() == k) ans.push_back(now);
            return;
        }
        if (now.size() > k || n-i+1+now.size() < k) return;

        now.push_back(i);
        dfs(ans, now, i+1, n, k);
        now.pop_back();
        dfs(ans, now, i+1, n, k);
    }

public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> now;
        dfs(ans, now, 1, n, k);
        return ans;
    }
};
