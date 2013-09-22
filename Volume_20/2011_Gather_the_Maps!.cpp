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
    int inheritance_schedule[50];
    ll inheritance_belongings[50];
    memset(inheritance_schedule,0,sizeof(inheritance_schedule));
    memset(inheritance_belongings,0,sizeof(inheritance_belongings));
    
    for(int i=0;i<N;i++) inheritance_belongings[i] = (1LL<<i);
    for(int i=0;i<N;i++){
      int total_days;
      scanf("%d",&total_days);
      
      int mask = 0;
      for(int j=0;j<total_days;j++){
	int day;
	scanf("%d",&day);
	mask |= (1<<day);
      }
      inheritance_schedule[i] = mask;
    }

    int res = -1;
    for(int day=1;day<=30;day++){
      for(int from=0;from<N;from++){
	for(int to=0;to<N;to++){
	  int both_suit_schedule
	    = inheritance_schedule[from] & inheritance_schedule[to];
	
	  if(both_suit_schedule & (1<<day)){
	    inheritance_belongings[to] |= inheritance_belongings[from];
	  }
	}
      }

      for(int i=0;i<N;i++){
	if(inheritance_belongings[i] == ((1LL<<N) - 1LL) ){
	  res = day;
	  goto found;
	}
      }
    }
  found:;
    printf("%d\n",res);
  }
}
