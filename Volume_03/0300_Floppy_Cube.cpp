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
 
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

static const int tops[4][3] = {{1,2,3},{3,6,9},{7,8,9},{1,4,7}};
static const int long_sides[4][3] = {{21,20,19},{15,14,13},{10,11,12},{16,17,18}};
static const int short_sides[4] = {16,19,13,10};

void rotate(int cell[31],int pattern_i){
  for(int i = 0; i < 3; i++){
    swap(cell[31 - tops[pattern_i][i]],cell[tops[pattern_i][2 - i]]);
    swap(cell[long_sides[pattern_i][2 - i]],cell[long_sides[pattern_i][i]]);
  }
  swap(cell[31-short_sides[pattern_i]],cell[short_sides[pattern_i]]);
}

bool check(int cell[31]){
  for(int i = 1; i < 9; i++){
    if(cell[i] != cell[i+1]) return false;
  }

  for(int i = 10; i < 12; i++){
    if(cell[i] != cell[i+1]) return false;
  }

  for(int i = 13; i < 15; i++){
    if(cell[i] != cell[i+1]) return false;
  }

  for(int i = 16; i < 18; i++){
    if(cell[i] != cell[i+1]) return false;
  }

  for(int i = 19; i < 21; i++){
    if(cell[i] != cell[i+1]) return false;
  }

  for(int i = 22; i < 30; i++){
    if(cell[i] != cell[i+1]) return false;
  }
  return true;
}
 

int dfs(int cell[31],int depth){
  if(depth > 8) return INF;
  if(check(cell)){
    return depth;
  }

  int res = INF;
  int prev[31];
  memcpy(prev,cell,sizeof(int)*31);
  for(int pattern_i = 0; pattern_i < 4; pattern_i++){
    rotate(cell,pattern_i);
    res = min(res,dfs(cell,depth+1));
    memcpy(cell,prev,sizeof(int)*31);
  }
  return res;
}

int main(){
  int total_test_cases;
  while(~scanf("%d",&total_test_cases)){
    int cell[31];
    for(int test_i = 0; test_i < total_test_cases; test_i++){
      for(int cell_i = 1; cell_i <= 30; cell_i++){
	int num;
	scanf("%d",&num);
	cell[cell_i] = num;
      }
      printf("%d\n",dfs(cell,0));
    }
  }
}
