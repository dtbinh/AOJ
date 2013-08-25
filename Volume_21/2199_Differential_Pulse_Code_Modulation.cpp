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
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};


int main(){
  int signal_num,code_num;
  while(~scanf("%d %d",&signal_num,&code_num)){
    if(signal_num == 0 && code_num == 0) break;

    int code[16];
    for(int i=0;i<code_num;i++){
      scanf("%d",code+i);
    }
    int input_signal[20000];
    for(int i=0;i<signal_num;i++){
      scanf("%d",input_signal+i);
    }

    int prev[256],next[256];
    memset(prev,0x3f,sizeof(prev));
    memset(next,0x3f,sizeof(next));

    prev[128] = 0;
    for(int step=0;step<signal_num;step++){
      for(int from = 0; from < 256;from++){
	for(int code_idx=0;code_idx<code_num;code_idx++){
	  int to = from + code[code_idx];
	  if(to < 0) to = 0;
	  if(to >= 256) to = 255;

	  next[to] = min(next[to],
			 prev[from] 
			 + (to - input_signal[step]) * (to - input_signal[step]));
	  
	}
      }
      memcpy(prev,next,sizeof(int)*256);
      memset(next,0x3f,sizeof(next));
    }

    int min_v = INF;
    for(int i=0;i<256;i++){
      min_v = min(min_v,prev[i]);
    }
    printf("%d\n",min_v);
  }
}
