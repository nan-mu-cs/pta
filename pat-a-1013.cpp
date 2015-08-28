#include <iostream>
#include <vector>
#include <set>
#define SIZE 1001

using namespace std;
vector<int> node[SIZE];
int nodeset[SIZE];
int test[SIZE];
int n,m,times;

int find(int *a,int x){
    int tmp = x;
    while(a[x]!=x)
        x = a[x];
    while(a[tmp]!=x){
        int v = a[tmp];
        a[tmp] = x;
        tmp = v;
    }
    return x;
}
int main(){
    cin >> n >> m >> times;
    for(int i = 0;i<=n;i++)
        nodeset[i] = i;
    int x,y;
    for(int i = 0;i<m;i++){
        cin >> x >> y;
        node[x].push_back(y);
        node[y].push_back(x);
        x = find(nodeset,x);
        y = find(nodeset,y);
        if(x!=y)
            nodeset[x] = y;
    }
    while(times--){
        int city;
        cin >> city;
        int cityset = find(nodeset,city);
        vector<int> st;
        test[city] = city;
        for(int i = 1;i<=n;i++){
            if(i == city)
                continue;
            if(nodeset[i] == cityset){
                st.push_back(i);
                test[i] = i;
            }
            else test[i] = nodeset[i];
        }
        for(int i = 0;i<st.size();i++)
            for(int j = 0;j<node[st[i]].size();j++){
                int x = st[i];
                int y = node[st[i]][j];
                if(y == city)
                    continue;
                x = find(test,x);
                y = find(test,y);
                if(x!=y)
                    test[y] = x;
            }
        int result = 0;
        for(int i = 1;i<=n;i++)
            if(test[i] == i&&i!=city)
                result++;
        cout << result-1<< endl;
    }
    return 0;
}