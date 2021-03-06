/*
题目大意：
给定一个城市的建筑物的轮廓，求出总体的轮廓。

解题思路：
将所有建筑物的左右两条边拆开，然后将所有的边按照x排序。如果x相同，就按照先进后出的顺序排序。
然后依次处理各条边的情况。

遇到的问题：
一开始没有考虑将所有的边放到一起排序，感觉还是挺麻烦的。
后来看了网上的解法，大开眼界：http://yuanhsh.iteye.com/blog/2217735
而且，我竟然用的是priority_queue，不好删除元素。
发现原来set和multiset竟然有这么好的功效啊。
而且，中间还发现了一个问题，multiset要是删除val的话，是删除了所有这个val，
而删除指针的话，是只删除其中一个。

再次阅读：
感觉这道题已经考虑过很多次了，所以答案都记住了。基本这样做就行了。
*/
class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int,int>> height, ret;
        for(auto b:buildings){
            height.push_back(make_pair(b[0],-b[2]));
            height.push_back(make_pair(b[1],b[2]));
        }
        sort(height.begin(), height.end());
        multiset<int> ms;
        for(auto h:height){
            if(h.second < 0){
                if(ms.empty() || *ms.rbegin() < -h.second){
                    ret.push_back(make_pair(h.first, -h.second));
                }
                ms.insert(-h.second);
            }else{
                int last = *ms.rbegin();
                ms.erase(ms.find(h.second));
                if(h.second == last){
                    if(ms.empty()){
                        ret.push_back(make_pair(h.first, 0));
                    }else if(*ms.rbegin() != h.second){
                        ret.push_back(make_pair(h.first, *ms.rbegin()));
                    }
                }
            }
        }
        return ret;
    }
};
/*
第二次做：
比较顺利。只有一处小问题。就是ans.push_back(make_pair(l.first, s.size() == 0 ? 0 : *s.rbegin()));
高度一开始搞错了。
*/
class Solution {
private:
    typedef pair<int, int> line;
    struct Cmp {
        bool operator() (const line l, const line r) const {
            if (l.first < r.first) return true;
            if (l.first > r.first) return false;
            return l.second > r.second;
        }
    };

public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<line> lines;
        for (auto b : buildings) {
            lines.push_back(make_pair(b[0], b[2]));
            lines.push_back(make_pair(b[1], -b[2]));
        }
        sort(lines.begin(), lines.end(), Cmp());

        vector<pair<int, int>> ans;
        multiset<int> s;
        for (auto l : lines) {
            if (l.second > 0) {
                if (s.size() == 0 || *s.rbegin() < l.second) ans.push_back(l);
                s.insert(l.second);
            } else {
                s.erase(s.find(-l.second));
                if (s.size() == 0 || *s.rbegin() < -l.second) {
                    ans.push_back(make_pair(l.first, s.size() == 0 ? 0 : *s.rbegin()));
                }
            }
        }

        return  ans;
    }
};
/*
 * good question. but I have remember it.
 */
class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> lines(buildings.size()*2);
        for (int i = 0; i < buildings.size(); ++i) {
            lines[i*2] = make_pair(buildings[i][0], -buildings[i][2]);
            lines[i*2+1] = make_pair(buildings[i][1], buildings[i][2]);
        }
        sort(lines.begin(), lines.end());

        vector<pair<int, int>> ans;
        multiset<int> height;
        height.insert(0);
        for (int i = 0; i < lines.size(); ++i) {
            if (lines[i].second < 0) {
                if (*height.rbegin() < -lines[i].second) {
                    ans.push_back(make_pair(lines[i].first, -lines[i].second));
                }
                height.insert(-lines[i].second);
            } else {
                height.erase(height.find(lines[i].second));
                if (*height.rbegin() < lines[i].second) {
                    ans.push_back(make_pair(lines[i].first, *height.rbegin()));
                }
            }
        }
        return ans;
    }
};
