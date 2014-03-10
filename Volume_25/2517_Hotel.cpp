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

struct DP{
  int cost;
  int prev;
  DP(){
    cost = INF;
    prev = -1;
  }
};

int main(){
  int total_hotels;
  int total_days;
  while(~scanf("%d %d",
	       &total_hotels,
	       &total_days)){
    int price_table[100][100];
    memset(price_table,0,sizeof(price_table));

    for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
      for(int day=1;day<=total_days;day++){
	int price;
	scanf("%d",&price);
	price_table[day][hotel_idx] = price;
      }
    }

    DP dp[100][100][100]; //dp[day][current_hotel][current_move_count] = cost
    for(int day=1;day<=total_days;day++){   
      for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
      	  for(int move_count=0;move_count<=day;move_count++){
	    dp[day][hotel_idx][move_count].cost = INF;
	    dp[day][hotel_idx][move_count].prev = -1;
	  }
      }
    }
    for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
      dp[0][hotel_idx][0].cost = 0;
    }

    for(int day=1;day<=total_days;day++){   
      for(int prev_move_count=0;prev_move_count<=day;prev_move_count++){
	for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
	  for(int prev_hotel_idx=1;prev_hotel_idx<=total_hotels;prev_hotel_idx++){
	    int move_count
	      = prev_move_count + (prev_hotel_idx == hotel_idx ? 0 : 1);
	    
	    if(dp[day][hotel_idx][move_count].cost
	       > dp[day-1][prev_hotel_idx][prev_move_count].cost + price_table[day][hotel_idx]){
	      
	      dp[day][hotel_idx][move_count].cost
		= dp[day-1][prev_hotel_idx][prev_move_count].cost + price_table[day][hotel_idx];
	      dp[day][hotel_idx][move_count].prev = prev_hotel_idx;
	    }
	    
	    if(dp[day][hotel_idx][move_count].cost
	       == dp[day-1][prev_hotel_idx][prev_move_count].cost + price_table[day][hotel_idx]
	       && dp[day][hotel_idx][move_count].prev > prev_hotel_idx){
	      dp[day][hotel_idx][move_count].prev = prev_hotel_idx;
	    }
	    
	  }
	}
      }
    }

    int min_cost = INF;
    int min_move = INF;
    vector<int> last_hotel_candidates;
    for(int move_count=0;move_count<=total_days;move_count++){
      for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
	if(min_cost > dp[total_days][hotel_idx][move_count].cost){
	  last_hotel_candidates.clear();
	  min_cost = dp[total_days][hotel_idx][move_count].cost;
	  min_move = move_count;
	  last_hotel_candidates.push_back(hotel_idx);
	}
	else if(min_cost == dp[total_days][hotel_idx][move_count].cost
		&& min_move == move_count){
	  last_hotel_candidates.push_back(hotel_idx);
	}
	else if(min_cost == dp[total_days][hotel_idx][move_count].cost
		&& min_move > move_count){
	  last_hotel_candidates.clear();
	  min_move = move_count;
	  last_hotel_candidates.push_back(hotel_idx);
	}
      }
    }

    printf("%d %d\n",min_cost,min_move);
    vector<int> champ;
    for(int last_hotel_candidate_idx=0;
	last_hotel_candidate_idx < last_hotel_candidates.size();
	last_hotel_candidate_idx++){

      vector<int> stk;
      int prev_move_count = min_move;
      int prev_day = total_days;
      int prev_hotel = last_hotel_candidates[last_hotel_candidate_idx];

      while(prev_day > 0){
	stk.push_back(prev_hotel);
	
	bool is_diff = false;
	if(prev_hotel != dp[prev_day][prev_hotel][prev_move_count].prev){
	  is_diff = true;
	}
	prev_hotel = dp[prev_day][prev_hotel][prev_move_count].prev;
	if(is_diff) prev_move_count--;
	prev_day--;
      }

      reverse(stk.begin(),stk.end());
      if(champ.empty()){
	champ = stk;
      }
      else {
	for(int i=0;i<champ.size();i++){
	  if(stk[i] != champ[i]){
	    if(stk[i] > champ[i]){
	      //nothing to do;
	      break;
	    }
	    else if(stk[i] < champ[i]){
	      champ = stk;
	      break;
	    }
	  }
	}
      }

    }

    for(int i=0;i<champ.size();i++){
      printf("%d\n",champ[i]);
    }
  }
  return 0;
}
