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
  
static const int tx[] = {-1,1,4,-4};


int stage[400];

int dfs(int day,int cloud_pos,set<int> visited[400]){
  int res = day;

  int now = 0;
  now |= (1<<cloud_pos);
  now |= (1<<cloud_pos+1);
  now |= (1<<cloud_pos+4);
  now |= (1<<cloud_pos+5);
  visited[day].insert(now);

  if(now & stage[day]) return res;

  for(int i=0;i<4;i++){
    int dx = cloud_pos + tx[i];
    if(dx == 3 || dx == 7 || dx == 11 || (dx >= 12)) continue;

    int next = 0;
    next |= (1<<dx);
    next |= (1<<dx+1);
    next |= (1<<dx+4);
    next |= (1<<dx+5);

    if(stage[day+1] & next) continue;
    if(day + 1 > 365) continue;
    if(visited[day+1].count(next)) continue;

    visited[day+1].insert(next);
    res = max(res,dfs(day+1,dx,visited));
  }
  return res;
}

int main(){
  int total_days;

  while(~scanf("%d",&total_days)){
    if(total_days == 0) break;

    set<int> visited[400];
    memset(stage,0,sizeof(stage));
    for(int day=0;day<total_days;day++){
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

    
    printf("%d\n",dfs(0,5,visited) < total_days ? 0 : 1);
  }
}
