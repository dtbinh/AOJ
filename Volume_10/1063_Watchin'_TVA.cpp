
#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <deque>
#include <bitset>
#include <list>
#include <cctype>
#include <utility>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
//Watchin' TVA
class Program{
public:
    int time;
    string name;
    Program(int _time, string _name) : time(_time), name(_name) {}
 
    bool operator < (const Program& p) const{
        return time < p.time;
    }
};
 
int main(){
    int N,P;
     
 
    while(~scanf("%d",&N)){
        if(N==0) break;
        map<int,vector<Program> > PRO;
        map<string,bool> FAV;
 
        for(int i=0;i<N;i++){
            string name;
            int day;
            int time;
            cin >> name >> day >> time;
            int m = time % 100;
            int h = time / 100;
            int total = h * 60 + m;
            PRO[day].push_back(Program(total,name));
        }
        scanf("%d",&P);
        for(int i=0;i<P;i++){
            string name;
            cin >> name;
            FAV[name] = true;
        }
 
        bool failed = false;
        int res = 0;
        for(map<int,vector<Program> >::iterator it = PRO.begin(); it != PRO.end(); it++){
            bool reserve[10000];
            memset(reserve,0,sizeof(reserve));
            sort(it->second.begin(),it->second.end());
            for(int i=0;i< it->second.size(); i++){
                if(FAV.find(it->second[i].name) != FAV.end()){
                    for(int j=it->second[i].time; j<it->second[i].time+30;j++){
                        if(reserve[j]){
                            failed = true;
                            goto next;
                        }
                        reserve[j]=true;
                    }
                    res++;
                }
            }
 
            for(int i=0;i< it->second.size(); i++){
                if(FAV.find(it->second[i].name) == FAV.end()){
                    bool tmp[10000];
                    memcpy(tmp,reserve,sizeof(reserve));
 
                    for(int j=it->second[i].time; j<it->second[i].time+30;j++){
                        if(tmp[j]){
                            goto cancel;
                        }
                        tmp[j]=true;
                    }
                    memcpy(reserve,tmp,sizeof(tmp));
                    res++;
                }       
cancel:;
            }
        }
next:;
 
        if(failed){
            printf("%d\n",-1);
        }
        else{
            printf("%d\n",res);
        }
    }
}

