#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Given a set of distinct integers, nums, return
 *          all possible subsets.
 * Solve: 2^n permutations, 00..00 ~ 11..11, use the position of 1 in the num
 *        to select the position of the nums.
 * Tips: we can allocate the space for the ans first, because we know the total
 *       size.
 */
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        long long total_count = 1 << nums.size();
        vector<vector<int>> ans(total_count, vector<int>());

        for (long long i = 0; i < total_count; ++i) {
            vector<int> cur;
            long long now = i;
            for (int j = 0; j < nums.size(); ++j) {
                if (now & 0x1) {
                    cur.push_back(nums[j]);

                }
                now >>= 1;

            }
            ans[i] = cur;

        }

        return ans;

    }

}
int main()
{

}
