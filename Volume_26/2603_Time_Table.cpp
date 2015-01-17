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
 
bool comp_user(const User& s,const User& t){
  return (s.time - s.pos) < (t.time - t.pos);
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
    // dp[0][0] = 0;
    // for(int user_i = 0; user_i < users.size(); user_i++){
    //   dp[user_i][0] = 0;
    // }
    dp[0][0] = 0;
    for(int used_count = 0; used_count < total_buses; used_count++){
      for(int user_i = 0; user_i < users.size(); user_i++){
	for(int user_j = 0; user_j <= user_i; user_j++){
	  int sum = 0;
	  for(int user_k = user_j; user_k <= user_i; user_k++){
	    int len
	      = (users[user_i].time - users[user_i].pos) //dept time for user_i
	      - (users[user_k].time - users[user_k].pos); 

	    // cout << "dept: " << (users[user_i].time - users[user_i].pos) << endl;
	    // cout << users[user_i].pos << endl;
	    // cout << users[user_i].time << endl;
	    // cout << users[user_k].pos << endl;
	    // cout << users[user_k].time << endl;
	    sum += len;
	  } 	
	  // cout << "sum " << sum << endl;
	  dp[user_i + 1][used_count + 1] = min(dp[user_i + 1][used_count + 1],
					       dp[user_j][used_count] + sum);
	}
      }
    }
    printf("%d\n",dp[total_users][total_buses]);
  }
}
