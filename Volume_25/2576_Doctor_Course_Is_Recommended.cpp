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
  int total_d;
  while(~scanf("%d",&total_d)){
    int total_one_choice_problem;
    scanf("%d",&total_one_choice_problem);

    vector<int> single_points;
    for(int problem_idx=0;problem_idx<total_one_choice_problem;problem_idx++){
      char type[32];
      int point;
      scanf("%s %d",type,&point);
      if(strcmp(type,"D") != 0){
	continue;
      }
      single_points.push_back(point);
    }
    int total_two_choice_problem;
    vector<int> double_points;
    scanf("%d",&total_two_choice_problem);
    for(int problem_idx=0;problem_idx<total_two_choice_problem;problem_idx++){
      char type[32];
      int point;
      scanf("%s %d",type,&point);
      if(strcmp(type,"DD") != 0){
	continue;
      }
      double_points.push_back(point);
    }

    int dp[15];
    memset(dp,0,sizeof(dp));

    for(int i=0;i<single_points.size();i++){
      for(int from=13;from>=0;from--){
	dp[from + 1] = max(dp[from] + single_points[i],dp[from+1]);
      }
    }
    for(int i=0;i<double_points.size();i++){
      for(int from=13;from>=0;from--){
	dp[from + 2] = max(dp[from] + double_points[i],dp[from+2]);
      }
    }

    int max_point = 0;
    for(int d=total_d;d>=0;d--){
      max_point = max(max_point,dp[d]);
    }
    printf("%d\n",max_point);
  }
}
