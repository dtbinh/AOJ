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

int dp[2001][2001];
int opt_waiting_time[2001];
int waiting_sum[2001][2001];
 
bool comp_user(const User& s,const User& t){
  return (s.time - s.pos) < (t.time - t.pos);
}

int compute_sum(int user_i,int user_j,int used_count,const vector<User>& users){
  if(waiting_sum[user_j + (used_count == 0 ? 0 : 1)][user_i] != -1){
    return waiting_sum[user_j + (used_count == 0 ? 0 : 1)][user_i];
  }

  int sum = 0;
  for(int user_k = user_j + (used_count == 0 ? 0 : 1); user_k < user_i; user_k++){
    int wait
      = (users[user_i].time - users[user_i].pos) //user_i's waiting time is zero
      - (users[user_k].time - users[user_k].pos);
    sum += wait;
  }

  return (waiting_sum[user_j + (used_count == 0 ? 0 : 1)][user_i] = sum);
}

int compute_opt_waiting_time(int user_i,int user_j,int used_count,const vector<User>& users){
  if(user_j > user_i) return INF;
  return dp[used_count][user_j] + compute_sum(user_i,user_j,used_count,users);
}

void dfs(int lx,int ly,int rx,int ry,int used_count,const vector<User>& users){
  if(ly > ry) return;

  int pivot_y = (ly + ry) / 2;
  int current_opt = INF;
  int pivot_x;
  for(int x = lx; x <= rx; x++){
    int opt_candidate = compute_opt_waiting_time(pivot_y,x,used_count,users);
    if(current_opt > opt_candidate){
      current_opt = opt_candidate;
      pivot_x = x;
    }
  }

  // for debug
  // printf("pivot_y: %d pivot_x: %d opt: %d\n",pivot_y,pivot_x,current_opt);
  opt_waiting_time[pivot_y] = current_opt;
  dfs(lx,ly,pivot_x,pivot_y - 1,used_count,users);
  dfs(pivot_x,pivot_y + 1,rx,ry,used_count,users);
}

void print_monotone_minima_table(int used_count,vector<User>& users){
  printf("sum:\n");
  for(int y = 0; y < users.size(); y++){
    for(int x = 0; x < users.size(); x++){
      int sum = compute_sum(y,x,used_count,users);
      printf("%10d ",sum);
    }
    printf("\n");
  }

  printf("dp:\n");
  for(int y = 0; y < users.size(); y++){
    for(int x = 0; x < users.size(); x++){
      int opt_candidate = compute_opt_waiting_time(y,x,used_count,users);
      printf("%10d ",opt_candidate);
    }
    printf("\n");
  }
  printf("\n");
}

int main(){
  int total_stops;
  int total_users;
  int total_buses;
  while(~scanf("%d %d %d",
               &total_stops,
               &total_users,
               &total_buses)){
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

    sort(users.begin(),users.end(),comp_user);
    memset(dp,0x3f,sizeof(dp));
    memset(waiting_sum,-1,sizeof(waiting_sum));

    dp[0][0] = 0;
    for(int used_count = 0; used_count < total_buses; used_count++){
      // for debug
      // print_monotone_minima_table(used_count,users);
      dfs(0,0,total_users - 1,total_users - 1,used_count,users);
      for(int user_i = 0; user_i < total_users; user_i++){
	dp[used_count + 1][user_i] = opt_waiting_time[user_i];
      }
    }
    printf("%d\n",dp[total_buses][total_users - 1]);
  }
}
