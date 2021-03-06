/*
题目大意：
给定一个无序数组，问是否可以找到一个长度为3的上升子序列。

解题思路：
就是最长连续上升子序列的阉割版。

遇到的问题：
没有问题。
*/
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        if (nums.size() < 3) return false;

        vector<int> seq(3, INT_MAX);
        seq[0] = nums[0];

        for (int i = 1; i < nums.size(); ++i) {
            int index = 0;
            while (nums[i] > seq[index]) index++;
            if (index == 2) return true;
            seq[index] = nums[i];
        }

        return false;
    }
};
/*
 * bad for me. After looking at last code, I did it out.
 */
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        if (nums.size() < 3) return false;

        int small1 = nums[0], small2 = INT_MAX;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] <= small1) {
                small1 = nums[i];
            } else if (nums[i] <= small2) {
                small2 = nums[i];
            } else {
                return true;
            }
        }

        return false;
    }
};
