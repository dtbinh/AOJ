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

int compute_remaining_characters(const vector<int>& characters,int idx,int color){
  int prev_lhs = idx;
  int prev_rhs = idx - 1;
  int lhs = idx;
  int rhs = idx;

  for(int round = 0; round <= characters.size(); round++){
    color = characters[lhs];
    for(;lhs >= 0;lhs--){
      if(characters[lhs] != color){
	lhs++;
	break;
      }
    }
    for(;rhs < characters.size();rhs++){
      if(characters[rhs] != color){
	rhs--;
	break;
      }
    }
    if(lhs < 0) lhs++;
    if(rhs >= characters.size()) rhs--;
    
    if((rhs - lhs + 1)-(prev_rhs-prev_lhs + 1) < 4){
      break;
    }
    prev_lhs = lhs;
    prev_rhs = rhs;
    
    //next pos
    lhs--;
    rhs++;
  }
  return characters.size() - (prev_rhs - prev_lhs + 1);
}

int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n==0) break;

    vector<int> characters;
    for(int i=0;i<n;i++){
      int color;
      scanf("%d",&color);
      characters.push_back(color);
    }

    int res = n;
    for(int idx=0;idx<characters.size();idx++){
      for(int color=1;color<=3;color++){
	vector<int> store = characters;
	characters[idx] = color;
	res = min(res,compute_remaining_characters(characters,idx,color));
	characters = store;
      }
    }
    printf("%d\n",res);
  }
}
