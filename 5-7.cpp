#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#define SIZE 1001
using namespace std;
struct tree{
    int left,right;
}node[SIZE];
vector<int> v,result;
int n;

int BuildTree(int begin,int end){
    if(begin>end)
        return -1;
    if(begin == end){
        node[begin].right = node[begin].left = -1;
        return begin;
    }
    int num = end - begin + 1;
    int height = 0;
    while(num>=0){
        num -= pow(2,height);
        height++;
    }
    if(num<0)
        num += pow(2, height-1);
    int mid;
    mid = (end - begin+ 1 - num)/2;
    if(num>pow(2,height-2))
        num = pow(2,height-2);
    mid += begin;
    node[mid].left = BuildTree(begin, mid-1);
    node[mid].right = BuildTree(mid+1, end);
    return mid;
}

void levelorder(int s){
    queue<int> q;
    q.push(s);
    while(q.size()){
        int index = q.front();
        q.pop();
        result.push_back(v[index]);
        if(node[index].left!=-1)
            q.push(node[index].left);
        if(node[index].right!=-1)
            q.push(node[index].right);
    }
}
int main(){
    cin >> n;
    int value;
    for(int i = 0;i<n;i++){
        cin >> value;
        v.push_back(value);
    }
    sort(v.begin(),v.end());
    int s = BuildTree(0,n-1);
    levelorder(s);
    for(int i = 0;i<result.size();i++)
        if(i == result.size()-1)
            cout << result[i] << endl;
        else cout << result[i] << ' ';
    return 0;
}