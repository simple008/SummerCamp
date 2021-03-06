/*
题目大意：
给定一个数组，求其中的某一段区间的和。
查询操作可能有很多次。而且中间数组也不会变。

解题思路：
将数组的前缀和算出来，求和的时候直接做减法就行了。

遇到的问题：
没有问题。

再次阅读：
比较简单，之前这种解答方式没啥问题。
只是最近我发现有很多人对于STL的使用实在是达到了炉火纯青的地步啊：
class NumArray {
public:
    NumArray(vector<int> &nums) : psum(nums.size()+1, 0) {
        partial_sum( nums.begin(), nums.end(), psum.begin()+1);
    }

    int sumRange(int i, int j) {
        return psum[j+1] - psum[i];
    }
private:
    vector<int> psum;
};
*/
class NumArray {
    vector<long long> ans;
public:
    NumArray(vector<int> &nums) {
        if (nums.size() == 0) return;
        ans.push_back(nums[0]);
        for (int i = 1; i < nums.size(); ++i) {
            int next = ans[ans.size()-1] + nums[i];
            ans.push_back(next);
        }
    }

    int sumRange(int i, int j) {
        if (i == 0) {
            return ans[j];
        }
        return ans[j] - ans[i-1];
    }
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);
/*
第二次做：
是我想多了，还想着用树状数组呢，真是傻逼。
树状数组是用来动态计算区间的和的。
*/
class NumArray {
    vector<long long> sum;
public:
    NumArray(vector<int> &nums) {
        sum.push_back(0);
        for (auto n : nums) {
            sum.push_back(sum.back() + n);
        }
    }

    int sumRange(int i, int j) {
        return sum[j+1] - sum[i];
    }
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);
/*
 * ok
 */
class NumArray {
private:
    vector<long long> sum;

public:
    NumArray(vector<int> &nums) {
        sum = vector<long long>(nums.size()+1);
        for (int i = 0; i < nums.size(); ++i) {
            sum[i+1] = sum[i] + nums[i];
        }
    }

    int sumRange(int i, int j) {
        return sum[j+1] - sum[i];
    }
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);


