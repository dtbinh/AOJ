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
  int edges[4];

  int total_triangles = 0;

  int right_angle_num = 0;
  int acute_angle_num = 0;
  int obtuse_angle_num = 0;

  while(~scanf("%d %d %d",edges+0,edges+1,edges+2)){
    sort(edges,edges+3);
    if(edges[2] >= edges[0] + edges[1]){
      printf("%d %d %d %d\n",
	     total_triangles,
	     right_angle_num,
	     acute_angle_num,
	     obtuse_angle_num);
      break;
    }

    if(edges[2] * edges[2] == edges[0] * edges[0] + edges[1] * edges[1]){
      right_angle_num++;
    }
    else if(edges[2] * edges[2] < edges[0] * edges[0] + edges[1] * edges[1]){
      acute_angle_num++;
    }
    else if(edges[2] * edges[2] > edges[0] * edges[0] + edges[1] * edges[1]){
      obtuse_angle_num++;
    }
    
    total_triangles++;
  }
}
