#include <iostream>
#include <map>
#include <queue>
using namespace std;

map<char,int> fre,idx;
map<char,string> result;

struct tree{
    int fre,value;
    bool flag;
};
struct comp{
    bool operator()(const struct tree &a,const struct tree &b){
            return a.fre>b.fre;
    }

};
struct realtree{
    struct realtree *left,*right;
    bool flag;
};
priority_queue<struct tree,vector<struct tree>,comp> pq;
int n;

int BuildTree(){
    struct tree node1,node2;
    while(pq.size()>1){
        node1 = pq.top();
        pq.pop();
        node2 = pq.top();
        pq.pop();
        node1.fre += node2.fre;
        node1.value += node2.value + node1.fre;
        pq.push(node1);
    }
    node1 = pq.top();
    pq.pop();
    if(node1.value)
        return node1.value;
    else return node1.fre;
}
bool flag = false;

struct realtree * BuildResultTree(struct realtree * root,string code,int begin){
    if(root != NULL&&begin == code.size()){
        flag = true;
        return root;
    }
    if(root!=NULL&&root->flag == true){
        flag = true;
        return root;
    }
    if(root == NULL){
        root = new struct realtree;
        root->left = root->right = NULL;
        root->flag = false;
    }
    if(begin == code.size()){
        root->flag = true;
        return root;
    }
    if(code[begin] == '0')
        root->left = BuildResultTree(root->left, code, begin+1);
    else root->right = BuildResultTree(root->right, code, begin+1);
    return root;
}

bool resultTree(){
    map<char,string>::iterator it;
    struct realtree *root = NULL;
    for(it = result.begin();it!=result.end();it++)
    {
        root = BuildResultTree(root,it->second,0);
        if(flag == true)
            break;
    }
    if(it!=result.end())
        return false;
    else return true;
}


int main(){
    char ch;
    int f;
    cin >> n;
    struct tree node;
    for(int i = 0;i<n;i++){
        cin >> ch >> f;
        fre[ch] = f;
        node.fre = f;
        node.value = 0;
        pq.push(node);
    }
    int value = BuildTree();
    int times = 0;
    cin >> times;
    while(times--){
        string code;
        int sum = 0;
        for(int i = 0;i<n;i++){
            cin >> ch >> code;
            result[ch] = code;
            sum += fre[ch]*code.size();
        }
        if(sum!=value)
            cout << "No" << endl;
        else{
            if(resultTree())
                cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    return 0;
}