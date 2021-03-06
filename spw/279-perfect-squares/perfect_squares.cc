/**
 * Problem: Given a positive integer n, find the least number of
 *          perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
 * Solve: dp and static vector
 * Tips: every time we iterator to index m instead of n
 */
class Solution {
    public:
        int numSquares(int n) {
            if (n <= 0) return 0;

            static vector<int> nums(1, 0);
            while (nums.size() <= n) {

                int min_step = INT_MAX;
                int m = nums.size();
                for (int i = 1; i*i <= m; ++i) {
                    min_step = min(min_step, nums[m-i*i]+1);
                }

                nums.push_back(min_step);
            }

            return nums[n];
        }
};

class Solution {
public:
    int numSquares(int n) {
        vector<int> ans(n+1, INT_MAX);

        ans[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j*j <= i; ++j) {
                ans[i] = min(ans[i], ans[i-j*j]+1);
            }
        }

        return ans[n];
    }

};
