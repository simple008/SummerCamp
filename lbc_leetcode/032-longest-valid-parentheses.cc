/*
题目大意：
给一个由左右括号组成的字符串，找出该字符串中最长的匹配的字串的长度。

解题思路：
采用动态规划，定义dp[i]为以i为最后一个字符的字串的最大长度。
当s[i]为(时，结果就是0；
当s[i]为)并且s[i-1]为(时，结果是dp[i-2]+2;
当s[i]为)并且s[i-1]为）时，则需要递推的往前找，知道无法匹配。
时间复杂度应该是n吧，空间复杂度是n

遇到的问题：
一开始这个题目感觉像是动态规划，但是直接想到了二维的动归，而且计算起来应该是n的三次方。
而且找到了一维动归后，还是忘记了))这种情况需要递推往前找的。

再次阅读：
一开始看到题目，首先是一个暴力的搜索。
然后低头一看，原来用的竟然是个动归，然后就立马想起来动归的解法了。
不过看了一下之前的代码，应该是有问题的，估计是样例不够吧，比如()()这种模式，应该就是错误的。
不过也挺容易修复的。
计算一下复杂度的话，大约是有可能n*n的。

然后看了一下DISCUSS，竟然最好的解法都是用的栈来解决的。而且，都是线性复杂度。
基本思路就是将一个stack来存放当前遍历过的没有匹配到的括号，然后遍历完了，之后，就知道了所有的无法
匹配的括号的位置了。然后通过计算每个不匹配的括号之间的匹配的长度，就可以知道最后最大的匹配长度是多少了。
感觉这个思路还是非常好的，代码如下：
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length(), longest = 0;
        stack<int> st;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push(i);
            else {
                if (!st.empty()) {
                    if (s[st.top()] == '(') st.pop();
                    else st.push(i);
                }
                else st.push(i);
            }
        }
        if (st.empty()) longest = n;
        else {
            int a = n, b = 0;
            while (!st.empty()) {
                b = st.top(); st.pop();
                longest = max(longest, a-b-1);
                a = b;
            }
            longest = max(longest, a);
        }
        return longest;
    }
};
*/
class Solution {
public:
    int longestValidParentheses(string s) {
        if(s.size() < 2)return 0;
        vector<int> dp(s.size(), 0);
        int ans = 0;
        for(int i = 1; i < s.size(); ++i){
            if(s[i] == '('){
                dp[i] = 0;
            }else{
                if(s[i-1] == '('){
                    if(i == 1){
                        dp[i] = 2;
                    }else{
                        dp[i] = dp[i-2]+2;
                    }
                }else if(dp[i-1] < i && s[i-dp[i-1]-1] == '('){
                    int cur = dp[i-1] + 2;
                    int tmp = i-dp[i-1]-2;
                    while(tmp >= 0 && dp[tmp] != 0){
                        cur += dp[tmp];
                        tmp -= dp[tmp];
                    }
                    dp[i] = cur;
                }else{
                    dp[i] = 0;
                }
            }
            if(dp[i] > ans){
                ans = dp[i];
            }
        }
        return ans;
    }
};
/*
第二次做：
这次直接做出来了。用的还是之前用的思路。跟DISCUSS中的思路还是有些不一样的，人家的思路还是要
好好看一下。
另外，我感觉我这种思路应该不是n*n的复杂度，应该是n的吧。因为每次计算dp[i]的时候，实际上那个循环最多循环一次，因为前面都已经做过这件事了。
*/
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() < 2) return 0;

        int ans = 0;
        vector<int> dp(s.size(), 0);
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == ')') {
                if (s[i-1] == '(') {
                    dp[i] = 2;
                } else if (dp[i-1] && i-dp[i-1]-1 >= 0 && s[i-dp[i-1]-1] == '(') {
                    dp[i] = dp[i-1] + 2;
                    int index = i - dp[i];
                }
            }

            int index = i - dp[i];
            while (index >= 0 && dp[index]) {
                dp[i] += dp[index];
                index -= dp[index];
            }

            ans = max(ans, dp[i]);
        }

        return ans;
    }
};
/*
 * 竟然又是用的自己的方法，感觉上需要栈，竟然还是没有想出来应该怎么用
 */
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() == 0) return 0;

        int ans = 0;
        vector<int> dp(s.size(), 0);
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == ')') {
                if (i-1-dp[i-1] >= 0 && s[i-1-dp[i-1]] == '(') dp[i] = dp[i-1] + 2;
                if (i-dp[i] >= 0) dp[i] += dp[i-dp[i]];
                ans = max(ans, dp[i]);
            }
        }

        return ans;
    }
};
