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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

bool is_prime[1000001];
map<P,int> stage;

int main(){
  int x = 0;
  int y = 0;
  int dir = 1;
  for(int round = 1; round <= 1000000;round++){
    stage[P(y,x)] = round;

    int prev_dir = dir;
    if(round > 1) dir = (dir + 3) % 4;
    int dx = x + tx[dir];
    int dy = y + ty[dir];
    if(stage.find(P(dy,dx)) != stage.end()){
      dir = prev_dir;
    }
    dx = x + tx[dir];
    dy = y + ty[dir];
    x = dx;
    y = dy;
  }
  
  memset(is_prime,true,sizeof(is_prime));

  is_prime[0] = false;
  is_prime[1] = false;

  for(int i=2;i*i<=1000000;i++){
    if(is_prime[i]){
      for(int j=i+i;j<=1000000;j+=i){
	is_prime[j] = false;
      }
    }
  }

  int start,total_caves;
  while(~scanf("%d %d",&total_caves,&start)){
    if(total_caves == 0 && start == 0) break;

    int sx=0,sy=0;
    for(map<P,int>::iterator it = stage.begin();
	it != stage.end();
	it++){
      int x = it->first.second;
      int y = it->first.first;
      int num = it->second;
      if(num == start){
	sx = x;
	sy = y;
	break;
      }
    }


    map <P,int> prev;
    map <P,int> next;

    int res_prime=0;
    int res_count=0;

    prev[P(sy,sx)] = (int)is_prime[stage[P(sy,sx)]];
    if(is_prime[stage[P(sy,sx)]]){
      res_prime = stage[P(sy,sx)];
      res_count = 1;
    }
    for(int y=sy+1,width=3;y<=1000;y++,width+=2){
      bool is_update = false;
      for(int x=sx - width;x<=sx + width;x++){
	if(stage[P(y,x)] > total_caves) continue;
	is_update = true;

	int cost = (int)is_prime[stage[P(y,x)]];
	if(prev.find(P(y-1,x-1)) != prev.end()){
	  next[P(y,x)] = max(prev[P(y-1,x-1)] + cost,next[P(y,x)]);
	}
	if(prev.find(P(y-1,x)) != prev.end()){
	  next[P(y,x)] = max(prev[P(y-1,x)] + cost,next[P(y,x)]);
	}
	if(prev.find(P(y-1,x+1)) != prev.end()){
	  next[P(y,x)] = max(prev[P(y-1,x+1)] + cost,next[P(y,x)]);
	}
      }

      prev.clear();
      prev = next;

      if(!is_update) break;
    }

    for(map<P,int>::iterator it = next.begin();
	it != next.end();
	it++){
      if(!is_prime[stage[it->first]]) continue;

      if(res_count < it->second){
	res_count = it->second;
	res_prime = stage[it->first];
      }
      if(res_count == it->second
	 && res_prime < stage[it->first]){
	res_prime = stage[it->first];
      }
    }
    printf("%d %d\n",res_count,res_prime);
  }
}
