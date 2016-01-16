/*
题目大意：
给一个二分查找树，交换其中两个节点的值。要求恢复这棵树。空间复杂度为常数。

解题思路：
如果不考虑空间复杂度的话，可以将二叉树的中序遍历记录下来，然后找到两个元素，恢复之。
现在不用额外空间，思路一样，中序遍历二叉树。在遍历的过程中，记录当前节点的pre。如果只
找到一个不符合顺序的节点的话，那么说明这个节点跟其pre交换了；如果有两个这样的节点的话，
说明是第一个的pre和第二个节点交换了。

遇到的问题：
这个题本来是想错了，以为交换了两棵子树呢。
后来知道交换的是点，还是没有自己想出来中序遍历进行找错。
总之，就是对于二分查找树的概念理解的还是不够到位。

再次阅读：
自己想了一下，竟然跟之前的解法不谋而合。
不过显然之前的解法是看的别人的，这次是完全自己想的。
之前的代码还不错。
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
    void recoverTree(TreeNode* root) {
        pair<TreeNode *, TreeNode *> wrong;
        sub(wrong, root, NULL);
        swap(wrong.first->val, wrong.second->val);
    }
    
    TreeNode * sub(pair<TreeNode *, TreeNode *> &wrong, TreeNode *root, TreeNode *pre){
        if(root == NULL)return NULL;
        if(root->left != NULL){
            pre = sub(wrong, root->left, pre);
            
        }
        if(pre != NULL){
            if(pre->val > root->val){
                if(wrong.first == NULL){
                    wrong.first = pre;
                    wrong.second = root;
                }else{
                    wrong.second = root;
                }
            }
        }
        if(root->right != NULL)return sub(wrong, root->right, root);
        return root;
    }
};