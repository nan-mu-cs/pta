#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct person{
    char name[10];
    int wealth,age;
    bool operator()(const struct person &a,const struct person &b){
        if(a.wealth == b.wealth)
            if(a.age == b.age)
                return strcmp(a.name,b.name)>0;
            else return a.age>b.age;
        else return a.wealth<b.wealth;
    }
};

bool cmp(const struct person &a,const struct person &b){
    if(a.age == b.age)
        if(a.wealth == b.wealth)
            return strcmp(a.name,b.name)<0;
        else return a.wealth>b.wealth;
    else return a.age<b.age;
}

map<int,int> agelist;
map<int,vector<struct person>> richer;
vector<struct person> people;
map<int,int> remain;
int main(){
    int n,times;
    int minage,largeage;
    minage = 201;
    largeage = -1;
    //cin >> n >> times;
    scanf("%d%d",&n,&times);
    struct person ele;
    for(int i = 0;i<n;i++){
        scanf("%s%d%d",ele.name,&ele.age,&ele.wealth);
        people.push_back(ele);
        if(ele.age<minage)
            minage = ele.age;
        if(ele.age>largeage)
            largeage = ele.age;
    }
    sort(people.begin(),people.end(),cmp);
    for(int i = 0;i<people.size();i++)
    {
        richer[people[i].age].push_back(people[i]);
        if(i == people.size()-1)
            agelist[people[i].age] = largeage+1;
        else agelist[people[i].age] = people[i+1].age;
    }
    int count = 1;
    while(times--){
        printf("Case #%d:\n",count++);
        int min,max,num;
        scanf("%d%d%d",&num,&min,&max);
        priority_queue<struct person,vector<struct person>,struct person> result;
        if(min<minage)
            min = minage;
        if(max>largeage)
            max = largeage;
        while(agelist.find(min) == agelist.end())
            min++;
               while(min<=max){
            remain[min] = 0;
            result.push(richer[min][0]);
            remain[min] = 1;
            min = agelist[min];
        }
        int count = 0;
        while(num--&&result.size()){
            ele = result.top();
            result.pop();
            if(remain[ele.age] < richer[ele.age].size()){
                result.push(richer[ele.age][remain[ele.age]]);
                remain[ele.age]++;
            }
            printf("%s %d %d\n",ele.name,ele.age,ele.wealth);
            count++;
        }
        if(count == 0)
            printf("None\n");
    }
    return 0;
}