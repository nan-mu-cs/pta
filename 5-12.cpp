/*关键路径，先用topsort求出每个点的最早时间ev，
 然后利用逆topsort求出每个点的最迟时间ltv，然后找到一条关键路径求时间，
 可能有多条关键路径，可能起始和终止点不止一个，需要添加一个伪起点和伪终点*/
#include<iostream>
#include<vector>
#include<stack>
#define SIZE 101
using namespace std;
int graph[SIZE][SIZE];
vector<int> parent[SIZE],child[SIZE];
vector<int> startset,endset;
vector<pair<int,int> > edges;
int ev[SIZE],ltv[SIZE],ch[SIZE],pare[SIZE];
bool visited[SIZE];
int n,m;
int start,ed;
stack<int>st;

bool TopSort(int s){
    visited[s] = true;
    st.push(s);
    for(int i = 0;i<parent[s].size();i++){
        ch[parent[s][i]]--;
        if(ev[s]+graph[s][parent[s][i]]>ev[parent[s][i]])
            ev[parent[s][i]] = ev[s]+graph[s][parent[s][i]];
    }
    for(int i = 0;i<=n+1;i++)
        if(visited[i] == false&&ch[i] == 0)
            TopSort(i);
    if(st.size() == n+2)
        return true;
    else return false;
}
void ReTopSort(){
    st.top();
    st.pop();
    while(st.size()){
        int index = st.top();
        st.pop();
        for(int i = 0;i<parent[index].size();i++)
            if(ltv[index]>ltv[parent[index][i]] - graph[index][parent[index][i]])
                ltv[index] = ltv[parent[index][i]] - graph[index][parent[index][i]];
    }
}
int sum = 0;
void KeyPath(int s){
    if(s == ed)
        return ;
    for(int i = 0;i<parent[s].size();i++){
        int p = parent[s][i];
        int ee = ev[s],lte = ltv[p] - graph[s][p];
        if(ee == lte){
            sum += graph[s][p];
            KeyPath(p);
            break;
        }
    }
}
int main(){
    cin >> n >> m;
    int x,y,le;
    for(int i = 0;i<m;i++){
        cin >> x >> y >> le;
        graph[x][y] = le;
        ch[y]++;
        pare[x]++;
        parent[x].push_back(y);
        child[y].push_back(x);
    }
    for(int i = 0;i<n;i++)
        if(child[i].size() == 0){
            startset.push_back(i);
        }
    start = n;
    ch[start] = 0;
    parent[start] = startset;
    for(int i = 0;i<startset.size();i++){
        ch[startset[i]]++;
    }
    for(int i = 0;i<n;i++)
        if(parent[i].size() == 0){
            endset.push_back(i);
        }
    ed = n+1;
    ch[ed] = endset.size();
    for(int i = 0;i<endset.size();i++){
        parent[endset[i]].push_back(ed);
    }
    for(int i = 0;i<=n+1;i++)
        ev[i] = 0;
    if(TopSort(start)){
        for(int i = 0;i<=n+1;i++)
            ltv[i] = ev[ed];
        ReTopSort();
        KeyPath(start);
        cout << sum << endl;
    }
    else cout << "Impossible" << endl;
    return 0;
}