#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double EPS = 1e-8;

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;

    vector<int> seedlings;
    for(int i=0;i<N+1;i++){
      int height;
      scanf("%d",&height);
      seedlings.push_back(height);
    }

    int res = -1;
    for(int erase_idx=0;erase_idx<seedlings.size();erase_idx++){
      vector<int> selected_seedlings;
      for(int get_idx=0;get_idx<seedlings.size();get_idx++){
	if(erase_idx == get_idx) continue;
	selected_seedlings.push_back(seedlings[get_idx]);
      }

      int diff = selected_seedlings[1] - selected_seedlings[0];      
      bool isok = true;
      for(int i=0;i+1<selected_seedlings.size();i++){
	if(diff != selected_seedlings[i+1] - selected_seedlings[i]){
	  isok = false;
	}
      }

      if(isok){
	res = seedlings[erase_idx];
	goto found;
      }
    }
  found:;
    printf("%d\n",res);
  }
}
