/*注意单转时要再次计算两次树高*/
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>
#define SIZE 21

using namespace std;
struct tree{
    struct tree *left,*right;
    int value,height;
} node;
int Height(struct tree *node){
    if( node == NULL)
        return -1;
    else return node->height;
}

struct tree * SingleRotatLeft(struct tree * node){
    struct tree * root = node->left;
    node->left = root->right;
    root->right = node;
    node->height = max(Height(node->left),Height(node->right)) + 1;
    root->height = max(Height(root->left),Height(root->right)) + 1;
    return root;
}

struct tree * SingleRotatRight(struct tree *node){
    struct tree * root = node->right;
    node->right = root->left;
    root->left = node;
    node->height = max(Height(node->left),Height(node->right)) + 1;
    root->height = max(Height(root->left),Height(root->right)) + 1;
    return root;
}

struct tree * DoubleRotatLeft(struct tree *node){
    node->left = SingleRotatRight(node->left);
    node = SingleRotatLeft(node);
    return node;
}

struct tree * DoubleRotatRight(struct tree *node){
    node->right = SingleRotatLeft(node->right);
    node = SingleRotatRight(node);
    return node;
}
struct tree* BuildTree(struct tree *root,struct tree *node){
    if (root == NULL) {
        root = node;
        return node;
    }
    if(root->value>node->value){
        root->left = BuildTree(root->left,node);
        if(Height(root->left)- Height(root->right)>1){
            if(root->left->value>node->value){
                root = SingleRotatLeft(root);
            }
            else root = DoubleRotatLeft(root);
        }
    }
    else{
        root->right = BuildTree(root->right, node);
        if(Height(root->right) - Height(root->left)>1){
            if(root->right->value<node->value)
                root = SingleRotatRight(root);
            else root = DoubleRotatRight(root);
        }
    }
    root->height = max(Height(root->left),Height(root->right))+1;
    return root;
}

int main(){
    int n,value;
    cin >> n;
    struct tree *root = NULL;
    struct tree *node;
    for(int i = 0;i<n;i++){
        cin >> value;
        node = new struct tree;
        node->value = value;
        node->left = node->right = NULL;
        node->height = 0;
        root = BuildTree(root,node);
    }
    if(root)
        cout << root->value << endl;
    return 0;
}