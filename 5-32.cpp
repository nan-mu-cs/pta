/*贪心法，如果当前站是能到达范围内最便宜的，就加满油，然后到下一个站点，再继续判断
 如果有比他更小的，就加刚好到比他更小站的油*/
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>


using namespace std;

struct Station{
    int dist;
    double price;
};

vector<struct Station> v;

int capacity,dist,distperunit,numofstat;

bool cmp(const struct Station &a,const struct Station &b){
    return a.dist<b.dist;
}
int main(){
    cin >> capacity >> dist >> distperunit >> numofstat;
    struct Station ele;
    for(int i = 0;i<numofstat;i++){
        cin >> ele.price >> ele.dist;
        v.push_back(ele);
    }
    sort(v.begin(),v.end(),cmp);
    double rundist,cost,remain;
    rundist = cost = remain = 0;
    int i = 0;
    while(rundist<dist||i<numofstat){
        if(rundist<v[i].dist)
            break;
        double availdist = capacity*distperunit;
        double price = v[i].price;
        int idx = i;
        int j;
        for(j = i+1;j<numofstat&&availdist+rundist>=v[j].dist;j++)
            if(v[j].price<v[i].price)
            {
                idx = j;
                break;
            }
        if(idx == i){
            if(rundist+availdist>=dist||i == numofstat-1){
                if(rundist+availdist>=dist){
                    cost += (dist - rundist)*1.0/distperunit*price - remain*price;
                    rundist = dist;
                }
                else rundist += availdist;
                break;
            }
            else if(rundist+availdist>v[i+1].dist){
                cost += (capacity - remain)*price;
                remain = capacity - (v[i+1].dist - v[i].dist)*1.0/distperunit;
                rundist = v[i+1].dist;
                i++;
            }
            else {
                rundist += availdist;
                break;
            }
        }
        else {
            if(remain*distperunit<v[idx].dist - v[i].dist){
                cost += (v[idx].dist - v[i].dist)*1.0/distperunit*price - remain*price;
                remain = 0;
                rundist = v[idx].dist;
            }
            else {
                remain -= (v[idx].dist - v[i].dist)*1.0/distperunit;
                rundist = v[idx].dist;
            }
            i = idx;
        }
    }
    if(rundist == dist)
        printf("%.2f\n",cost);
    else printf("The maximum travel distance = %.2f\n",rundist);
    return 0;
}