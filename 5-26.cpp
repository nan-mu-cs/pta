#include <iostream>
#define SIZE 20000


using namespace std;

struct YTree{
    struct YTree *left,*right;
    int lvalue,rvalue,num;
};

struct XTree{
    struct XTree *left,*right;
    struct YTree *yroot;
    int lvalue,rvalue;
};



struct YTree* CopyTree(struct YTree* aroot,struct YTree *broot){
    if(broot == NULL)
        return NULL;
    if(aroot == NULL){
        aroot = new struct YTree;
        aroot->left = aroot->right = NULL;
        aroot->num = broot->num;
        aroot->lvalue = broot->lvalue;
        aroot->rvalue = broot->rvalue;
    }
    aroot->left = CopyTree(aroot->left, broot->left);
    aroot->right = CopyTree(aroot->right, broot->right);
    return aroot;
}
struct YTree* BuildYTree(struct YTree* root,int y,int num){
    if(root == NULL){
        root = new struct YTree;
        root->left = root->right = NULL;
        root->lvalue = root->rvalue = y;
        root->num = num;
        return root;
    }
    if(root->lvalue == root->rvalue){
        if(root->lvalue>y)
        {
            root->left = BuildYTree(root->left, y, num);
            root->right = BuildYTree(root->right, root->lvalue, root->num);
            root->lvalue = y;
        }
        else if(root->rvalue<y){
            root->left = BuildYTree(root->left, root->rvalue, root->num);
            root->right = BuildYTree(root->right, y, num);
            root->rvalue = y;
        }
        root->num += num;
        return root;
    }
    int mid = (root->lvalue+root->rvalue)/2;
    if(y<=mid){
        root->left = BuildYTree(root->left, y, num);
        if(y<root->lvalue)
            root->lvalue = y;
    }
    else if(y>mid){
        root->right = BuildYTree(root->right, y, num);
        if(y>root->rvalue)
            root->rvalue = y;
    }
    //BuildYTree(root->left, , <#int num#>)
    root->num += num;
    return root;
}

struct XTree* BuildTree(struct XTree* root,int x,int y,int num){
    if(root == NULL){
        root = new struct XTree;
        root->left = root->right = NULL;
        root->yroot = NULL;
        root->yroot = BuildYTree(root->yroot, y, num);
        root->lvalue = root->rvalue = x;
        return root;
    }
    if(root->lvalue == root->rvalue){
        struct XTree *newroot = NULL;
        if(root->lvalue>x){
            newroot = new struct XTree;
            struct XTree *leftnode = new struct XTree;
            leftnode->left = leftnode->right = NULL;
            leftnode->yroot = NULL;
            leftnode->yroot = BuildYTree(leftnode->yroot, y, num);
            leftnode->lvalue = leftnode->rvalue = x;
            newroot->left = leftnode;
            //newroot->left = BuildTree(root->left, x, y, num);
            newroot->right = root;
            newroot->yroot = NULL;
            newroot->yroot = CopyTree(newroot->yroot,root->yroot);
            //newroot->yroot = root->yroot;
            newroot->lvalue = x;
            newroot->rvalue = root->lvalue;
        }
        else if(root->rvalue<x){
            struct XTree *rightnode = new struct XTree;
            rightnode->left = rightnode->right =  NULL;
            rightnode->yroot = NULL;
            rightnode->yroot = BuildYTree(rightnode->yroot, y, num);
            rightnode->lvalue = rightnode->rvalue = x;
            newroot = new struct XTree;
            newroot->left = root;
            newroot->right = rightnode;
            //newroot->yroot = root->yroot;
            newroot->yroot = NULL;
            newroot->yroot = CopyTree(newroot->yroot,root->yroot);
            //newroot->right = BuildTree(root->right, x, y, num);
            newroot->lvalue = root->lvalue;
            newroot->rvalue = x;
        }
        if(newroot){
            newroot->yroot = BuildYTree(newroot->yroot, y, num);
            return newroot;
        }
        else {
            root->yroot = BuildYTree(root->yroot, y, num);
            return root;
        }
    }
    root->yroot = BuildYTree(root->yroot, y, num);
    int mid = (root->lvalue + root->rvalue)/2;
    if(x<=root->right->lvalue){
        root->left = BuildTree(root->left, x, y, num);
        if(x<root->lvalue)
            root->lvalue = x;
    }
    else {
        root->right = BuildTree(root->right, x, y, num);
        if(x>root->rvalue)
            root->rvalue = x;
    }
    return root;
}

int QueryYTree(struct YTree* root,int ymin,int ymax){
    if(root == NULL)
        return 0;
    if(ymin<=root->lvalue&&ymax>=root->rvalue)
        return root->num;
    int result = 0;
    int mid = (root->lvalue+root->rvalue)/2;
    if(root->left&&root->left->rvalue>=ymin)
        result += QueryYTree(root->left, ymin, ymax);
    if(root->right&&root->right->lvalue<=ymax)
        result += QueryYTree(root->right, ymin, ymax);
    return result;
}

int QueryTree(struct XTree* root,int xmin,int xmax,int ymin,int ymax){
    if(root == NULL)
        return 0;
    if(xmin<=root->lvalue&&xmax>=root->rvalue)
        return QueryYTree(root->yroot, ymin, ymax);
    int result,mid;
    result = 0;
    mid = (root->lvalue + root->rvalue)/2;
    if(root->left&&root->left->rvalue>=xmin)
        result += QueryTree(root->left, xmin, xmax, ymin, ymax);
    if(root->right&&root->right->lvalue<=xmax)
        result += QueryTree(root->right, xmin, xmax, ymin, ymax);
    return result;
}

int strtoint(string str){
    int i,result;
    result = 0;
    for(i = 0;i<str.size();i++)
        if(str[i]>='0'&&str[i]<='9')
            result  = result*10 + str[i] - '0';
        else break;
    if(i<str.size())
        return -1;
    else return result;
}

int main(){
    string cmd;
    cin >> cmd;
    struct XTree *root = NULL;
    while(1){
        if(cmd == "E")
            break;
        while(1){
            string str;
            cin >> str;
            int x;
            x = strtoint(str);
            if(x == -1)
            {
                cmd = str;
                break;
            }
            if(cmd == "I"){
                int y,num;
                cin >> y >> num;
                root = BuildTree(root,x,y,num);
            }
            else {
                int xmin,xmax,ymin,ymax;
                xmin = x;
                cin >> xmax >> ymin >> ymax;
                cout << QueryTree(root,xmin,xmax,ymin,ymax) << endl;
            }
        }
    }
    return 0;
}
