/*
题目大意：
给两个数组表示的非负整数，加起来。

解题思路：
大整数。

遇到的问题：
一次通过。

再次阅读：
首先余数的英文可以用carry来表示，再用yu感觉就要找不到工作了。
这个题目本身很简单。虽然我的做法没啥问题，但是在DISCUSS中看到了一个更好的解法：
void plusone(vector<int> &digits)
{
    int n = digits.size();
    for (int i = n - 1; i >= 0; --i)
    {
        if (digits[i] == 9)
        {
            digits[i] = 0;
        }
        else
        {
            digits[i]++;
            return;
        }
    }
        digits[0] =1;
        digits.push_back(0);

}
*/
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> ans;
        int yu = 1;
        int index = digits.size()-1;
        while(index >= 0 || yu){
            yu += digits[index--];
            ans.push_back(yu%10);
            yu /= 10;
        }
        for(int i = 0; i < ans.size()/2; ++i){
            swap(ans[i], ans[ans.size()-1-i]);
        }
        return ans;
    }
};
/*
第二次做：
简单题，不过要注意一定要仔细写简单题。
*/
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> ans;
        if (digits.size() == 0) {
            ans.push_back(1);
            return ans;
        }

        int carry = 1;
        for (int i = digits.size()-1; i >= 0; --i) {
            carry += digits[i];
            ans.push_back(carry%10);
            carry /= 10;
        }
        if (carry) ans.push_back(carry);

        for (int i = 0; i < ans.size()/2; ++i) {
            swap(ans[i], ans[ans.size()-1-i]);
        }
        return ans;
    }
};
/*
 * some easy
 */
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        for (int i = digits.size()-1; i >= 0; --i) {
            carry += digits[i];
            digits[i] = carry % 10;
            carry /= 10;
        }
        if (carry) {
            vector<int> ret(digits.size()+1);
            ret[0] = carry;
            for (int i = 1; i < ret.size(); ++i) {
                ret[i] = digits[i-1];
            }
            return ret;
        }
        return digits;
    }
};
