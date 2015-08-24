#include <iostream>
#define SIZE 10001
using namespace std;
int a[SIZE];

int find(int x){
    int tmp = x;
    while(a[x]!=x)
        x = a[x];
    while(a[tmp]!=x)
    {
        tmp = a[tmp];
        a[tmp] = x;
    }
    return x;
}

int main(){
    int n;
    cin >> n;
    for(int i = 1;i<=n;i++)
        a[i] = i;
    string str;
    while(cin >> str){
        if(str == "S")
            break;
        int x,y;
        cin >> x >> y;
        x = find(x);
        y = find(y);
        if(str == "C")
        {
            if(x == y)
                cout << "yes" << endl;
            else cout << "no" << endl;
        }
        else {
            a[y] = x;
        }
    }
    int part = 0;
    for(int i = 1;i<=n;i++)
        if(a[i] == i)
            part++;
    if(part == 1)
        cout << "The network is connected." << endl;
    else cout << "There are " << part <<" components." << endl;
    return 0;
}