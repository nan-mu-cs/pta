/*Quadratic probing的公式是hash(x) = (x+(-)i*i)%n,i<n题目只要求递增序列*/
#include<iostream>
using namespace std;

bool isprime(int n){
    int i;
    if(n == 1)
        return false;
    for(i = 2;i*i<=n;i++)
        if(n%i == 0)
            break;
    if(i*i<=n)
        return false;
    else return true;
}

int nextprime(int n){
    while(!isprime(n)){
        n++;
    }
    return n;
}
int *a;

int InsertHash(int value,int n){
    int i = 0;
    while(i<n){
        if(a[(value+i*i)%n] == -1){
            a[(value+i*i)%n] = value;
            return (value+i*i)%n;
        }
        i++;
    }
    return -1;
}
int main(){
    int n,m;
    cin >> m >> n;
    m = nextprime(m);
    a = new int [m];
    for(int i = 0;i<m;i++)
        a[i] = -1;
    for(int i = 0;i<n;i++){
        int ele;
        cin >> ele;
        int value = InsertHash(ele,m);
        if(value == -1)
            cout << '-';
        else cout << value;
        if(i == n-1)
            cout << endl;
        else cout << ' ';
    }
    return 0;
}