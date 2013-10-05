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
  int cycle_length,interview_num;
  int cycle[100];
  map<int,vector<int> > interview;

  scanf("%d",&cycle_length);
  for(int i=0;i<cycle_length;i++){
    scanf("%d",cycle+i);
  }
  scanf("%d",&interview_num);
  
  int last_day = 0;
  for(int i=0;i<interview_num;i++){
    int day,start_hour;
    scanf("%d %d",&day,&start_hour);
    interview[day].push_back(start_hour);
    last_day = max(day,last_day);
  }

  int dp[100][100];
  memset(dp,0,sizeof(dp));

  //1
  //0
  //1 1
  //0 1
  //1 0
  //0 0

  for(int day=1;day<=last_day;day++){
    for(int used_day=1;used_day<day;used_day++){
      for(int hour_idx=0;hour_idx<interview[day].size();hour_idx++){
	int start_hour = interview[hour_idx];
      }
    }
  }
}
