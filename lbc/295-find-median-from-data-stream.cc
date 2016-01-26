/*
题目大意：
给定一个数字序列，和查询函数。求数列的动态的中位数。

解题思路：
将数字大的一半放到s1，小的一半放到s2.这样就可以用O(1)的时间复杂度求得中位数了。

遇到的问题：
一开始忘记了将set设置为multiset了。所以除了莫名其妙的错误，还去debug了半天。

再次阅读：
感觉自己对这道题的解法就是怎么想的就是怎么写的，一点技巧都没有用到啊。
然后看到DISCUSS中有一个及其简单的解法，思想一样，但是过程简单到不知道哪里去了：
class MedianFinder {
    priority_queue<long> small, large;
public:

    void addNum(int num) {
        small.push(num);
        large.push(-small.top());
        small.pop();
        if (small.size() < large.size()) {
            small.push(-large.top());
            large.pop();
        }
    }

    double findMedian() {
        return small.size() > large.size()
               ? small.top()
               : (small.top() - large.top()) / 2.0;
    }
};
*/
class MedianFinder {
private:
    multiset<int> s1, s2; // s1 large, s2 small
public:

    // Adds a number into the data structure.
    void addNum(int num) {
        if (s1.size() == 0) {
            s1.insert(num);
        } else if (s2.size() == 0) {
            int tmp = *s1.begin();
            if (tmp < num) {
                s1.erase(s1.find(tmp));
                s1.insert(num);
                s2.insert(tmp);
            } else {
                s2.insert(num);
            }
        } else {
            if (s1.size() > s2.size()) {
                //add to s2
                int tmp = *s1.begin();
                if (num > tmp) {
                    s1.erase(s1.find(tmp));
                    s1.insert(num);
                    s2.insert(tmp);
                } else {
                    s2.insert(num);
                }
            } else {
                //add to s1
                int tmp = *s2.rbegin();
                if (num < tmp) {
                    s2.erase(s2.find(tmp));
                    s2.insert(num);
                    s1.insert(tmp);
                } else {
                    s1.insert(num);
                }
            }
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        if (s1.size() > s2.size()) {
            return *s1.begin();
        } else {
            double sum = *s1.begin() + *s2.rbegin();
            return sum / 2;
        }
    }
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();