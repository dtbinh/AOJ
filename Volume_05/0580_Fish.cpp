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
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

class Cuboid{
public:
  ll ox[8]; //original x
  ll oy[8];
  ll od[8];

  int mx[8]; // mapped x
  int my[8];
  int md[8];

  Cuboid(int x1,int y1,int d1,
	 int x2,int y2,int d2){
    ox[0] = x1;
    oy[0] = y1;
    od[0] = d1;

    ox[1] = x1;
    oy[1] = y2;
    od[1] = d1;

    ox[2] = x2;
    oy[2] = y2;
    od[2] = d1;

    ox[3] = x2;
    oy[3] = y1;
    od[3] = d1;

    ox[4] = x1;
    oy[4] = y1;
    od[4] = d2;

    ox[5] = x1;
    oy[5] = y2;
    od[5] = d2;

    ox[6] = x2;
    oy[6] = y2;
    od[6] = d2;

    ox[7] = x2;
    oy[7] = y1;
    od[7] = d2;
  }    

  void mapping(const vector<ll>& xs,
	       const vector<ll>& ys,
	       const vector<ll>& ds){
    for(int i=0;i<8;i++){
      mx[i] = lower_bound(xs.begin(),xs.end(),ox[i]) - xs.begin();
      my[i] = lower_bound(ys.begin(),ys.end(),oy[i]) - ys.begin();
      md[i] = lower_bound(ds.begin(),ds.end(),od[i]) - ds.begin();
    }
  }
};

int dp[101][101][101];

int main(){
  int total_fish;
  int lower;
  while(~scanf("%d %d",&total_fish,&lower)){

    vector<ll> xs;
    vector<ll> ys;
    vector<ll> ds;

    vector<Cuboid> cuboids;
    for(int fish_idx = 0; fish_idx < total_fish; fish_idx++){
      ll x1,y1,d1;
      ll x2,y2,d2;
      scanf("%lld %lld %lld",&x1,&y1,&d1);
      scanf("%lld %lld %lld",&x2,&y2,&d2);
      
      cuboids.push_back(Cuboid(x1,y1,d1,x2,y2,d2));
      xs.push_back(x1);       
      xs.push_back(x2);

      ys.push_back(y1);       
      ys.push_back(y2);

      ds.push_back(d1);       
      ds.push_back(d2);
    }

    sort(xs.begin(),xs.end());
    sort(ys.begin(),ys.end());
    sort(ds.begin(),ds.end());

    xs.erase(unique(xs.begin(),xs.end()),xs.end());
    ys.erase(unique(ys.begin(),ys.end()),ys.end());
    ds.erase(unique(ds.begin(),ds.end()),ds.end());

    memset(dp,0,sizeof(dp));
    for(int i=0;i<cuboids.size();i++){
      cuboids[i].mapping(xs,ys,ds);

      for(int x = cuboids[i].mx[0]; x < cuboids[i].mx[2]; x++){
	for(int y = cuboids[i].my[0]; y < cuboids[i].my[1]; y++){
	  for(int d = cuboids[i].md[0]; d < cuboids[i].md[4]; d++){
	    dp[x][y][d]++;
	  }
	}
      }
    }

    ll res = 0;
    for(int x = 0; x < xs.size(); x++){
      for(int y = 0; y < ys.size(); y++){
	for(int d = 0; d < ds.size(); d++){
	  if(dp[x][y][d] >= lower){
	    res += (xs[x + 1] - xs[x])
	      * (ys[y + 1] - ys[y])
	      * (ds[d + 1] - ds[d]);
	  }
	}
      }
    }

    printf("%lld\n",res);
  }
}
