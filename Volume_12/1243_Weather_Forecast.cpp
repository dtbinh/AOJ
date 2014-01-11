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

set<int> visited[400];
int stage[400];
int no_rainny_days[20];

void print_stage(int num){
  for(int y=0;y<4;y++){
    for(int x=0;x<4;x++){
      printf("%d ",num & (1<<(y*4+x)) ? 1 : 0);
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

void dfs(int day,int cloud_pos,int total_days){

  for(int i=0;i<9;i++){
    int dx = cloud_pos + tx[i];
    if(dx < 0
       || dx == 3 || dx == 7 || dx == 11
       || (dx >= 12)) continue;

    int store[20];
    memcpy(store,no_rainny_days,sizeof(int)*20);

    int next = 0;
    next |= (1<<dx);
    next |= (1<<(dx+1));
    next |= (1<<(dx+4));
    next |= (1<<(dx+5));
    if(stage[day+1] & next) continue;
    if(day + 1 > total_days) continue;

    rain(next);
    if(!check()){
      memcpy(no_rainny_days,store,sizeof(int)*20);
      continue;
    }

    int history = 0;
    history = (next << 12);
    history |= (1<<dx);
    
    // if(visited[day+1].count(history)) continue;

    // printf("day:%d\n",day+1);
    // printf("%u\n",history);

    // printf("cloud day:%d\n",day+1);
    // print_stage(next);
    
    // printf("festival day:%d\n",day+1);
    // print_stage(stage[day+1]);

    visited[day+1].insert(history);
    dfs(day+1,dx,total_days);
    memcpy(no_rainny_days,store,sizeof(int)*20);
  }
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
	scanf("%d",&state);
	if(state == 1){
	  bits |= (1<<pos);
	}
      }
      stage[day] = bits;
    }

    int init = 0;
    init |= (1<<5);
    init |= (1<<(5+1));
    init |= (1<<(5+4));
    init |= (1<<(5+5));

    // if(total_days % 7 != 0){
    //   total_days += (total_days % 7);
    // }
    // printf("ans:%d\n",(stage[1] & init) ? 0
    // 	   : (dfs(1,5,init,total_days) < total_days ? 0 : 1));

    int last_day = 0;
    rain(init);
    
    if(init & stage[1]) {
      // nothing to do
    }
    else {
      dfs(1,5,total_days);
    }

    for(int i=1;i<400;i++){
      if(visited[i].size() > 0){
	last_day = i;
      }
    }

    printf("last:%d total:%d\n",last_day,total_days);
    printf("%d\n",last_day < total_days ? 0 : 1);
  }
}
