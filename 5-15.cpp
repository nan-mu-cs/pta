#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#define QSIZE 10


using namespace std;

struct person{
    int rank,totalscore,perfect,id,succsub;
    int q[QSIZE];
};

vector<struct person> stu;
vector<struct person> result;
int problem[QSIZE];
int numofusers,numofproblem,numofsub;


bool cmp(const struct person &a,const struct person &b){
    if(a.succsub == b.succsub)
        if(a.totalscore == b.totalscore)
            if(a.perfect == b.perfect)
                return a.id < b.id;
            else return a.perfect>b.perfect;
        else return a.totalscore>b.totalscore;
    else return a.succsub>b.succsub;
}
int main(){
    cin >> numofusers >> numofproblem >> numofsub;
    for(int i = 1;i<=numofproblem;i++)
        cin >> problem[i];
    struct person user;
    for(int i = 1;i<=numofusers;i++){
        user.id = i;
        user.totalscore = user.perfect = user.succsub = 0;
        for(int j = 1;j<=numofproblem;j++)
            user.q[j] = -1;
        stu.push_back(user);
    }
    int id,ques,score;
    for(int i = 1;i<=numofsub;i++){
        cin >> id >> ques >> score;
        id--;
        if(score>stu[id].q[ques]){
            if(score == problem[ques])
                stu[id].perfect++;
            if(stu[id].q[ques] == -1)
                stu[id].totalscore += score;
            else stu[id].totalscore += score - stu[id].q[ques];
            stu[id].q[ques] = score;
        }
        else if(score == -1 &&stu[id].q[ques] == -1)
            stu[id].q[ques] = 0;
        if(score>=0)
            stu[id].succsub = 1;
    }
    sort(stu.begin(),stu.end(),cmp);
    stu[0].rank = 1;
    result.push_back(stu[0]);
    for(int i = 1;i<stu.size();i++){
        if(stu[i].totalscore == stu[i-1].totalscore)
            stu[i].rank = stu[i-1].rank;
        else stu[i].rank = i+1;
        if(stu[i].succsub == 1)
            result.push_back(stu[i]);
    }
    for(int i = 0;i<result.size();i++)
    {
        cout << stu[i].rank << ' '<< setfill('0') << setw(5) << stu[i].id<<' '<<stu[i].totalscore;
        for(int j = 1;j<=numofproblem;j++)
            if(stu[i].q[j]>=0)
                cout << ' '<< stu[i].q[j];
            else cout << " -";
        cout << endl;
    }
    return 0;
}