/*topsort 负数代表空！！我一直按-1来做，查了好久%>_<%*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#define SIZE 1001
using namespace std;

map<int,vector<int> > parent;
vector<int> startset,endset;
map<int,int> child;
vector<int> result;
priority_queue<int,vector<int>,std::greater<int>> pq;
int hsh[SIZE];
int n;
int largest = -1;
void Topsort(int s){
    if(s<largest)
        result.push_back(s);
    for(int i = 0;i<parent[s].size();i++){
        int ele = parent[s][i];
        child[ele]--;
        if(child[ele] == 0)
            pq.push(ele);
    }
    int idx;
    while(pq.size()){
        idx = pq.top();
        pq.pop();
        Topsort(idx);
    }
}

int main(){
    cin >> n;
    for(int i = 0;i<n;i++){
        cin >> hsh[i];
        if(hsh[i] < 0)
            continue;
        child[hsh[i]] = 0;
        parent[hsh[i]] = {};
    }
    for(int i = 0;i<n;i++){
        int ele = hsh[i];
        if(ele <0)
            continue;
        int j = i;
        int count = 0;
        while(j!=ele%n){
            j--;
            if(j<0)
                j = n-1;
            parent[hsh[j]].push_back(ele);
            child[ele]++;
        }
    }
    map<int,vector<int> >::iterator it;
    for(it = parent.begin();it!=parent.end();it++){
        if(it->second.size() == 0)
            endset.push_back(it->first);
        if(it->first>largest)
            largest = it->first;
    }
    largest++;
    map<int,int>::iterator cit;
    for(cit = child.begin();cit!=child.end();cit++)
        if(cit->second == 0){
            startset.push_back(cit->first);
        }
    for(int i = 0;i<startset.size();i++)
        child[startset[i]]++;
    parent[largest] = startset;
    parent[largest+1] = {};
    child[largest+1] = endset.size();
    child[largest] = 0;
    Topsort(largest);
    for(int i = 0;i<result.size();i++)
        if(i == result.size()-1)
            cout << result[i] << endl;
        else cout << result[i] << ' ';
    return 0;
}