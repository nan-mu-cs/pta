/*vip和非vip组成两个队列，然后模拟，先处理vip队列的情况是vip比非vip先到，
 或者两者到时都没有空桌但是viptable先空出来*/
#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
#define SIZE 101
#define INF 0x7fffffff
using namespace std;
struct TPlayer{
    int came,serve,vip,playtime;
};
bool camecmp(const struct TPlayer &a,const struct TPlayer &b){
    return a.came<b.came;
}
bool servecmp(const struct TPlayer &a,const struct TPlayer &b){
    return a.serve<b.serve;
}
vector<struct TPlayer> player,vplayer;
vector<struct TPlayer> presult;
struct Table{
    int avail,num,id,vip;
};

vector<struct Table> table;

int timetosec(const int &hour,const int &minute,const int &sec){
    return hour*3600 + minute*60 + sec;
}

void PrintTime(int sec){
    int hour = sec/3600;
    sec -= hour*3600;
    int minute = sec/60;
    sec -= minute*60;
    printf("%02d:%02d:%02d",hour,minute,sec);
}

int main(){
    int numofplayer;
    scanf("%d",&numofplayer);
    struct TPlayer ele;
    int hour,minute,sec;
    for(int i = 0;i<numofplayer;i++){
        scanf("%d:%d:%d%d%d",&hour,&minute,&sec,&ele.playtime,&ele.vip);
        ele.came = timetosec(hour,minute, sec);
        if(ele.came>=21*3600)
            continue;
        ele.playtime *= 60;
        if(ele.playtime>120*60)
            ele.playtime = 120*60;
        if(ele.vip)
            vplayer.push_back(ele);
        else player.push_back(ele);
    }
    sort(vplayer.begin(),vplayer.end(),camecmp);
    sort(player.begin(),player.end(),camecmp);
    int numoftable,numofvtable;
    scanf("%d%d",&numoftable,&numofvtable);
    struct Table tele;
    for(int i = 0;i<numoftable;i++)
    {
        tele.avail = 8*3600;
        tele.vip = 0;
        tele.num = 0;
        table.push_back(tele);
    }
    for(int i = 0;i<numofvtable;i++){
        int idx ;
        scanf("%d",&idx);
        idx--;
        table[idx].vip = 1;
    }
    int curplayer,curvplayer;
    int curavail,availtable;
    curavail = 8*3600;
    availtable = 0;
    curplayer = curvplayer = 0;
    while(curplayer<player.size()||curvplayer<vplayer.size()){
        int vavail,vidx;
        vavail = INF;
        bool flag = false;
        for(int i = 0;i<numoftable;i++)
            if(vavail>table[i].avail){
                vidx = i;
                vavail = table[i].avail;
            }
            else if(table[i].vip&&vavail == table[i].avail)
            {
                if(flag == false)
                {
                    vidx = i;
                }
                else flag = true;
            }
        if(curvplayer<vplayer.size()&&(curplayer == player.size()
                                       ||(table[vidx].vip&&table[vidx].avail>=vplayer[curvplayer].came)
                                       ||player[curplayer].came>vplayer[curvplayer].came)){
            int idx = 0;
            bool playerearly = true;
            int availtime = table[0].avail;
            for(int i = 0;i<numoftable;i++){
                if(playerearly&&availtime>=table[i].avail){
                    if(table[i].avail<=vplayer[curvplayer].came){
                        if(table[i].vip)
                        {
                            idx = i;
                            break;
                        }
                        else {
                            playerearly = false;
                            idx = i;
                            availtime = vplayer[curvplayer].came;
                        }
                    }
                    else if(availtime>table[i].avail){
                        idx = i;
                        availtime = table[i].avail;
                    }
                }
                else if(playerearly == false&&availtime>=table[i].avail&&table[i].vip){
                    idx = i;
                    break;
                }
            }
            vplayer[curvplayer].serve = table[idx].avail>vplayer[curvplayer].came?table[idx].avail:vplayer[curvplayer].came;
            if(vplayer[curvplayer].serve>=21*3600)
                break;
            table[idx].avail = vplayer[curvplayer].serve + vplayer[curvplayer].playtime;
            table[idx].num++;
            presult.push_back(vplayer[curvplayer]);
            curvplayer++;
        }
        else {
            int idx = -1;
            int availtime = INF;
            for(int i = 0;i<numoftable;i++)
                if(table[i].avail<=player[curplayer].came){
                    idx = i;
                    break;
                }
                else if(availtime>table[i].avail){
                    idx = i;
                    availtime = table[i].avail;
                }
            player[curplayer].serve = table[idx].avail>player[curplayer].came?table[idx].avail:player[curplayer].came;
            if(player[curplayer].serve>=21*3600)
                break;
            table[idx].avail = player[curplayer].serve + player[curplayer].playtime;
            table[idx].num++;
            presult.push_back(player[curplayer]);
            curplayer++;
        }
    }
    sort(presult.begin(),presult.end(),servecmp);
    for(int i = 0;i<presult.size();i++)
        if(presult[i].serve>=21*3600)
            break;
        else {
            PrintTime(presult[i].came);
            putchar(' ');
            PrintTime(presult[i].serve);
            printf(" %d\n",(presult[i].serve - presult[i].came+30)/60);
        }
    for(int i = 0;i<table.size();i++)
        if(i == table.size()-1)
            printf("%d\n",table[i].num);
        else printf("%d ",table[i].num);
    return 0;
}