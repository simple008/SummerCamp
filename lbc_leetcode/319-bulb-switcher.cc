/*
题目大意：
给定n个灯，一开始都是关着的。第一轮，将所有灯的状态改变；第二轮，将所有
为2的倍数的灯的转台改变；。。。；第n轮，改变第n个灯的状态。
问最后有多少等是亮着的。

解题思路：
其实相当于是判断某个灯最后是否是亮着的，只需要判断该数字的因数的个数为奇数个。
然后进一步观察发现，只有为某数平方的数才能满足该条件。
见代码。

遇到的问题：
一开始用的模拟的方法，超时了。

再次阅读：
其实这道题目我应该在很久之前就知道的了。感觉这种方式还是挺好的，数学规律。
但是可以直接用sqrt来求解也是可以的：
int bulbSwitch(int n) {
    return sqrt(n);
}
*/
class Solution {
public:
    int bulbSwitch(int n) {
        int ret = 0;
        for (int i = 1; i*i <= n; ++i) {
            ret++;
        }

        return ret;
    }
};
/*
第二次做：
二分。
注意要使用long long才不会越界。
*/
class Solution {
public:
    int bulbSwitch(int n) {
        if (n < 1) return 0;

        long long left = 1, right = n;
        while (left < right) {
            long long mid = (left + right + 1) >> 1;
            if (mid*mid > n) right = mid-1;
            else left = mid;
        }

        return left;
    }
};
/*
 * good
 */
class Solution {
public:
    int bulbSwitch(int n) {
        if (n < 1) return 0;
        int left = 1, right = n;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (mid <= n / mid) left = mid;
            else right = mid - 1;
        }

        return left;
    }
};


