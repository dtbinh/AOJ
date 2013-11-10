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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-12;

int main(){
  int N,T;
  while(~scanf("%d %d",&N,&T)){
    vector<int> levels;
    for(int i=0;i<N;i++){
      int num;
      scanf("%d",&num);
      levels.push_back(num);
    }

    sort(levels.begin(),levels.end());

    ll res = 1;
    const ll MOD = 1000000007;
    for(int i=0;i<N;i++){
      ll trans_num = upper_bound(levels.begin(),levels.end(),levels[i] + T) - (levels.begin() + i);
      res = ((res % MOD) * (trans_num % MOD)) % MOD;
    }

    printf("%lld\n",res);
  }
}
