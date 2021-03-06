/*
题目大意：
给定一个二叉树，设计一个算法将其序列化和反序列化。

解题思路：
直接按照二叉树分层遍历的过程将其存放到字符串中。
并且按照同样的顺序将其反序列化。
见代码。

遇到的问题：
没有问题。

再次阅读：
原来这种题目有好多种方法可以解的啊。在DISCUSS中找到了一个基于二叉树先序遍历的方法：
仔细想想，实在是厉害极了啊。感觉自己对于二叉树的理解还是没有达到这个水准呢。实在是太厉害了。
class Codec {
public:

    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }

private:

    void serialize(TreeNode* root, ostringstream& out) {
        if (root) {
            out << root->val << ' ';
            serialize(root->left, out);
            serialize(root->right, out);
        } else {
            out << "# ";
        }
    }

    TreeNode* deserialize(istringstream& in) {
        string val;
        in >> val;
        if (val == "#")
            return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    vector<string> split(string str, char delim) {
        stringstream ss(str);
        vector<string> ans;

        string cur;
        while (ss >> cur) {
            ans.push_back(cur);
        }

        return ans;
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans;
        queue<TreeNode *> q;
        if (root == NULL) {
            return ans;
        }

        q.push(root);
        while (q.size() > 0) {
            TreeNode *root = q.front();
            q.pop();

            if (root == NULL) {
                ans.append("n ");
            } else {
                ans.append(to_string(root->val) + " ");
                q.push(root->left);
                q.push(root->right);
            }
        }

        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() == 0) return NULL;
        vector<string> words = split(data, ' ');

        TreeNode *root = new TreeNode(stoi(words[0]));
        queue<TreeNode *> q;
        q.push(root);

        for (int i = 1; i < words.size(); i += 2) {
            TreeNode *cur = q.front();
            q.pop();

            if (words[i][0] != 'n') {
                cur->left = new TreeNode(stoi(words[i]));
                q.push(cur->left);
            }
            if (words[i+1][0] != 'n') {
                cur->right = new TreeNode(stoi(words[i+1]));
                q.push(cur->right);
            }
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
/*
第二次做：
这次写的还不错。用的是先序遍历了。
不是之前的那种层次遍历了。其实都差不多的。
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
    TreeNode* des(string &data, int &index) {
        if (index >= data.size()) return NULL;
        if (data[index] == '#') {
            index += 2;
            return NULL;
        }

        int end = index+1;
        while (end < data.size() && data[end] != ' ') end++;

        int value = stoi(data.substr(index, end-index));
        TreeNode *root = new TreeNode(value);

        index = end+1;
        root->left = des(data, index);
        root->right = des(data, index);
        return root;
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == NULL) return "#";
        return to_string(root->val) + " " + serialize(root->left) + " " + serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int index = 0;
        return des(data, index);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
/*
 * ok, but discuss's better.
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans;
        if (root == NULL) return ans;
        queue<TreeNode *> q;
        q.push(root);
        while (q.size() > 0) {
            TreeNode *cur = q.front(); q.pop();
            if (cur == NULL) ans += " #";
            else {
                ans += " " + to_string(cur->val);
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        return ans.substr(1);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() == 0) return NULL;

        stringstream ss(data);
        int rootVal;
        ss >> rootVal;

        TreeNode *root = new TreeNode(rootVal);
        queue<TreeNode *> q;
        q.push(root);

        while (q.size() > 0) {
            TreeNode *cur = q.front(); q.pop();

            string left, right;
            ss >> left >> right;
            if (left[0] != '#') {
                cur->left = new TreeNode(stoi(left));
                q.push(cur->left);
            }
            if (right[0] != '#') {
                cur->right = new TreeNode(stoi(right));
                q.push(cur->right);
            }
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));


