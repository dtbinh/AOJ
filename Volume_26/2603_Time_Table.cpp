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
 
struct User {
  int time;
  int pos;
  User(int time,int pos)
    : time(time),pos(pos) {}
};
 
int dp[2001];
 
int dfs(int start_time,int cost,int limit,const vector<User>& users){
  if(limit <= 0) return cost;
  if(start_time > 100) return cost;
 
  int res = cost;
  int tmp[2001];
  memcpy(tmp,dp,sizeof(int)*2000);
  for(int user_i = 0; user_i < users.size(); user_i++){
    //in-time
    int diff;
    if((diff = (users[user_i].pos - start_time) - users[user_i].time) >= 0){
      if(dp[user_i] > diff){
        dp[user_i] = diff;
      }
    }
    //too fast
    else{
      continue;
    }
  }
 
  int sum = 0;
  for(int user_i = 0; user_i < users.size(); user_i++){
    sum += dp[user_i];
    if(sum >= INF) break;
  }
  res = min(res,dfs(start_time + 1,sum,limit - 1,users));
 
  memcpy(dp,tmp,sizeof(int)*2000);
  res = min(res,dfs(start_time + 1,cost,limit,users));
  return res;
}
 
int main(){
  int total_stops;
  int total_users;
  int total_buses;
  while(~scanf("%d %d %d",
               &total_stops,
               &total_users,
               &total_buses)){
    memset(dp,0x3f,sizeof(dp));
    vector<User> users;
 
    int stops[10001];
    for(int stop_i = 0; stop_i < total_stops; stop_i++){
      int dist;
      scanf("%d",&dist);
      stops[stop_i] = dist;
    }
    for(int user_i = 0; user_i < total_users; user_i++){
      int time,stop_i;
      scanf("%d %d",&time,&stop_i);
      stop_i--;
      users.push_back(User(time,stops[stop_i]));
    }
 
    printf("%d\n",dfs(-100,INF,total_buses,users));
  }
}
