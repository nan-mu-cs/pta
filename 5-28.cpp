#include <iostream>
#include <vector>
#include <stack>
#define SIZE 10
#define INF 0x7fffffff
using namespace std;

stack<int>item;
vector<int>result;
struct Question{
    string title;
    int solvetime,debugtime;
} quest[SIZE];

int gametime,readtime,numofques,numofsolve,usetime;
bool visited[SIZE];

void ArrangeQuest(int idx,int solved,int userealtime,int usegametime){
    int addtime = 0;
    userealtime += quest[idx].solvetime;
    int hour = userealtime/60;
    if(userealtime%60 == 0&&hour)
        hour--;
    userealtime += hour *quest[idx].debugtime;
    addtime = hour*20;
    if(userealtime>=gametime){
        if(numofsolve<solved||(numofsolve == solved&&usegametime<usetime)){
            numofsolve = solved;
            stack<int> tmp = item;
            result.clear();
            while(tmp.size()){
                result.push_back(tmp.top());
                tmp.pop();
            }
            usetime = usegametime;
        }
        return ;
    }
    usegametime += userealtime + addtime;
    solved++;
    item.push(idx);
    visited[idx] = true;
    if(solved == numofques){
        if(numofsolve<solved||usegametime<usetime){
            numofsolve = solved;
            stack<int> tmp = item;
            result.clear();
            while(tmp.size()){
                result.push_back(tmp.top());
                tmp.pop();
            }
            usetime = usegametime;
        }
        item.pop();
        visited[idx] = false;
        return ;
    }
    for(int i = 0;i<numofques;i++)
        if(!visited[i])
            ArrangeQuest(i, solved, userealtime, usegametime);
    item.pop();
    visited[idx] = false;
}
int main(){
    while(cin >> gametime){
        if(gametime<0)
            break;
        gametime *= 60;
        cin >> numofques >> readtime;
        for(int i = 0;i<numofques;i++)
            cin >> quest[i].title >> quest[i].solvetime >> quest[i].debugtime;
        numofsolve = 0;
        usetime = INF;
        result.clear();
        for(int i = 0;i<numofques;i++)
            visited[i] = false;
        for(int i = 0;i<numofques;i++){
            ArrangeQuest(i,0,readtime,0);
        }
        /*
        while(result.size()){
            idx = result.top();
            result.pop();
            rresult.push_back(idx);
        }*/
        cout << "Total Time = " << usetime << endl;
        for(int i = result.size()-1;i>=0;i--)
            cout << quest[result[i]].title << endl;
    }
    return 0;
}