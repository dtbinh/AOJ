#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
static const double EPS = 1e-8;

static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int prior[21];
int credit[21];
int dp[1<<20];
int total_subjects;
int credit_requirement;

void dfs(int S,int sum){
  if(dp[S] != -1) return;
  dp[S] = sum;
  for(int i = 0; i < total_subjects; i++){
    if((prior[i] | S) == S){
      dfs(S | (1<<i),sum + credit[i]);
    }
  }
}

int main(){
  while(~scanf("%d %d",&total_subjects,&credit_requirement)){
    if(total_subjects == 0 && credit_requirement == 0) break;
    memset(dp,-1,sizeof(dp));
    memset(prior,0,sizeof(prior));

    for(int subject_i = 0; subject_i < total_subjects; subject_i++){
      int prior_subject_num;
      scanf("%d %d",&credit[subject_i],&prior_subject_num);
      for(int subject_j = 0; subject_j < prior_subject_num; subject_j++){
	int subject_code;
	scanf("%d",&subject_code);
	prior[subject_i] |= (1<<subject_code);
      }
    }
    dfs(0,0);
    int res = INF;
    for(int S = 0; S < (1<<total_subjects); S++){
      if(dp[S] == -1) continue;
      if(dp[S] >= credit_requirement){
	res = min(res,__builtin_popcount(S));
      }
    }
    printf("%d\n",res);
  }
}
