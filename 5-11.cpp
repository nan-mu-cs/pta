/*回溯时访问某个元素时visit设为true结束之后设为false*/
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>
#define SIZE 101

using namespace std;

vector<int> node[SIZE],result;
stack<int> st;
bool closetoend[SIZE];
bool visited[SIZE];
struct position{
    double x,y;
} poi[SIZE];

double dist(const struct position &a,const struct position &b){
    return pow(a.x - b.x,2)+pow(a.y - b.y,2);
}

bool cmp(const int &a,const int &b){
    return dist(poi[a],poi[0])<=dist(poi[b],poi[0]);
}

bool dfs(int s){
    if(closetoend[s]){
        if((result.size()&&st.size()<result.size())||result.empty()){
            stack<int>newst = st;
            int index;
            result.clear();
            while(newst.size()){
                index = newst.top();
                newst.pop();
                result.push_back(index);
            }
        }
        return true;
    }
    //visited[s] = true;
    int i;
    bool flag = false;
    for(i = 0;i<node[s].size();i++)
        if(!visited[node[s][i]]){
            st.push(node[s][i]);
            visited[node[s][i]] = true;
            if(dfs(node[s][i]))
                flag = true;
            st.pop();
            visited[node[s][i]] = false;
        }
    return flag;
}

int main(){
    int n;
    double dis;
    cin >> n >> dis;
    poi[0].x = poi[0].y = 0;
    for(int i = 0;i<=n;i++){
        visited[i] = false;
        closetoend[i] = false;
    }
    for(int i = 1;i<=n;i++){
        cin >> poi[i].x >> poi[i].y;
        if(dist(poi[i],poi[0])<=7.5*7.5)
            continue;
        for(int j = 1;j<i;j++)
            if(dist(poi[i],poi[j])<=dis*dis)
            {
                node[i].push_back(j);
                node[j].push_back(i);
            }
        if(dist(poi[0],poi[i])<=pow(dis+7.5,2))
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
    sort(node[0].begin(),node[0].end(),cmp);
    visited[0] = true;
    if(dis>=42.5)
        cout << 1 << endl;
    else if(dfs(0)){
        cout << result.size()+1 << endl;
        for(int i = result.size()-1;i>=0;i--)
            cout << poi[result[i]].x << ' ' << poi[result[i]].y << endl;
    }
    else cout << 0 << endl;
    return 0;
}

