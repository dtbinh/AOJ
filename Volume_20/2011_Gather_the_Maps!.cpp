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
 
const static int mx[] = {1,-1,1,-1};
const static int my[] = {1,-1,-1,1};

int main(){
  int N;
  
  while(~scanf("%d",&N)){
    if(N==0) break;
    int inheritance[50];
    for(int i=0;i<N;i++){
      int total_days;
      scanf("%d",&total_days);
      
      int mask = 0;
      for(int j=0;j<total_days;j++){
	int day;
	scanf("%d",&day);
	mask |= (1<<day);
      }
      inheritance[i] = mask;
    }


    bool visited_day[31];
    bool visited_inheritance[50];
    memset(visited_day,false,sizeof(visited_day));
    memset(visited_inheritance,false,sizeof(visited_inheritance));

    int res = 0;
    for(int round=0;round<N;round++){
      int opt_freq = 0;
      int opt_day = 0;
      for(int day=1;day<=30;day++){
	if(visited_day[day]) continue;
	int freq = 0;
	for(int j=0;j<N;j++){
	  if(visited_inheritance[j]) continue;
	  if(inheritance[j] & (1<<day)){
	    freq++;
	  }
	}
	
	if(opt_freq < freq){
	  opt_freq = freq;
	  opt_day = day;
	}
      }

      if(opt_day == 0) break;
      visited_day[opt_day] = true;
      for(int j=0;j<N;j++){
	if(inheritance[j] & (1<<opt_day)){
	  visited_inheritance[j] = true;
	}
      }
      res++;
    }

    printf("%d\n",res <= 30 ? res : -1);
  }
}
