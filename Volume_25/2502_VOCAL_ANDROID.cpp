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
  int pattern_num;


  while(~scanf("%d",&pattern_num)){

    int len2point[400];
    memset(len2point,-1,sizeof(len2point));

    for(int pattern_idx=0;pattern_idx<pattern_num;pattern_idx++){
      int lower_len,upper_len,point;
      scanf("%d %d %d",&lower_len,&upper_len,&point);
      for(int len=lower_len;len<=upper_len;len++){
	len2point[len] = max(len2point[len],point);
      }
    }
      
    int m;
    scanf("%d",&m);
    vector<int> point_vec;
    for(int melody_idx=0;melody_idx<m;melody_idx++){
      int w;
      scanf("%d",&w);
      int dp[400];
      memset(dp,-1,sizeof(dp));
      dp[0] = 0;
      for(int total_len=0;total_len<=w;total_len++){
	for(int add_bar_len=0;add_bar_len<=total_len;add_bar_len++){
	  if(len2point[add_bar_len] == -1) continue;
	  dp[total_len] = max(len2point[add_bar_len]+dp[total_len-add_bar_len],dp[total_len]);
	}
      }
      point_vec.push_back(dp[w]);
    }

    bool isok = true;
    for(int i=0;i<point_vec.size();i++){
      if(point_vec[i] == -1){
	isok = false;
      }
    }

    if(isok){
      for(int i=0;i<point_vec.size();i++){
	printf("%d\n",point_vec[i]);
      }
    }

    else{
      printf("%d\n",-1);
    }
  }
}
