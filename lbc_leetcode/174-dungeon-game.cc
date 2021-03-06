/*
题目大意：
给定一个二维的board，然后需要从左上角到右下角去。
然后需要找到最初的一个体力值，使得某条路径上的所有点都是非负的。

解题思路：
动归+二分

遇到的问题：
原来看到这个题目的时候，感觉好像好难好难的，没敢做。
这次大体看了一下，感觉这个思路其实是可以做的。
然后竟然真的做出来了。

再次阅读：
虽然这次想到的还是二分+动归。
但是还是抱着试一试的心态看了一下DISCUSS有没有更好的解法，结果真的有人就一次动归就做出来了。。。
class Solution {
public:
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
        int M = dungeon.size();
        int N = dungeon[0].size();
        // hp[i][j] represents the min hp needed at position (i, j)
        // Add dummy row and column at bottom and right side
        vector<vector<int> > hp(M + 1, vector<int>(N + 1, INT_MAX));
        hp[M][N - 1] = 1;
        hp[M - 1][N] = 1;
        for (int i = M - 1; i >= 0; i--) {
            for (int j = N - 1; j >= 0; j--) {
                int need = min(hp[i + 1][j], hp[i][j + 1]) - dungeon[i][j];
                hp[i][j] = need <= 0 ? 1 : need;
            }
        }
        return hp[0][0];
    }
};
*/
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int old = dungeon[0][0];
        long long left = INT_MIN, right = INT_MAX;
        int ret = INT_MAX;
        while(left <= right){
            long long mid = left + (right-left+1)/2;
            dungeon[0][0] = mid;
            if(sub(dungeon)){
                if(mid < ret){
                    ret = mid;
                }
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        ret -= old;
        if(ret <= 0)ret = 1;
        return ret;
    }

    bool sub(vector<vector<int>> &dungeon){
        vector<vector<long long>> dp(dungeon.size(), vector<long long>(dungeon[0].size()));
        dp[0][0] = dungeon[0][0];
        if(dp[0][0] <= 0)return false;
        for(int i = 1; i < dp.size(); ++i){
            if(dp[i-1][0] <= 0)dp[i][0] = 0;
            else dp[i][0] = dp[i-1][0] + dungeon[i][0];
        }
        for(int i = 1; i < dp[0].size(); ++i){
            if(dp[0][i-1] <= 0)dp[0][i] = 0;
            else dp[0][i] = dp[0][i-1] + dungeon[0][i];
        }
        for(int i = 1; i < dp.size(); ++i){
            for(int j = 1; j < dp[0].size(); ++j){
                if(dp[i-1][j] <= 0 && dp[i][j-1] <= 0)dp[i][j] = 0;
                else if(dp[i-1][j] <= 0)dp[i][j] = dp[i][j-1] + dungeon[i][j];
                else if(dp[i][j-1] <= 0)dp[i][j] = dp[i-1][j] + dungeon[i][j];
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + dungeon[i][j];
            }
        }
        return dp[dp.size()-1][dp[0].size()-1] > 0;
    }
};
/*
第二次做：
这次做的还不错，思路清晰，代码简洁。只是中间有一点点小问题。
*/
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        assert(m > 0);
        int n = dungeon[0].size();
        assert(n > 0);

        int left = 1, right = INT_MAX;
        while (left < right) {
            int mid = left + ((right-left)>>1);

            vector<int> dp(n);
            dp[0] = dungeon[0][0] + mid;
            for (int i = 1; i < n; ++i) {
                if (dp[i-1] <= 0) dp[i] = 0;
                else dp[i] = dp[i-1] + dungeon[0][i];
            }

            for (int i = 1; i < m; ++i) {
                if (dp[0] > 0) dp[0] += dungeon[i][0];
                for (int j = 1; j < n; ++j) {
                    int health = 0;
                    if (dp[j-1] > 0) health = max(dp[j-1]+dungeon[i][j], health);
                    if (dp[j] > 0) health = max(dp[j]+dungeon[i][j], health);
                    dp[j] = health;
                }
            }

            if (dp[n-1] > 0) {
                right = mid;
            } else {
                left = mid+1;
            }
        }
        return left;
    }
};
/*
 * new method. cheers
 */
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();

        vector<vector<int>> dp(m, vector<int>(n));
        dp[m-1][n-1] = 1 - dungeon[m-1][n-1] < 1 ? 1 : 1 - dungeon[m-1][n-1];
        for (int i = n-2; i >= 0; --i) {
            dp[m-1][i] = dp[m-1][i+1] - dungeon[m-1][i];
            if (dp[m-1][i] < 1) dp[m-1][i] = 1;
        }

        for (int i = m-2; i >= 0; --i) {
            dp[i][n-1] = dp[i+1][n-1] - dungeon[i][n-1] < 1 ? 1 : dp[i+1][n-1] - dungeon[i][n-1];
            for (int j = n-2; j >= 0; --j) {
                dp[i][j] = min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j];
                if (dp[i][j] < 1) dp[i][j] = 1;
            }
        }

        return dp[0][0];
    }
};
