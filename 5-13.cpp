#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> orig;
vector<int> result,target;

bool InsertSort(){
    bool flag = false;
    vector<int> item = orig;
    for(int i = 1;i<item.size();i++){
        int j = i;
        int tmp = item[i];
        for(;j>=1;j--)
            if(tmp<item[j-1])
                item[j] = item[j-1];
            else break;
        item[j] = tmp;
        if(flag){
            result = item;
            break;
        }
        if(item == target)
            flag = true;
    }
    return flag;
}

void MergeSort(){
    vector<int>item = orig;
    bool flag = false;
    for(int i = 1;2*i<=item.size();i *= 2){
        int group = item.size()/(2*i);
        int cnt = group;
        vector<int>::iterator it;
        for(it = item.begin();cnt>0;it+= 2*i,cnt--)
            sort(it,it+2*i);
        int left = item.size() - group*2*i;
        if(left>i)
            sort(it,item.end());
        if(flag){
            result = item;
            break;
        }
        if(item == target)
            flag = true;
    }
}



int main(){
    cin >> n;
    int ele;
    for(int i = 0;i<n;i++){
        cin >> ele;
        orig.push_back(ele);
    }
    for(int i = 0;i<n;i++){
        cin >> ele;
        target.push_back(ele);
    }
    if(InsertSort()){
        cout << "Insertion Sort" << endl;
    }
    else {
        MergeSort();
        cout << "Merge Sort" << endl;
    }
    for(int i = 0;i<result.size();i++)
        if(i == result.size()-1)
            cout << result[i] << endl;
        else cout << result[i] << ' ';
    return 0;
}