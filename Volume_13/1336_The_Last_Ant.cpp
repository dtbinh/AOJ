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

class Ant{
public:
  char dir;
  int pos;
  Ant(char _d,int _p) : dir(_d), pos(_p) {}
  Ant() : dir('\0'), pos(-1) {}
};

int main(){
  int total_ants;
  int tunnel_length;
  while(scanf("%d %d",&total_ants,&tunnel_length)){
    if(total_ants == 0) break;

    Ant ants[101];
    for(int ant_idx=0; ant_idx < total_ants; ant_idx++){
      char dir[2];
      int pos;
      scanf("%s %d",dir,&pos);
      ants[ant_idx] = Ant(dir[0],pos);
    }

    int last_time = 0;
    int last_ant = 0;
    for(int time=1;time <= tunnel_length * total_ants;time++){
      int collapse[101];
      memset(collapse,0,sizeof(collapse));
      int rem = 0;
      for(int ant_idx=0; ant_idx < total_ants; ant_idx++){
	if(ants[ant_idx].pos == 0
	   || ants[ant_idx].pos == tunnel_length) continue;

	rem |= (1 << ant_idx);
	if(ants[ant_idx].dir == 'R'){
	  collapse[ants[ant_idx].pos + 1] |= (1 << ant_idx);
	}

	else if(ants[ant_idx].dir == 'L'){
	  collapse[ants[ant_idx].pos - 1] |= (1 << ant_idx);
	}
      }

      if(rem == 0) break;

      for(int i=1;i<tunnel_length;i++){
	if(__builtin_popcount(collapse[i]) >= 2){
	  for(int ant_idx=0; ant_idx < total_ants; ant_idx++){
	    if(collapse[i] & (1 << ant_idx)){
	      ants[ant_idx].pos += (ants[ant_idx].dir == 'R' ? 1 : -1);
	      ants[ant_idx].dir = (ants[ant_idx].dir == 'R' ? 'L' : 'R');
	      rem &= ~(1 << ant_idx);
	    }
	  }	  
	}
      }

      for(int ant_idx=0; ant_idx < total_ants; ant_idx++){
	if(rem & (1<< ant_idx)){
	  if(ants[ant_idx].dir == 'R'){
	    ants[ant_idx].pos++;
	  }
	  else if(ants[ant_idx].dir == 'L'){
	    ants[ant_idx].pos--;
	    if(ants[ant_idx].pos == 0){
	      last_ant = ant_idx;
	    }
	  }
	}
      }
      last_time = max(last_time,time);
    }
    
    printf("%d %d\n",last_time,last_ant + 1);
  }
}
