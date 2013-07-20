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
  int n;
  while(~scanf("%d",&n)){
    vector<ll> h;
    for(int i=0;i<n;i++){
      ll hit_point;
      scanf("%ld",&hit_point);
      h.push_back(hit_point);
    }
    sort(h.begin(),h.end(),greater<ll>());
    ll res = 1;

    for(int i=0;i<h.size();i++){
      res += (h[i] - i/4 >= 0 ? h[i] - i/4 : 0);
    }

    printf("%ld\n",res);
  }
}

