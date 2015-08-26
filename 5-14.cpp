/*注意heapsort的写法*/
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
void PrecDown(int index,vector<int> &item,int end){
    int tmp;
    int child;
    for(tmp = item[index];2*index + 1<end;index = child){
        child = 2*index+1;
        if(child!=end-1&&item[child]<item[child+1])
            child++;
        if(tmp<item[child])
            item[index] = item[child];
        else break;
    }
    item[index] = tmp;
}
void HeapSort(){
    bool flag = false;
    vector<int> item = orig;
    for(int i = item.size()/2;i>=0;i--)
        PrecDown(i, item,item.size());
    for(int i = item.size()-1;i>0;i--){
        if(item == target)
            flag = true;
        int tmp = item[0];
        item[0] = item[i];
        item[i] = tmp;
        PrecDown(0, item,i);
        if(flag == true){
            result = item;
            break;
        }
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
        HeapSort();
        cout << "Heap Sort" << endl;
    }
    for(int i = 0;i<result.size();i++)
        if(i == result.size()-1)
            cout << result[i] << endl;
        else cout << result[i] << ' ';
    return 0;
}