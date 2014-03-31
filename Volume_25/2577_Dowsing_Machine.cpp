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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

int main(){
  int h,w,d_range,total_responses;
  while(~scanf("%d %d %d %d",&h,&w,&d_range,&total_responses)){
    char stage[51][51];

    int d_x,d_y;
    for(int y=0;y<h;y++){
      char line[256];
      scanf("%s",line);
      for(int x=0;x<w;x++){
	stage[y][x] = line[x];
	if(line[x] == 'D'){
	  d_x = x;
	  d_y = y;
	}
      }
    }

    int r[101];
    for(int d_idx=0;d_idx<d_range;d_idx++){
      int distance;
      scanf("%d",&distance);
      r[d_idx] = distance;
    }

    int state=0;
    for(int response_idx=0;response_idx<total_responses;response_idx++){
      int x,y,s;
      scanf("%d %d %d",&x,&y,&s);
      int distance = max(abs(d_x - x),abs(d_y - y));
      printf("real dist:%d\n",distance);

      if(s == d_range){
	printf("outside :\n");
	if(distance < r[s]){
	  state |= (1<<0);
	}
      }
      else if(s < d_range){
	printf("inside : %d\n",r[s]);
	if(distance > r[s]){
	  state |= (1<<0);
	}
      }
    }
  }
}
