
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
 
class Data{
public:
    int wrong[11];
    bool correct[11];
    int penalty;
    Data(){
        memset(wrong,0,sizeof(wrong));
        memset(correct,0,sizeof(correct));
        penalty = 0;
    }
};
 
class Team{
public:
    int solved;
    int penalty;
    int tid;
    Team (int _sol,int _pen,int _tid) : solved(_sol),penalty(_pen),tid(_tid) {}
    bool operator<(const Team& t) const{
        if(solved != t.solved){
            return solved > t.solved;
        }
        else if(solved == t.solved && penalty != t.penalty){
            return penalty < t.penalty;
        }
        else{
            return tid < t.tid;
        }
    }
};
 
int main(){
    int T,P,R;
    while(~scanf("%d %d %d",&T,&P,&R)){
        if(T==0 && P==0 && R==0) break;
        map<int,Data> status;
        for(int i=1;i<=T;i++){
            status[i];
        }
        for(int i=0;i<R;i++){
            int tID;
            int pID;
            int time;
            string str;
            cin >> tID >> pID >> time >> str;
            if(str == "CORRECT"){
                status[tID].correct[pID] = true;
                status[tID].penalty += status[tID].wrong[pID] * 1200 + time; 
            }
            else{
                if(!status[tID].correct[pID]) status[tID].wrong[pID]++;
            }
        }
 
        vector<Team> teams;
 
        for(map<int,Data>::iterator it = status.begin(); it != status.end(); it++){
            teams.push_back(Team(count(it->second.correct,it->second.correct + 11,true),it->second.penalty,it->first));
        }
 
        sort(teams.begin(),teams.end());
 
        for(int i=0;i<teams.size();i++){
            printf("%d %d %d\n",teams[i].tid,teams[i].solved,teams[i].penalty);
        }
    }
}

