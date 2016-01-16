/*
题目大意：
大整数乘法。非负。

解题思路：
按照每一位来进行一位乘法。
然后将结果加起来。

遇到的问题：
没有问题。代码细节。

再次阅读：
虽然感觉没有太大的思路问题，但是感觉效率稍微有点问题。
然后看到DISCUSS中有一个用迭代的方式计算的，而且空间是一次性申请。
感觉这个写法实在是无懈可击啊：
string multiply(string num1, string num2) {
    string sum(num1.size() + num2.size(), '0');

    for (int i = num1.size() - 1; 0 <= i; --i) {
        int carry = 0;
        for (int j = num2.size() - 1; 0 <= j; --j) {
            int tmp = (sum[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
            sum[i + j + 1] = tmp % 10 + '0';
            carry = tmp / 10;
        }
        sum[i] += carry;
    }

    size_t startpos = sum.find_first_not_of("0");
    if (string::npos != startpos) {
        return sum.substr(startpos);
    }
    return "0";
}
*/
class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0")return num1;
        if(num2 == "0")return num2;
        string ans;
        for(int i = num2.size()-1; i >= 0; --i){
            if(num2[i] == '0')continue;
            string tmp = subMul(num1, num2[i]-'0');
            if(ans == ""){
                ans = tmp+string(num2.size()-i-1, '0');
            }else{
                ans = add(ans, tmp+string(num2.size()-i-1, '0'));
            }
        }
        return ans;
    }
    
    string subMul(string num, int x){
        int index = num.size()-1;
        int yu = 0;
        string ans;
        while(index >= 0 || yu){
            if(index >= 0){
                yu += (num[index]-'0')*x;
                index--;
            }
            ans.push_back(yu%10+'0');
            yu /= 10;
        }
        for(int i = 0; i < ans.size()/2; ++i){
            swap(ans[i], ans[ans.size()-1-i]);
        }
        return ans;
    }
    string add(string s1, string s2){
        int index1 = s1.size()-1;
        int index2 = s2.size()-1;
        int yu = 0;
        string ans;
        while(index1 >= 0 || index2 >= 0 || yu){
            if(index1 >= 0){
                yu += s1[index1]-'0';
                index1--;
            }
            if(index2 >= 0){
                yu += s2[index2]-'0';
                index2--;
            }
            ans.push_back(yu%10+'0');
            yu /= 10;
        }
        for(int i = 0; i < ans.size()/2; ++i){
            swap(ans[i], ans[ans.size()-1-i]);
        }
        return ans;
    }
};