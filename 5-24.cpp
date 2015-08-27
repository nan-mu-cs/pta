/*数组用sort用自己写的比较大小的函数会出现段错误，不知道是因为什么*/
#include <iostream>
#include <vector>
#include <algorithm>
#define SIZE 100005
#define MSIZE 105
using namespace std;
int graph[SIZE][MSIZE];
int arr[SIZE],dp[MSIZE];
vector<int>result;
int n,m;

bool CountValue(){
    for(int i = 0;i<=m;i++)
        dp[i] = 0;
    dp[0] = 1;
    for(int i = 1;i<=n;i++)
        for(int j = m;j>=arr[i];j--)
            if(dp[j-arr[i]]){
                dp[j] = 1;
                graph[i][j] = 1;
            }
    if(dp[m] == 0)
        return false;
    int i = n,j = m;
    while(i&&j){
        if(graph[i][j]){
            result.push_back(arr[i]);
            j -= arr[i];
            i--;
        }
        else i--;
    }
    return true;
}

int main(){
    cin >> n >> m;
    for(int i = 1;i<=n;i++)
        cin >> arr[i];
    sort(&arr[1],&arr[n+1],greater<int>());
    if(CountValue()){
        for(int i = 0;i<result.size();i++)
        {
            if(i == result.size()-1)
                cout << result[i] << endl;
            else cout << result[i] << ' ';
        }
    }
    else cout << "No Solution" << endl;
    return 0;
}