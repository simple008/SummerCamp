/*
题目大意：
给定一个字符串，其中都是0-9的digit，现在定义一个数是additive number就是字符串中恰好是a+b=c,b+c=d这种形式。
例如“11235813”就是1+1=2, 1+2 = 3等等。当然，最少有三个数。然后就是开头两个数是啥无所谓，还有就是0不可以开头，
也就是不可以出现091这种，但是0单独自己是可以的。

解题思路：
算是dfs吧。

遇到的问题：
一开始也是这么个思路想试试，结果怎么都调不出来。
然后今天晚上写代码感觉思路特别清晰，改了一遍就直接过了。。。

再次阅读：
看了下DISCUSS中的解法，基本思路差不多。只不过下面这份代码还处理了大数据的时候的情况。
而且还对循环做了一点点优化，其实我一开始也是做了这个优化的，但是后来感觉影响不是很大，但是会容易出错，就算了。
class Solution {
public:
    bool isAdditiveNumber(string num) {
        for(int i=1; i<=num.size()/2; i++){
            for(int j=1; j<=(num.size()-i)/2; j++){
                if(check(num.substr(0,i), num.substr(i,j), num.substr(i+j))) return true;
            }
        }
        return false;
    }
    bool check(string num1, string num2, string num){
        if(num1.size()>1 && num1[0]=='0' || num2.size()>1 && num2[0]=='0') return false;
        string sum=add(num1, num2);
        if(num==sum) return true;
        if(num.size()<=sum.size() || sum.compare(num.substr(0,sum.size()))!=0) return false;
        else return check(num2, sum, num.substr(sum.size()));
    }
    string add(string n, string m){
        string res;
        int i=n.size()-1, j=m.size()-1, carry=0;
        while(i>=0 || j>=0){
            int sum=carry+(i>=0 ? (n[i--]-'0') : 0) + (j>=0?  (m[j--]-'0') : 0);
            res.push_back(sum%10+'0');
            carry=sum/10;
        }
        if(carry) res.push_back(carry+'0');
        reverse(res.begin(), res.end());
        return res;
    }
};
*/
class Solution {
private:
    bool dfs(long long a, long long b, string num) {
        long long c = a + b;
        string sum = to_string(c);
        //if (num.size() == 0) return true;
        if (sum == num) return true;
        if (sum != num.substr(0, sum.size())) return false;
        return dfs(b, c, num.substr(sum.size()));
    }
public:
    bool isAdditiveNumber(string num) {
        if (num.size() < 3) return false;

        for (int i = 0; i < num.size(); ++i) {
            if (i != 0 && num[0] == '0') continue;
            for (int j = i+1; j < num.size(); ++j) {
                if (j != i+1 && num[i+1] == '0') continue;

                long long a = stoll(num.substr(0, i+1));
                long long b = stoll(num.substr(i+1, j-i));
                long long c = a + b;
                string sum = to_string(c);
                if (sum.size() > num.size()-j-1 || num.substr(j+1, sum.size()) != sum) continue;
                if (dfs(a, b, num.substr(j+1))) return true;
            }
        }

        return false;
    }
};
/*
第二次做：
这次还好吧。
*/
class Solution {
    string add(const string s1, const string s2) {
        string ans(max(s1.size(), s2.size()) + 1, '0');

        int i1 = s1.size()-1, i2 = s2.size()-1, index = ans.size()-1;
        int carry = 0;
        while (i1 >= 0 || i2 >= 0) {
            if (i1 >= 0) carry += s1[i1--]-'0';
            if (i2 >= 0) carry += s2[i2--]-'0';
            ans[index--] = carry % 10 + '0';
            carry /= 10;
        }
        if (carry) ans[index--] = carry + '0';

        return ans.substr(index+1);
    }

    bool dfs(string num, string n1, string n2) {
        string sum = add(n1, n2);
        if (sum.size() > num.size()) return false;

        for (int i = 0; i < sum.size(); ++i) if (sum[i] != num[i]) return false;
        if (sum.size() == num.size()) return true;
        return dfs(num.substr(sum.size()), n2, sum);
    }

public:
    bool isAdditiveNumber(string num) {
        if (num.size() < 3) return false;

        for (int i = 0; i < num.size(); ++i) {
            if (i != 0 && num[0] == '0') break;

            for (int j = i+1; j < num.size(); ++j) {
                if (j != i+1 && num[i+1] == '0') break;

                if (dfs(num.substr(j+1), num.substr(0, i+1), num.substr(i+1, j-i))) return true;
            }
        }
        return false;
    }
};
/*
 * ok, but very tedious.
 */
class Solution {
private:
string add(const string &s1, const string &s2) {
    string ret(max(s1.size(), s2.size())+1, '0');
    int i1 = s1.size()-1, i2 = s2.size()-1, i3 = ret.size()-1;
    int carry = 0;
    while (i1 >= 0 || i2 >= 0) {
        if (i1 >= 0) carry += s1[i1--] - '0';
        if (i2 >= 0) carry += s2[i2--] - '0';
        ret[i3--] = '0' + carry % 10;
        carry /= 10;
    }
    if (carry) ret[i3--] = '0' + carry;
    return ret.substr(i3+1);
}

bool isPrefix(const string s1, const string &s2) {
    if (s1.size() > s2.size()) return false;
    for (int i = 0; i < s1.size(); ++i) {
        if (s1[i] != s2[i]) return false;
    }
    return true;
}

public:
    bool isAdditiveNumber(string num) {
        if (num.size() < 3) return false;

        for (int i = 0; i < num.size(); ++i) {
            string s1 = num.substr(0, i+1);
            if (s1[0] == '0' && s1.size() > 1) break;

            for (int j = i+1; j < num.size(); ++j) {
                string s2 = num.substr(i+1, j-i);
                if (s2[0] == '0' && s2.size() > 1) break;

                string num1 = s1, num2 = s2;
                string sum = add(num1, num2);
                if (!isPrefix(sum, num.substr(j+1))) continue;

                num1 = num2;
                num2 = sum;
                int index = j+sum.size()+1;
                bool ok = true;
                while (index < num.size()) {
                    sum = add(num1, num2);
                    if (!isPrefix(sum, num.substr(index))) {
                        ok = false;
                        break;
                    }
                    num1 = num2;
                    num2 = sum;
                    index += sum.size();
                }

                if (ok) return true;
            }
        }

        return false;
    }
};


