/*注意j能托i办的前提条件是j到来时，i正在办自己或者朋友的业务*/
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#define PSIZE 10001
#define SSIZE 101
using namespace  std;
int visit[SSIZE];
set<string> friendset[SSIZE];
map<string,int> pindex;
struct Person{
    int come,cost,visit;
    string name;
} customer[PSIZE];

int n,m;
vector<int> resultset;
int main(){
    cin >> n >> m;
    for(int i = 0;i<m;i++){
        int num;
        cin >> num;
        string name;
        for(int j = 0;j<num;j++)
        {
            cin >> name;
            friendset[i].insert(name);
        }
    }
    for(int i = 0;i<n;i++){
        cin >> customer[i].name >> customer[i].come >> customer[i].cost;
        if(customer[i].cost>60)
            customer[i].cost = 60;
        customer[i].visit = 0;
        pindex[customer[i].name] = i;
    }
    int i = 0;
    int totaltime = 0,avail = 0;
    for(i=0;i<n;i++)
        if(!customer[i].visit){
            customer[i].visit = 1;
            totaltime += (avail - customer[i].come)>0?avail - customer[i].come:0;
            int serve = customer[i].come > avail ? customer[i].come:avail;
            avail = serve + customer[i].cost;
            resultset.push_back(i);
            for(int j = 0;j<m;j++)
                if(friendset[j].find(customer[i].name)!=friendset[j].end()){
                    set<string>::iterator it;
                    vector<int> waiting;
                    for(it = friendset[j].begin();it!=friendset[j].end();it++)
                        if((*it)!=customer[i].name&&!customer[pindex[*it]].visit)
                            waiting.push_back(pindex[(*it)]);
                    sort(waiting.begin(),waiting.end());
                    for(int k = 0;k<waiting.size();k++)
                        if(!customer[waiting[k]].visit){
                            
                        int idx = waiting[k];
                        if(customer[idx].come>avail)
                            break;
                        customer[idx].visit = 1;
                        resultset.push_back(idx);
                        totaltime += (avail - customer[idx].come)>0?avail - customer[idx].come:0;
                        int serve = customer[idx].come > avail ? customer[idx].come:avail;
                        avail = serve + customer[idx].cost;
                    }
                }
        }
    for(int i = 0;i<resultset.size();i++)
        cout << customer[resultset[i]].name << endl;
    printf("%.1f\n",totaltime*1.0/n);
    return 0;
}