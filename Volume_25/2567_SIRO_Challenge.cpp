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
typedef pair <string,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};


int edges[301][301];
int ramen_time[20];
int dp[301][1<<16];

int main(){
  int num_of_stations;
  int num_of_pairs;
  int num_of_SIRO;
  int starting_point;
  int time_limit;
  while(~scanf("%d %d %d %d %d",
	       &num_of_stations,
	       &num_of_pairs,
	       &num_of_SIRO,
	       &starting_point,
	       &time_limit)){
    if(num_of_stations == 0
       && num_of_pairs == 0
       && num_of_SIRO == 0
       && starting_point == 0
       && time_limit == 0) break;

    memset(edges,0x3f,sizeof(edges));
    starting_point--;

    for(int i = 0; i < num_of_pairs; i++){
      int from,to;
      int time;
      scanf("%d %d %d",&from,&to,&time);
      from--;
      to--;
      edges[from][to] = time;
      edges[to][from] = time;
    }

    for(int mid = 0; mid < num_of_stations; mid++){
      for(int from = 0; from < num_of_stations; from++){
	for(int to = 0; to < num_of_stations; to++){
	  edges[from][to] = min(edges[from][to],edges[from][mid] + edges[mid][to]);
	}
      }
    }

    int SIRO_idx[301];
    memset(SIRO_idx,-1,sizeof(SIRO_idx));
    memset(ramen_time,0x3f,sizeof(ramen_time));
    for(int i = 0; i < num_of_SIRO; i++){
      int station,time;
      scanf("%d %d",&station,&time);
      station--;
      ramen_time[i] = time;
      SIRO_idx[station] = i;
    }

    memset(dp,0x3f,sizeof(dp));
    dp[starting_point][0] = 0;

    for(int S = 0; S < (1<<num_of_SIRO); S++){
      for(int from = 0; from < num_of_stations; from++){
	if(SIRO_idx[from] != -1){
	  dp[from][S | (1<<SIRO_idx[from])]
	    = min(dp[from][S | (1<<SIRO_idx[from])],
		  dp[from][S] + ramen_time[SIRO_idx[from]]);
	}

	for(int to = 0; to < num_of_stations; to++){
	  if(from == to) continue;

	  if(SIRO_idx[to] == -1){
	    dp[to][S] = min(dp[from][S] + edges[from][to],dp[to][S]);
	  }
	  else{
	    dp[to][S | (1 << SIRO_idx[to])]
	      = min(dp[to][S | (1 << SIRO_idx[to])]
		    ,dp[from][S] + edges[from][to] + ramen_time[SIRO_idx[to]]);
	    dp[to][S]
	      = min(dp[to][S],dp[from][S] + edges[from][to]);
	  }
	}
      }
    }

    int res = 0;
    for(int S = 0; S < (1<<num_of_SIRO); S++){
      for(int point = 0; point < num_of_stations; point++){
	if(time_limit >= dp[point][S]){
	  res = max(res,__builtin_popcount(S));
	}
      }
    }
    
    printf("%d\n",res);
  }
}
