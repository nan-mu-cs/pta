/*所有小于该数的数要么在stack里面要么已经出去，否则要进栈*/
#include <iostream>
#include <stack>
#define SIZE 1001

using namespace std;
int a[SIZE],b[SIZE];

int main(){
    int SizeofArr,SizeofStack,query;
    cin >> SizeofStack >> SizeofArr >> query;
    while(query--){
        int i = 0;
        for(i = 1;i<=SizeofArr;i++){
            cin >> a[i];
            b[i] = 0;
        }
        i = 1;
        stack<int> s;
        while(i<SizeofArr){
            if(a[i] - i>SizeofStack)
                break;
            if(b[a[i]] == 1&&s.top() == a[i]){
                s.pop();
                b[a[i]] = 2;
                i++;
                continue;
            }
            else if(b[a[i]] == 1)
                break;
            for(int j = 1;j<a[i];j++)
                if(b[j] == 0){
                    s.push(j);
                    b[j] = 1;
                }
            if(s.size()>=SizeofStack)
                break;
            b[a[i]] = 2;
            i++;
        }
        if(i<SizeofArr)
            cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}