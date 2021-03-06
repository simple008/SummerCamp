/*
题目大意：
给一个二叉树，判定该二叉树是否是对称的？

解题思路：
递归

遇到的问题：
一次通过。

再次阅读：
没啥问题，比较简单，直接递归求解就行。
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
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL)return true;
        return sub(root->left, root->right);
    }

    bool sub(TreeNode *left, TreeNode *right){
        if(left == NULL && right == NULL){
            return true;
        }else if(left == NULL || right == NULL || left->val != right->val){
            return false;
        }else{
            return sub(left->left, right->right) && sub(left->right, right->left);
        }
    }
};
/*
第二次做：
太简单的题目了。
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
class Solution {
private:
    bool sub(TreeNode *left, TreeNode *right) {
        if (left == NULL || right == NULL) return left == right;
        if (left->val != right->val) return false;
        return sub(left->left, right->right) && sub(left->right, right->left);
    }

public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        return sub(root->left, root->right);
    }
};
/*
 * too easy
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
class Solution {
private:
    bool isMirror(TreeNode *left, TreeNode *right) {
        if (left == NULL || right == NULL) return left == right;
        if (left->val != right->val) return false;
        return isMirror(left->left, right->right) && isMirror(left->right, right->left);
    }

public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        return isMirror(root->left, root->right);
    }
};
