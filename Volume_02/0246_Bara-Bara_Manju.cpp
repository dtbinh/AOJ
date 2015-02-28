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


map<vector<int>,int> dp;

int dfs(vector<int> buns,int sum,int comb_i,vector<vector<int> >& all_combinations){
  if(comb_i >= all_combinations.size()) return sum;
  if(dp.find(buns) != dp.end()) return dp[buns];

  vector<int> prev = buns;
  bool isok = true;
  for(int weight = 1; weight <= 10; weight++){
    int use_count = all_combinations[comb_i][weight];
    buns[weight] -= use_count;
    if(buns[weight] < 0){
      isok = false;
      break;
    }
  }

  int res = 0;
  if(isok){
    res = max(sum + 1,dfs(buns,sum + 1,comb_i,all_combinations));
  }
  else{
    buns = prev;
    res = max(sum,dfs(buns,sum,comb_i + 1,all_combinations));
  }

  return (dp[buns] = max(res,dp[buns]));
}

void make_combinations(int weight,int sum,vector<int>& current,vector<vector<int> >& all_combinations){
  if(sum >= 10){
    if(sum == 10) all_combinations.push_back(current);
    return;
  }
  if(weight > 10) return;

  for(int use_count = 0; use_count <= 10; use_count++){
    current[weight] = use_count;
    make_combinations(weight + 1,sum + weight * use_count,current,all_combinations);
    current[weight] = 0;
  }
}

int main(){
  int total_buns;
  
  vector<vector<int> > all_combinations;
  vector<int> current(11);
  make_combinations(1,0,current,all_combinations);
  while(~scanf("%d",&total_buns)){
    if(total_buns == 0) break;
    dp.clear();
    vector<int> buns(11);

    for(int i = 0; i < total_buns; i++){
      int weight;
      scanf("%d",&weight);
      buns[weight]++;
    }

    int greedy_sum = 0;
    for(int weight = 1; weight <= 10; weight++){
      if(weight == 5){
	int use_count = (buns[weight] / 2) * 2;
	greedy_sum += use_count / 2;
	buns[weight] -= use_count;
      }
      else{
	int use_count = min(buns[weight],buns[10 - weight]);
	greedy_sum += use_count;
	buns[weight] -= use_count;
	buns[10 - weight] -= use_count;
      }
    }

    printf("%d\n",greedy_sum + dfs(buns,0,0,all_combinations));
  }
}
