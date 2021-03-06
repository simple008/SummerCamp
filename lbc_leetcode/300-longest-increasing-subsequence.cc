/*
题目大意：
给定一个数组，求其最长上升子序列。

解题思路：
动归。
普通的动归是n*n的复杂度。
如果我们把每个最长的上升子序列的最后一个数字记录下来的话，可以用二分查找进行更新。
使得复杂度变为nlogn。

遇到的问题：
本来知道是有nlogn的方法的，可是自己还是没有想起来到底应该二分哪个东西。

再次阅读：
这次想起来是怎么做到二分到nlogn的复杂度了。
其实之前的代码已经很不错了。但是在DISCUSS中找到了一个用stl非常好的解法：
int lengthOfLIS(vector<int>& nums) {
    vector<int> res;
    for(int i=0; i<nums.size(); i++) {
        auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
        if(it==res.end()) res.push_back(nums[i]);
        else *it = nums[i];
    }
    return res.size();
}

*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() < 2) return nums.size();

        vector<int> dp(nums.size());
        int len = 1;
        dp[0] = nums[0];

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > dp[len-1]) {
                dp[len++] = nums[i];
            } else {
                int left = 0, right = len-1, index = len-1;
                while (left <= right) {
                    int mid = left + (right-left)/2;
                    if (dp[mid] >= nums[i]) {
                        index = min(index, mid);
                        right = mid-1;
                    } else {
                        left = mid+1;
                    }
                }
                dp[index] = nums[i];
            }
        }

        return len;
    }
};
/*
第二次做：
这次做的还不错。
只是二分的时候又把等号搞错方向了。
*/
class Solution {
    int binarySearch(vector<int> &v, int val) {
        int left = 0, right = v.size()-1;
        while (left < right) {
            int mid = (left+right) >> 1;
            if (v[mid] >= val) right = mid;
            else left = mid+1;
        }

        if (v[left] >= val) return left;
        return v.size();
    }

public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 0) return 0;

        vector<int> seq;
        seq.push_back(nums[0]);

        for (int i = 1; i < nums.size(); ++i) {
            int index = binarySearch(seq, nums[i]);
            if (index == seq.size()) seq.push_back(nums[i]);
            else seq[index] = nums[i];
        }

        return seq.size();
    }
};
/*
 * good
 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() < 2) return nums.size();

        vector<int> dp;
        dp.push_back(nums[0]);
        for (int i = 1; i < nums.size(); ++i) {
            int left = 0, right = dp.size()-1;
            while (left < right) {
                int mid  = (left + right) / 2;
                if (dp[mid] < nums[i]) left = mid + 1;
                else right = mid;
            }
            if (dp[left] < nums[i]) dp.push_back(nums[i]);
            else if (dp[left] > nums[i]) dp[left] = nums[i];
        }

        return dp.size();
    }
};


