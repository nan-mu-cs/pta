#include <iostream>
#define SIZE 10001
using namespace std;

int a[SIZE];

int main(){
    int n;
    cin >> n;
    for(int i = 0;i<n;i++)
        cin >> a[i];
    int maxstart = a[0],maxend = a[n-1],max = -1,sum = 0;
    int start = 0,end = 0;
    for(int i = 0;i<n;i++)
    {
        if(sum+a[i]>=0)
        {
            sum += a[i];
            end++;
        }
        else {
            sum = 0;
            start = end = i+1;
        }
        if(sum>max&&(end - start)){
            max = sum;
            maxstart = a[start];
            maxend = a[end-1];
        }
    }
    if (max == -1)
        max = 0;
    cout << max << " " <<maxstart << " " << maxend << endl;
    return 0;
}
