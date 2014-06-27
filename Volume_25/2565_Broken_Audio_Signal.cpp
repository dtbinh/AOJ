#define _USE_MATH_DEFINES
#define INF 1000000100

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

    bool has_x = false;
    bool has_num = false;
    for(int i=0; i < N; i++){
      char signal[12];
      int num;
      scanf("%s",signal);
      if(signal[0] != 'x'){
	num = atoi(signal);
	has_num = true;
      }
      else{
	num = INF;
	has_x = true;
	unknown.push(i);
      }
      signals.push_back(num);
    }
    
    if(has_num && has_x){
      //x x 1 x
      int lower = -INF;
      int upper = INF;
      
      while(!unknown.empty()){
	int idx = unknown.front();
	unknown.pop();
	int lhs = idx - 1;
	int rhs = idx + 1;
	
	//even
	if((idx+1) % 2 == 0){
	  if(lhs >= 0 && signals[lhs] != INF) {
	    lower = max(signals[lhs]+1,lower);
	  }
	  if(rhs < signals.size() && signals[rhs] != INF){
	    lower = max(signals[rhs]+1,lower);
	  }
	}
	//odd
	else{
	  if(rhs < signals.size() && signals[rhs] != INF){
	    upper = min(signals[rhs]-1,upper);
	  }
	  if(lhs >= 0 && signals[lhs] != INF){
	    upper = min(signals[lhs]-1,upper);
	  }
	}
      }

      if(upper - lower > 0){
	printf("ambiguous\n");
      }
      else if(upper == lower){
	printf("%d\n",upper);
      }
      else if(upper - lower < 0){
	printf("none\n");
      }
    }

    else if(!has_num && has_x){
      //x x x
      printf("none\n");
    }
    else if(has_num && !has_x){
      //1 2 3
      
      bool is_none = false;
      for(int i=0;i<signals.size();i++){
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
     
      printf("%s\n",is_none ? "none" : "ambiguous");
    }
  }
}
