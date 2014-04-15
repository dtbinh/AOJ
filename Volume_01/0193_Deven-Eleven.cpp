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
  
static const double EPS = 1e-8;
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

pair<int,int> maja(int x) {
  if (x == 0) return pair<int,int>(0,0);
  int n = static_cast<int>(ceil((-1.0+sqrt(1.0+4.0/3.0*x))/2.0));
  int a = 3*n*(n-1), d = static_cast<int>(ceil((1.0*x-a)/n-1.0));
  int k = x - a - n * d;
  switch (d) {
  case 0: return pair<int,int>(n-k,k);
  case 1: return pair<int,int>(-k,n);
  case 2: return pair<int,int>(-n,n-k);
  case 3: return pair<int,int>(-n+k,-k);
  case 4: return pair<int,int>(k,-n);
  case 5: return pair<int,int>(n,-n+k);
  }
}

int majadist(const pair<int,int> &a, const pair<int,int> &b) {
  int dx = abs(a.first - b.first);
  int dy = abs(a.second - b.second);
  int dz = abs(a.first+a.second-b.first-b.second);
  return min(dx+dy, min(dx+dz, dy+dz));
}

int main(){
  int W,H;

  while(~scanf("%d %d",&W,&H)){
    if(W == 0 && H == 0) break;

    map<pair<int,int>,bool> stage;
    int total_existing_stores;
    scanf("%d",&total_existing_stores);
    for(int store_idx = 0; store_idx < total_existing_stores; store_idx++){
      int x,y;
      scanf("%d %d",&x,&y);
      x--;
      y--;
      stage[pair<int,int>(x,y)] = true;
    }

    int total_new_stores;

    int res = 0;
    scanf("%d",&total_new_stores);
    for(int store_idx = 0; store_idx < total_new_stores; store_idx++){
      int sx,sy;
      scanf("%d %d",&sx,&sy);

      sx--;
      sy--;
      int region = 0;
      for(int x=0;x<W;x++){
	for(int y=0;y<H;y++){
	  int min_dist = INF;
	  
	  for(map<pair<int,int>,bool>::iterator it = stage.begin();
	      it != stage.end();
	      it++){
	    min_dist = min(min_dist,majadist(it->first,pair<int,int>(x,y)));
	  }
	  
	  if(majadist(pair<int,int>(sx,sy),pair<int,int>(x,y)) < min_dist)
	    {
	      region++;
	    }
	}
	res = max(region,res);
      }
    }
    printf("%d\n",res);
  }
}
