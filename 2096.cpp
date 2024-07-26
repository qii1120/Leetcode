#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <string.h>
#include <set>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
TreeNode *find(TreeNode *node, int val)
{
    if (node->val == val)
        return node;
    if (node->left != nullptr && find(node->left, val) != nullptr)
        return find(node->left, val);
    if (node->right != nullptr && find(node->right, val) != nullptr)
        return find(node->right, val);
    return nullptr;
}
void findDir(TreeNode *node, int val, string &str)
{
    // cout<<node->val<<" "<<val<<endl;
    if (node->val == val)
    {
        str = "F";
        return;
    }
    if (node->left != nullptr)
    {
        findDir(node->left, val, str);
        if (str == "F")
            str = "L";
        else if (str != "N" && str != "F")
            str += "L";
        if(str=="N") str.clear();
        else return ;
    }
    if (node->right != nullptr)
    {
        findDir(node->right, val, str);
        if (str == "F")
            str = "R";
        else if (str != "N" && str != "F")
            str += "R";
        if(str=="N") str.clear();
        else return ;
    }
    str = "N";
    return;
}
string getDirections(TreeNode *root, int startValue, int destValue)
{
    string start, dest, result;
    findDir(root, startValue, start);
    findDir(root, destValue, dest);
    // cout<<"s"<<endl<<start<<endl;
    // cout<<dest<<endl;
    reverse(start.begin(), start.end());
    reverse(dest.begin(), dest.end());
    while (start[0] == dest[0])
    {
        start = start.substr(1);
        dest = dest.substr(1);
    }
    for (int i = 0; i < start.length() && start[i] != 'F'; i++)
        result += "U";
    return result.append(dest != "F" ? dest : "");
}
int main()
{
    string path;
    TreeNode *root = new TreeNode(0);
    TreeNode *n1 = new TreeNode(1);
    TreeNode *n2 = new TreeNode(2);
    TreeNode *n3 = new TreeNode(3);
    TreeNode *n4 = new TreeNode(4);
    TreeNode *n5 = new TreeNode(5);
    root->left = n1;
    root->right = n2;
    n1->left = n3;
    n1->right = n4;
    n2->left = n5;
    findDir(root, 3, path);
    // cout << find(root, 5)->val << endl;
    cout << path << endl;
    cout << endl;
    cout << getDirections(root, 3, 5) << endl;
    return 0;
}