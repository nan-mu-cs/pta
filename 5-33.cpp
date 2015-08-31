#include <iostream>
#include <map>
#include <vector>
#define SIZE 1000
#define INF 0x7fffffff

using namespace std;

int graph[SIZE][SIZE];
int f[SIZE][SIZE],r[SIZE][SIZE];
bool visit[SIZE];
vector<int> node[SIZE];
vector<pair<int, int> > ed,item;
map<string,int> point;
int mincap = INF;
int numofpoint = 0;
int cap =  0;
bool DFS(int s){
    visit[s] = true;
    if(s == 1)
        return true;
    int i;
    for(i = 0;i<node[s].size();i++)
        if(!visit[node[s][i]]){
            int v = node[s][i];
            if(graph[s][v] - f[s][v]+f[v][s]>0)
            {
                visit[v] = true;
                item.push_back(make_pair(s, v));
                if(graph[s][v] - f[s][v]+f[v][s]<mincap)
                    mincap = graph[s][v] - f[s][v]+f[v][s];
                if(DFS(v))
                    break;
            }
        }
    if(i<node[s].size())
        return true;
    else return false;
}
int main(){
    string source,dist;
    int edage;
    cin >> source >> dist >> edage;
    point[source] = 0;
    point[dist] = 1;
    numofpoint = 2;
    int capacity;
    for(int i = 0;i<edage;i++){
        cin >> source >> dist >> capacity;
        int x,y;
        if(point.find(source) == point.end())
        {
            point[source] = numofpoint;
            x = numofpoint;
            numofpoint++;
        }
        else x = point[source];
        if(point.find(dist) == point.end()){
            point[dist] = numofpoint;
            y = numofpoint;
            numofpoint++;
        }
        else y = point[dist];
        graph[x][y] = capacity;
        node[x].push_back(y);
        node[y].push_back(x);
        ed.push_back(make_pair(x, y));
    }
    while(DFS(0)){
        cap += mincap;
        for(int i = 0;i<item.size();i++)
        {
            int u = item[i].first,v = item[i].second;
            f[u][v] += mincap;
        }
        for(int i = 0;i<numofpoint;i++)
            visit[i] = false;
        mincap = INF;
        item.clear();
    }
    cout << cap << endl;
    return 0;
}