#define _USE_MATH_DEFINES
#define INF 1000000000

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

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;

    vector<int> signals;
    queue<int> unknown;

    for(int i=0; i < N; i++){
      char signal[12];
      int num;
      scanf("%s",signal);
      if(signal[0] != 'x'){
	num = atoi(signal);
      }
      else{
	num = INF;
	unknown.push(i);
      }
      signals.push_back(num);
    }
    
    int lower = -INF;
    int upper = INF;

    while(!unknown.empty()){
      int idx = unknown.front();
      unknown.pop();
      int lhs = idx - 1;
      int rhs = idx + 1;
      
      //even
      if((idx+1) % 2 == 0){
	if(idx > 0) {
	  if(signals[lhs] != INF){
	    lower = max(signals[lhs]+1,lower);
	  }
	}
	if(signals[rhs] != INF){
	  lower = max(signals[rhs]+1,lower);
	}
      }
      //odd
      else{
	if(idx < signals.size() -1){
	  if(signals[rhs] != INF){
	    upper = min(signals[rhs]-1,upper);
	  }
	}
	if(signals[lhs] != INF){
	  upper = min(signals[lhs]-1,upper);
	}
      }
    }

    bool is_none = false;
    for(int i=0;i<signals.size();i++){
      if(signals[i] == INF) continue;

      int lhs = i - 1;
      int rhs = i + 1;
      if(lhs >= 0 && signals[lhs] != INF){
	if((i + 1) % 2 == 0){
	  if(signals[i] - signals[lhs] < 0){
	    is_none = true;
	    break;
	  }
	}
	else{
	  if(signals[i] - signals[lhs] > 0){
	    is_none = true;
	    break;
	  }
	}
      }
      if(rhs < signals.size() && signals[rhs] != INF){
	if((i + 1) % 2 == 0){
	  if(signals[i] - signals[rhs] < 0){
	    is_none = true;
	    break;
	  }
	}
	else{
	  if(signals[i] - signals[rhs] > 0){
	    is_none = true;
	    break;
	  }
	}
      }
    }

    if(!is_none && upper - lower > 0){
      printf("ambiguous\n");
    }
    else if(!is_none && upper == lower){
      printf("%d\n",upper);
    }
    else if(is_none || upper - lower < 0){
      printf("none\n");
    }
  }
}
