#include <iostream>
#include <vector>
#define SIZE 11
using namespace std;
struct tree{
    int value;
    struct tree *left,*right;
};
vector<int> v;

struct tree *InsertTree(int value,struct tree *root){
    if(root == NULL){
        root = new struct tree;
        root->left = root->right = NULL;
        root->value = value;
        return root;
    }
    if(value<root->value)
        root->left = InsertTree(value, root->left);
    else root->right = InsertTree(value, root->right);
    return root;
}

bool JudgeSame(struct tree *root,vector<int> v){
    if(root == NULL)
        return true;
    if(v.size() == 0)
        return false;
    if(root->value != v[0])
        return false;
    vector<int> vleft,vright;
    for(int i = 1;i<v.size();i++)
        if(v[i]<root->value)
            vleft.push_back(v[i]);
        else vright.push_back(v[i]);
    return JudgeSame(root->left, vleft) && JudgeSame(root->right, vright);
}

int main(){
    int n;
    while(1){
        cin >> n;
        if(n == 0)
            break;
        int query;
        cin >> query;
        int ele;
        struct tree *root = NULL;
        for(int i = 0;i<n;i++){
            cin >> ele;
            root = InsertTree(ele,root);
        }
        while(query--){
            v.clear();
            for(int i = 0;i<n;i++)
            {
                cin >> ele;
                v.push_back(ele);
            }
            if(JudgeSame(root,v))
                cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    return 0;
}