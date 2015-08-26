#include <iostream>
#include <vector>
#include <queue>
#define SIZE 101
using namespace std;

vector<int> node[SIZE];
vector<int> result;
int nxt;
int cnt = 0;
int level = 0;
int lvl[SIZE];
void CountLeaves(){
    queue<int> q;
    q.push(1);
    level = 0;
    lvl[1] = 0;
    while(!q.empty()){
        int index = q.front();
        q.pop();
        if(lvl[index]!=level){
            level = lvl[index];
            result.push_back(cnt);
            cnt = 0;
        }
        if(node[index].size()){
            for(int i = 0;i<node[index].size();i++){
                q.push(node[index][i]);
                lvl[node[index][i]] = lvl[index]+1;
            }
        }
        else cnt++;
    }
}

int main(){
    int n,m;
    while(1){
        cin >> n >> m;
        if(n == 0)
            break;
        result.clear();
        for(int i = 0;i<=100;i++)
            node[i].clear();
        for(int i = 0;i<=100;i++)
            lvl[i] = 0;
        int parent,numofchild,child;
        for(int j = 0;j<m;j++){
            cin >> parent >> numofchild;
            for(int i = 0;i<numofchild;i++){
                cin >> child;
                node[parent].push_back(child);
            }
        }
        nxt = 1;
        CountLeaves();
        result.push_back(cnt);
        cnt = 0;
        for(int i = 0;i<result.size();i++)
            if(i == result.size()-1)
                cout << result[i] << endl;
            else cout << result[i] << ' ';
    }
    return 0;
}
