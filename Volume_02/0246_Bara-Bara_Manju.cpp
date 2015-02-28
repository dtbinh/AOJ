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
typedef pair <int,P> PP;
 
static const int tx[] = {+0,+1,+0,-1};
static const int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

int dfs(){
}

void make_combinations(int weight,int sum,vector<int> current,vector<vector<int> >& all_combinations){
  if(sum >= 10){
    if(sum == 10) all_combinations.push_back(current);
    return;
  }
  for(int count = 1; count <= 10; count++){
    current[weight] = count;
    make_combinations(weight + 1,sum + weight * count,current,all_combinations);
    current[weight] = 0;
  }
}

int main(){
  int total_buns;
  
  vector<vector<int> > all_combinations;
  while(~scanf("%d",&total_buns)){
    if(total_buns == 0) break;

    vector<int> buns;
    for(int i = 0; i < total_buns; i++){
      int weight;
      scanf("%d",&weight);
      buns.push_back(weight);
    }
    vector<int> current(10);
    make_combinations(1,0,current,all_combinations);
  }
}
