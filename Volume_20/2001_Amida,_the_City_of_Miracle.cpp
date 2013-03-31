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

//[x][y]
int connect[101][1001];

int main(){
  int virtical_num,horizontal_num,search_pos;

  while(~scanf("%d %d %d",&virtical_num,&horizontal_num,&search_pos)){
    if(virtical_num == 0 
       && horizontal_num == 0 
       && search_pos == 0) break;

    int max_h = 0;
    memset(connect,-1,sizeof(connect));
    for(int i=0;i<horizontal_num;i++){
      int h,from,to;
      scanf("%d %d %d",&h,&from,&to);
      connect[from][h] = to;
      connect[to][h] = from;
      max_h = max(h,max_h);
    }

    int x = search_pos;
    for(int y=max_h;y>=0;y--){
      if(connect[x][y] != -1){
	x = connect[x][y];
	// printf("x:%d\n",x);
      }
    }

    printf("%d\n",x);
  }
}


