/*
题目大意：
给一个罗马数字，将其转换为阿拉伯数字。

解题思路：
与12题是反着的。也是利用贪心，从前往后找就行。

遇到的问题：
但是这个题目的代码如何才能写得好看点呢，感觉丑死了。
之前这个题目是不敢做的，但是感觉在变成了任务之后，好像是也没有多难。
*/
class Solution {
public:
    int romanToInt(string s) {
        map<char,int> table;
        table['I'] = 1;
        table['V'] = 5;
        table['X'] = 10;
        table['L'] = 50;
        table['C'] = 100;
        table['D'] = 500;
        table['M'] = 1000;
        int cur = 0;
        int ans = 0;
        while(cur < s.size()){
            int local = 0;
            switch(s[cur]){
                case 'I':
                    local = 1;
                    for(cur++; cur < s.size(); ++cur){
                        if(s[cur] == 'V'){
                            local = 4;
                            cur++;
                            break;
                        }else if(s[cur] == 'X'){
                            local = 9;
                            cur++;
                            break;
                        }else if(s[cur] == 'I'){
                            local += 1;
                        }else{
                            break;
                        }
                    }
                    break;
                case 'V':
                    local = 5;
                    for(cur++; cur < s.size(); ++cur){
                        if(s[cur] == 'I'){
                            local += 1;
                        }else{
                            break;
                        }
                    }
                    break;
                case 'X':
                    local = 10;
                    for(cur++; cur < s.size(); ++cur){
                        if(s[cur] == 'L'){
                            local = 40;
                            cur++;
                            break;
                        }else if(s[cur] == 'C'){
                            local = 90;
                            cur++;
                            break;
                        }else if(s[cur] == 'X'){
                            local += 10;
                        }else{
                            break;
                        }
                    }
                    break;
                case 'L':
                    local = 50;
                    for(cur++; cur < s.size(); ++cur){
                        if(s[cur] == 'X'){
                            local += 10;
                        }else{
                            break;
                        }
                    }
                    break;
                case 'C':
                    local = 100;
                    for(cur++; cur < s.size(); ++cur){
                        if(s[cur] == 'D'){
                            local = 400;
                            cur++;
                            break;
                        }else if(s[cur] == 'M'){
                            local = 900;
                            cur++;
                            break;
                        }else if(s[cur] == 'C'){
                            local += 100;
                        }else{
                            break;
                        }
                    }
                    break;
                case 'D':
                    local = 500;
                    for(cur++; cur < s.size(); ++cur){
                        if(s[cur] == 'C'){
                            local += 100;
                        }else{
                            break;
                        }
                    }
                    break;
                case 'M':
                    local = 1000;
                    for(cur += 1; cur < s.size(); ++cur){
                        if(s[cur] == 'M'){
                            local += 1000;
                        }else{
                            break;
                        }
                    }
                    break;
                default:
                    break;
            }
            ans += local;
        }
        return ans;
    }
};