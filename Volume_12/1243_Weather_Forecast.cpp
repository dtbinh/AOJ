#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
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
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
static const int tx[] = {-8,-4,-2,-1,1,2,4,8,0};

class State {
public:
  long long int no_rainny_summary;
  int dx;
  State(int _no_rainny_days[16],int _dx){
    dx = _dx;
    long long int digit = 1;
    no_rainny_summary = 0;
    for(int i=0;i<16;i++){
      no_rainny_summary += (long long int)_no_rainny_days[i] * digit;
      digit *= 10LL;
    }
  }
  bool operator <(const State& s) const{
    if(no_rainny_summary == s.no_rainny_summary){
      return dx < s.dx;
    }
    else{
      return no_rainny_summary < s.no_rainny_summary;
    }
  }
  bool operator >(const State& s) const{
    if(no_rainny_summary == s.no_rainny_summary){
      return dx > s.dx;
    }
    else{
      return no_rainny_summary > s.no_rainny_summary;
    }
  }
  bool operator ==(const State& s) const{
    return (no_rainny_summary == s.no_rainny_summary
	    && dx == s.dx);
  }
};

set<State> visited[400];
int stage[400];
int no_rainny_days[16];

void print_stage(int num){
  for(int y=0;y<4;y++){
    for(int x=0;x<4;x++){
      printf("%d ",num & (1<<(y*4+x)) ? 1 : 0);
    }
    printf("\n");
  }
  printf("\n");
}

void print_rain(){
  for(int y=0;y<4;y++){
    for(int x=0;x<4;x++){
      printf("%d ",no_rainny_days[y*4+x]);
    }
    printf("\n");
  }
  printf("\n");
}

int rain(int bits){
  for(int i=0;i<16;i++){
    if(bits & (1<<i)){
      no_rainny_days[i] = 0;
    }
    else{
      no_rainny_days[i]++;
    }
  }
}

bool check(){
  for(int i=0;i<16;i++){
    if(no_rainny_days[i] >= 7) return false;
  }
  return true;
}

int make_cloud(int cloud_pos){
  int cloud = 0; 
  cloud |= (1<<cloud_pos);
  cloud |= (1<<(cloud_pos+1));
  cloud |= (1<<(cloud_pos+4));
  cloud |= (1<<(cloud_pos+5));
  return cloud;
}

bool dfs(int day,int cloud_pos,int total_days){
  if(day == total_days){
    return true;
  }

  bool res = false;

  int store[16];
  memcpy(store,no_rainny_days,sizeof(int)*16);

  for(int i=0;i<9;i++){
    if(day+1 == 1 && i != 8) continue;

    int dx = cloud_pos + tx[i];
    if(dx < 0
       || dx == 3 || dx == 7 || dx == 11
       || (dx >= 12)) continue;

    int next = make_cloud(dx);
    if(stage[day+1] & next) continue;
    // if(day + 1 > total_days) continue;

    rain(next);
    if(!check()){
      memcpy(no_rainny_days,store,sizeof(int)*16);
      continue;
    }

    // printf("festial:%d\n",day+1);
    // print_stage(stage[day+1]);

    // printf("cloud:%d\n",day+1);
    // print_stage(next);

    // printf("no rain:%d\n",day+1);
    // print_rain();

    State next_state(no_rainny_days,dx);
    if(visited[day+1].count(next_state) > 0) continue;
    visited[day+1].insert(next_state);

    res |= dfs(day+1,dx,total_days);
    memcpy(no_rainny_days,store,sizeof(int)*16);
  }
  return res;
}

int main(){
  int total_days;

  while(~scanf("%d",&total_days)){
    if(total_days == 0) break;

    for(int i=0;i<400;i++) visited[i].clear();
    memset(stage,0,sizeof(stage));
    memset(no_rainny_days,0,sizeof(no_rainny_days));

    for(int day=1;day<=total_days;day++){
      int bits = 0;
      for(int pos=0;pos<16;pos++){
	int state;
	cin >> state;
	if(state == 1){
	  bits |= (1<<pos);
	}
      }
      stage[day] = bits;
    }

    printf("%d\n",dfs(0,5,total_days) ? 1 : 0);
  }
}
