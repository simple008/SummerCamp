/*
题目大意：
给定一个字符串，将其中所有的word都翻转。

解题思路：
注意题目中单词的定义：以空格为分割的字符序列。
而且，题目要求，如果首尾有空格，则省去；而且单词间多余一个空格都变为一个空格。

遇到的问题：
感觉这个跟翻转url的题目是很类似的。结果忘了处理多余空格的问题了。
然后又加上了处理空格的代码才过的。
不过感觉代码还需要整理一下，或者优化一下。

再次阅读：
一道经典老题了，这种解法应该是目前最好的了吧？
不过在DISCUSS中还有人用一个临时的数组记录下来翻转的单词：
class Solution {
public:
    void reverseWords(string &s) {
        string result;
        int pos = 0;
        for (int i = 0; i < s.size(); i ++){
            if (s[i] == ' '){
                if (i > pos )
                    result = s.substr(pos,i-pos)+ " " + result ;
                pos = i + 1;
            }
            else if (i == s.size()-1)
                result = s.substr(pos,s.size()-pos)+" "+result;
        }
        s = result.substr(0,result.size()-1) ;
    }
};
*/
class Solution {
public:
    void reverseWords(string &s) {
        if(s.size() == 0)return;
        string tmp;
        int cur = 0;
        while(cur < s.size()){
            while(cur < s.size() && s[cur] == ' ')cur++;
            if(cur >= s.size())break;
            tmp.push_back(' ');
            while(cur < s.size() && s[cur] != ' '){
                tmp.push_back(s[cur]);
                cur++;
            }
        }
        if(tmp == ""){
            s = tmp;
        }else if(tmp[0] == ' '){
            s = tmp.substr(1, tmp.size()-1);
        }else{
            s = tmp;
        }

        sub(s, 0, s.size()-1);
        int left = 0;
        while(left < s.size() && s[left] == ' ')left++;
        while(left < s.size()){
            int right = left+1;
            while(right < s.size() && s[right] != ' ')right++;
            sub(s, left, right-1);
            left = right+1;
            while(left < s.size() && s[left] == ' ')left++;
        }
    }

    void sub(string &s, int left, int right){
        for(int i = left; i < left+(right-left+1)/2; ++i){
            swap(s[i], s[right-i+left]);
        }
    }
};
/*
第二次做：
这次做的还可以吧。不过还是稍微除了一点点问题。
*/
class Solution {
private:
    void reverse(string &s, int left, int right) {
        for (int i = left; i < left+(right-left+1)/2; ++i) {
            swap(s[i], s[right-i+left]);
        }
    }

public:
    void reverseWords(string &s) {
        int len = 0, index = 0;

        while (index < s.size() && s[index] == ' ') index++;
        if (index == s.size()) {
            s = "";
            return;
        }

        while (index < s.size()) {
            while (index < s.size() && s[index] != ' ') s[len++] = s[index++];
            while (index < s.size() && s[index] == ' ') index++;
            if (index != s.size()) s[len++] = ' ';
        }

        reverse(s, 0, len-1);

        int start = 0, end = 0;
        while (start < len) {
            while (end < len && s[end] != ' ') end++;
            reverse(s, start, end-1);
            start = end+1;
            end = start;
        }

        s = s.substr(0, len);
    }
};
/*
 * it's ok
 */
class Solution {
private:
    void reverse(string &s, int left, int right) {
        while (left < right) {
            swap(s[left++], s[right--]);
        }
    }

public:
    void reverseWords(string &s) {
        string ans;
        int index = 0;

        while (index < s.size()) {
            while (index < s.size() && s[index] == ' ') index++;
            if (index == s.size()) break;
            int next = index+1;
            while (next < s.size() && s[next] != ' ') next++;

            if (ans.size() == 0) {
                ans = s.substr(index, next-index);
            } else {
                ans += " " + s.substr(index, next-index);
            }
            index = next;
        }

        s = ans;
        if (s.size() == 0) return;

        reverse(s, 0, s.size()-1);
        index = 0;
        while (index < s.size()) {
            int next = index+1;
            while (next < s.size() && s[next] != ' ') next++;
            reverse(s, index, next-1);
            index = next+1;
        }
    }
};
