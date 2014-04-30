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

int main(){
  int N,R;
  int dp[100001];
  int target[100001];
  while(~scanf("%d %d",&N,&R)){
    for(int i=1;i<=N;i++) target[i] = i;
    for(int r = 0; r< R;r++){
      int from_idx,int to_idx;
      scanf("%d %d",&from_idx,&to_idx);
      swap(target[from_idx],target[to_idx]);
    }
    
  }
}
