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
  
static const int tx[] = {-1,1,4,-4,0};

set<unsigned long int> visited[400];
unsigned long int stage[400];

void print_stage(int num){
  for(int y=0;y<4;y++){
    for(int x=0;x<4;x++){
      printf("%d ",num & (1<<(y*4+x)) ? 1 : 0);
    }
    printf("\n");
  }
  printf("\n");
}

int dfs(int day,int cloud_pos,unsigned long int rain_log,int total_days){
  int res = day;

  for(int dist=1;dist<=2;dist++){
    for(int i=0;i<5;i++){
      int dx = cloud_pos + tx[i] * dist;
      if(dx < 0
	 || dx == 3 || dx == 7 || dx == 11
	 || (dx >= 12)) continue;
      
      unsigned long int next = 0;
      next |= (1<<dx);
      next |= (1<<(dx+1));
      next |= (1<<(dx+4));
      next |= (1<<(dx+5));
      
      if(stage[day+1] & next) continue;
      if(day + 1 > total_days) continue;

      unsigned long int next_rain_log = rain_log;
      next_rain_log |= next;

      if((day + 1) % 7 == 0){
	if(next_rain_log != (1<<16)-1){
	  continue;
	}
	else {
	  next_rain_log = next;
	}
      }

      unsigned long int history = 0;
      history |= (next << 16);
      history |= next_rain_log;

      if(visited[day+1].count(history)) continue;

      // printf("cloud day:%d\n",day+1);
      // print_stage(next);

      // printf("festival day:%d\n",day+1);
      // print_stage(stage[day+1]);
      visited[day+1].insert(history);
      res = max(res,dfs(day+1,dx,next_rain_log,total_days));
    }
  }
  return res;
}

int main(){
  int total_days;

  while(~scanf("%d",&total_days)){
    if(total_days == 0) break;

    for(int i=0;i<400;i++) visited[i].clear();
    memset(stage,0,sizeof(stage));

    for(int day=1;day<=total_days;day++){
      unsigned long int bits = 0;
      for(int pos=0;pos<16;pos++){
	int state;
	scanf("%d",&state);
	if(state == 1){
	  bits |= (1<<pos);
	}
      }
      stage[day] = bits;
    }

    unsigned long int init = 0;
    init |= (1<<5);
    init |= (1<<(5+1));
    init |= (1<<(5+4));
    init |= (1<<(5+5));

    printf("%d\n",(stage[1] & init) ? 0
	   : (dfs(1,5,init,total_days) < total_days ? 0 : 1));
  }
}
