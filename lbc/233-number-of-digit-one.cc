/*
题目大意：
给定一个整数n，求从1-n的所有数中，1出现的次数。

解题思路：
对于某一位数字来说，在该位出现1的次数，比如百位：
如果百位等于0：n/1000 * 100 
如果百位等于1：n/1000 * 100 + n%100+1
如果百位大于1：(n/1000+1) * 100

遇到的问题：
看了别人的思路才理解的。
参考资料：http://blog.csdn.net/xudli/article/details/46798619
*/
class Solution {
public:
    int countDigitOne(int n) {
        int ret = 0;
        for(long i = 1; i <= n; i *= 10){
            int a = n/i;
            int b = n%i;
            if(a % 10 == 0){
                ret += a/10*i;
            }else if(a % 10 == 1){
                ret += a/10*i+b+1;
            }else{
                ret += (a/10+1)*i;
            }
        }
        return ret;
    }
};