/*
题目大意：
给定一组素数。
问只由这些素数为引子的数的第n个多少？

解题思路：
对于每个素数，维护一个队列。表示当前找到的丑数*primes[i]所产生的丑数，该丑数一定
在该队列的末尾，因为之前的丑数都比当前的丑数要小。
还有很重要的一点就是，比如当前的丑数是从7的队列中找到的话，
那么cur * 3一定在3的队列中出现过了。也一定在5的队列中出现过了。
原因是cur 一定等于7*X，然而，3*X肯定比7*X小，所以3*X已经考虑过了。所以
3*X*7已经在7的队列中了，也就是cur*3已经出现过了。
所以我们每次更新队列的时候，只需要更新当前队列已经当前队列之后的队列就可以了。

遇到的问题：
一开始用的方法虽然也挺高效的，但是会多一个logn的倍数，一般情况下已经可以过了，但是
这道题的数据比较紧，所以还是超时。幸好在CCIW中看到了这道题。

再次阅读：
感觉这个题目做了好多次了。不过这个用k个队列的方式还是用了第一次。
感觉上这种方式已经是最优了。但是实际上，在DISCUSS中有一个更好一点的解法：
下面这种时间上稍微多一点点，但是空间上要省一些。
int nthSuperUglyNumber(int n, vector<int>& primes) {
    vector<int> index(primes.size(), 0), ugly(n, INT_MAX);
    ugly[0]=1;
    for(int i=1; i<n; i++){
        for(int j=0; j<primes.size(); j++) ugly[i]=min(ugly[i],ugly[index[j]]*primes[j]);
        for(int j=0; j<primes.size(); j++) index[j]+=(ugly[i]==ugly[index[j]]*primes[j]);
    }
    return ugly[n-1];
}
*/
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<queue<int> > vq(primes.size());
        for (int i = 0;i < vq.size(); ++i) {
            vq[i].push(primes[i]);
        }

        int cnt = 1;
        int ans = 1;
        while (cnt++ < n) {
            int next = 0;
            for (int i = 1; i < vq.size(); ++i) {
                if (vq[i].front() < vq[next].front()) {
                    next = i;
                }
            }

            ans = vq[next].front();
            vq[next].pop();

            for (int i = next; i < vq.size(); ++i) {
                vq[i].push(ans * primes[i]);
            }
        }

        return ans;
    }

    int nthSuperUglyNumber2(int n, vector<int>& primes) {
        set<int> ugly;
        ugly.insert(1);
        for (int i = 1; i < n; ++i) {
            int next = INT_MAX;
            int cur = *ugly.rbegin();
            cur++;
            for (int j = 0; j < primes.size(); ++j) {
                int tmp = (cur+primes[j]-1)/primes[j];
                tmp = *ugly.lower_bound(tmp) * primes[j];
                next = min(next, tmp);
                if (next == cur) break;
            }

            ugly.insert(next);
        }

        return *ugly.rbegin();
    }
};
/*
第二次做：
这次已经知道了怎么做了。
*/
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<queue<long long>> vq(primes.size());
        for (int i = 0; i < primes.size(); ++i) {
            vq[i].push(primes[i]);
        }

        long long cur = 1, cnt = 1;
        while (cnt++ < n) {
            int index = 0;
            for (int i = 0; i < primes.size(); ++i) {
                if (vq[i].front() < vq[index].front()) index = i;
            }

            cur = vq[index].front();
            vq[index].pop();

            for (int i = index; i < vq.size(); ++i) {
                vq[i].push(cur * primes[i]);
            }
        }

        return cur;
    }
};
/*
 * ok
 */
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        if (n == 1) return 1;

        vector<queue<int>> vq(primes.size());
        for (int i = 0; i < primes.size(); ++i) {
            vq[i].push(primes[i]);
        }

        int ans;
        for (int i = 1; i < n; ++i) {
            int index = 0;
            for (int j = 1; j < vq.size(); ++j) {
                if (vq[j].front() < vq[index].front()) index = j;
            }

            ans = vq[index].front(); vq[index].pop();
            for (int j = index; j < vq.size(); ++j) {
                vq[j].push(ans * primes[j]);
            }
        }

        return ans;
    }
};


