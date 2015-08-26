#include <iostream>
#include <stdio.h>
#include <vector>
#define SIZE 100000
using namespace std;
vector<int> v;
int idx[SIZE];
void swamp(int &a,int &b){
    int tmp = a;
    a = b;
    b = tmp;
}
int main(){
    int n;
    cin >> n;
    int ele;
    int pos;
    for(int i = 0;i<n;i++){
        //cin >> ele;
        scanf("%d",&ele);
        if(ele == 0)
            pos = i;
        v.push_back(ele);
        idx[ele] = i;
    }
    int sum = 0;
    int flag = 1;
    while(1){
        if(pos == 0){
            int index = -1;
            for(int i = flag;i<n;i++)
                if(v[i]!=i){
                    index = i;
                    break;
                }
            if(index == -1)
                break;
            swamp(v[pos],v[index]);
            sum++;
            idx[v[pos]] = 0;
            idx[0] = index;
            pos = index;
            flag = index+1;
        }
        while(pos){
            v[pos] = v[idx[pos]];
            int tmp = pos;
            pos = idx[pos];
            v[pos] = 0;
            idx[tmp] = tmp;
            sum++;
        }
    }
    cout << sum << endl;
    return 0;
}