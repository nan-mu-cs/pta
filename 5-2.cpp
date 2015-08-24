/*会有不止一条链表，只需要处理开头标好的那个*/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stack>
#include <vector>

using namespace std;

struct lst{
    int addr,data,next;
};

vector<struct lst> input,result;

int main(){
    int startaddr,n,k;
    cin >> startaddr >> n >> k;
    struct lst node;
    for(int i = 0;i<n;i++){
        scanf("%d%d%d",&node.addr,&node.data,&node.next);
        input.push_back(node);
    }
    stack<struct lst> s1;
    while(startaddr!=-1){
        for(int i = 0;i<n;i++)
            if(input[i].addr == startaddr){
                startaddr = input[i].next;
                s1.push(input[i]);
                if(s1.size() == k){
                    while(s1.size()){
                        struct lst node = s1.top();
                        s1.pop();
                        result.push_back(node);
                    }
                }
            }
    }
    stack<struct lst> s2;
    while(s1.size()){
        struct lst node = s1.top();
        s1.pop();
        s2.push(node);
    }
    while(s2.size()){
        struct lst node = s2.top();
        s2.pop();
        result.push_back(node);
    }
    int size = result.size();
    for(int i = 0;i<size;i++){
        cout << setfill('0') << setw(5) <<result[i].addr << ' ' << result[i].data;
        if(i == size-1)
            cout << ' ' << -1 << endl;
        else cout << ' ' << setfill('0') << setw(5) << result[i+1].addr << endl;
    }
    return 0;
}