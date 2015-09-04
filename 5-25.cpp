#include<iostream>
#include<vector>
#define SIZE 101
#define INF 0x7fffffff
using namespace std;
vector<pair<int,int> > node[SIZE];
int dist[SIZE],visit[SIZE];

int n,m,smaxlength,maxlength,minindex;


void Dij(int s){
    dist[s] = 0;
    for(int i = 0;i<n;i++){
        int u,minlen;
        minlen = INF;
        u = -1;
        for(int j = 0;j<n;j++)
            if(!visit[j]&&minlen>dist[j]){
                u = j;
                minlen = dist[j];
            }
        if(u == -1)
            break;
        visit[u] = 1;
        for(int j = 0;j<node[u].size();j++){
            int v = node[u][j].first;
            int d = node[u][j].second;
            if(!visit[v]&&dist[v]>dist[u]+d)
                dist[v] = dist[u]+d;
        }
    }
}
int main(){
    cin >> n >> m;
    int x,y,d;
    for(int i = 0;i<m;i++){
        cin >> x >> y >> d;
        x--;
        y--;
        node[x].push_back(make_pair(y, d));
        node[y].push_back(make_pair(x, d));
    }
    maxlength = INF;
    minindex = -1;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++)
        {
            dist[j] = INF;
            visit[j] = 0;
        }
        smaxlength = 0;
        Dij(i);
        for(int j = 0;j<n;j++)
            if(smaxlength<dist[j])
                smaxlength = dist[j];
        if(smaxlength<maxlength){
            minindex = i;
            maxlength = smaxlength;
        }
    }
    if(maxlength == INF)
        cout << 0 << endl;
    else cout << minindex+1 << ' ' << maxlength << endl;
    return 0;
}