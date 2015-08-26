#include <iostream>
#include <vector>
#include <cmath>
#define SIZE 101

using namespace std;

vector<int> node[SIZE];

bool closetoend[SIZE];
bool visited[SIZE];
struct position{
    int x,y;
} poi[SIZE];

int dist(const struct position &a,const struct position &b){
    return pow(a.x - b.x,2)+pow(a.y - b.y,2);
}

bool dfs(int s){
    if(closetoend[s])
        return true;
    visited[s] = true;
    int i;
    for(i = 0;i<node[s].size();i++)
        if(!visited[node[s][i]])
            if(dfs(node[s][i]))
                break;
    if(i<node[s].size())
        return true;
    else return false;
}

int main(){
    int n,dis;
    cin >> n >> dis;
    poi[0].x = poi[0].y = 0;
    for(int i = 0;i<=n;i++){
        visited[i] = false;
        closetoend[i] = false;
    }
    for(int i = 1;i<=n;i++){
        cin >> poi[i].x >> poi[i].y;
        for(int j = 1;j<i;j++)
            if(dist(poi[i],poi[j])<=dis*dis)
            {
                node[i].push_back(j);
                node[j].push_back(i);
            }
        if(dist(poi[0],poi[i])<=pow(dis+15,2))
            node[0].push_back(i);
        if(pow(50-poi[i].x,2)<=dis*dis){
            closetoend[i] = true;
            continue;
        }
        if(pow(poi[i].x+50,2)<=dis*dis){
            closetoend[i] = true;
            continue;
        }
        if(pow(50-poi[i].y,2)<=dis*dis){
            closetoend[i] = true;
            continue;
        }
        if(pow(poi[i].y+50,2)<=dis*dis){
            closetoend[i] = true;
            continue;
        }
    }
    if(dfs(0))
        cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}

