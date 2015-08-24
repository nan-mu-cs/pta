#include <iostream>
#include <vector>
#include <queue>
#define SIZE 11
using namespace std;

struct tree{
    int left,right,value;
} node[SIZE];

int parent[SIZE];
vector<int> result;
queue<int> q;
int n;

int strtoint(string str){
    int result = 0;
    for(int i = 0;i<str.size();i++){
        if(str[i]>='0'&&str[i]<='9')
            result  = result*10 + str[i] - '0';
        else {
            result = -1;
            break;
        }
    }
    return result;
}

void inorder(int s){
    q.push(s);
    while(!q.empty()){
        int index = q.front();
        q.pop();
        if(node[index].left==-1&&node[index].right == -1)
            result.push_back(index);
        else{
            if(node[index].left!=-1)
                q.push(node[index].left);
            if(node[index].right!=-1)
                q.push(node[index].right);
        }
    }
}
int main(){
    string lstr,rstr;
    cin >> n;
    for(int i = 0;i<n;i++){
        cin >> lstr >> rstr;
        int left = strtoint(lstr),right = strtoint(rstr);
        node[i].left = left;
        node[i].right = right;
        if(left!=-1)
            parent[left]++;
        if(right!=-1)
            parent[right]++;
    }
    int s = 0;
    for(int i = 0;i<n;i++)
        if(parent[i] == 0)
        {
            s = i;
            break;
        }
    inorder(s);
    for(int i = 0;i<result.size();i++)
        if(i == result.size()-1)
            cout << result[i] << endl;
        else cout << result[i] << ' ';
    return 0;
}