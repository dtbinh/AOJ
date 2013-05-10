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
  int grid_num = 0;
  while(~scanf("%d",&grid_num)){
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    
    int res = INF;
    for(int w=1;w<=grid_num;w++){
      int p_x[4];
      int p_y[4];
      p_x[0] = (a-1)%w;
      p_x[1] = (b-1)%w;
      p_x[2] = (c-1)%w;
      p_x[3] = (d-1)%w;
      p_y[0] = (a-1)/w;
      p_y[1] = (b-1)/w;
      p_y[2] = (c-1)/w;
      p_y[3] = (d-1)/w;

      int ab_dist = abs(p_x[0]-p_x[1]) + abs(p_y[0]-p_y[1]);
      int cd_dist = abs(p_x[2]-p_x[3]) + abs(p_y[2]-p_y[3]);
      res = min(ab_dist+cd_dist,res);
    }

    printf("%d\n",res);
  }
}
