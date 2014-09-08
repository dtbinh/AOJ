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
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

vector<string> answers;
vector<int> groups;
map<vector<int>, int> dp;
int total_questions;
int total_ppl;

int dfs(const vector<int>& current,int used){
  if(current.size() <= 0) return -1;
  if(current.size() == 1) return 0;

  if(dp.count(current)) return dp[current];

  int res = INF;
  for(int question_i=0;question_i<total_questions;question_i++){
    if(used & (1<<question_i)) continue;

    vector<int> next[256];
    for(int i = 0; i < current.size(); i++){
      int ppl_i = current[i];
      char ans = answers[ppl_i][question_i];
      next[ans].push_back(ppl_i);
    }

    int cost = max(dfs(next['0'],
		       used | (1<<question_i)) + 1,
		   dfs(next['1'],
		       used | (1<<question_i)) + 1);
    res = min(res,cost);
  }
  return (dp[current] = res);
}

int main(){
  while(~scanf("%d %d",&total_questions,&total_ppl)){
    if(total_questions == 0 && total_ppl == 0) break;
    groups.clear();
    answers.clear();
    dp.clear();

    for(int ppl_i = 0; ppl_i < total_ppl; ppl_i++){
      string ans;
      cin >> ans;
      answers.push_back(ans);
      groups.push_back(ppl_i);
    }
    
    printf("%d\n",dfs(groups,0));
  }
}
