/*简单背包dp[i][j],前i件在ddl j前的最大收益,
 dp[i][j] = max(dp[i-1][j],dp[i-1][j-lasttime[i]]+profit[i]+)*/
#include <iostream>
#include <vector>
#include <algorithm>
#define SIZE 5000

using namespace  std;

bool visit[SIZE];
struct Project{
    int deadline,profit,times;
};

bool cmp(const struct Project &a,const struct Project &b){
    if(a.deadline == b.deadline)
        if(a.profit == b.profit)
            return a.times<b.times;
        else return a.profit>b.profit;
    else return a.deadline < b.deadline;
}
vector<struct Project> project;
int maxprofit,n,day;
int dp[SIZE];
int main(){
    cin >> n;
    struct Project ele;
    int largeddl = 0;
    for(int i = 0;i<n;i++){
        //cin >> ele.profit >> ele.times >> ele.deadline;
        scanf("%d%d%d",&ele.profit,&ele.times,&ele.deadline);
        project.push_back(ele);
        if(ele.deadline>largeddl)
            largeddl = ele.deadline;
    }
    sort(project.begin(),project.end(),cmp);
    maxprofit = 0;
    for(int i = 1;i<=n;i++)
        for(int j = project[i-1].deadline;j>=0;j--)
            if(j-project[i-1].times>=0&&dp[j-project[i-1].times]+project[i-1].profit>dp[j])
                dp[j] = dp[j-project[i-1].times]+project[i-1].profit;
    for(int i = 0;i<=largeddl;i++)
        if(dp[i]>maxprofit)
            maxprofit = dp[i];
    cout << maxprofit << endl;
    return 0;
}