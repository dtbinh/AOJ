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
  int next;
  DP(){
    cost = INF;
    next = -1;
  }
};

int main(){
  int total_hotels;
  int total_days;
  while(~scanf("%d %d",
	       &total_hotels,
	       &total_days)){
    int price_table[55][55];
    memset(price_table,0,sizeof(price_table));

    for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
      for(int day=1;day<=total_days;day++){
	int price;
	scanf("%d",&price);
	price_table[day][hotel_idx] = price;
      }
    }

    DP dp[55][55][55]; //dp[day][current_hotel][current_move_count] = cost
    for(int day=0;day<=total_days;day++){   
      for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
      	  for(int move_count=0;move_count<=total_days;move_count++){
	    dp[day][hotel_idx][move_count].cost = INF;
	    dp[day][hotel_idx][move_count].next = -1;
	  }
      }
    }

    for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
      dp[total_days+1][hotel_idx][0].cost = 0;
      dp[total_days+1][hotel_idx][0].next = hotel_idx;
    }

    for(int day=total_days;day>=1;day--){   
	for(int next_hotel_idx=1;next_hotel_idx<=total_hotels;next_hotel_idx++){
	  for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
	    for(int next_move_count=0;next_move_count<=total_days;next_move_count++){
	    
	    int move_count
	      = next_move_count + (next_hotel_idx == hotel_idx ? 0 : 1);

	    if(dp[day][hotel_idx][move_count].cost
	       > dp[day+1][next_hotel_idx][next_move_count].cost + price_table[day][hotel_idx]){
	      
	      dp[day][hotel_idx][move_count].cost
		= dp[day+1][next_hotel_idx][next_move_count].cost + price_table[day][hotel_idx];
	      dp[day][hotel_idx][move_count].next = next_hotel_idx;
	    }
	  }
	}
      }
    }
    
    int next_hotel;
    int current_move_count = 0;
    int min_cost = INF;
    int min_move_count = INF;

    for(int move_count=0;move_count<=total_days;move_count++){
      for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
	if(dp[1][hotel_idx][move_count].cost < min_cost){
	  min_cost = dp[1][hotel_idx][move_count].cost;
	  min_move_count = move_count;
	  next_hotel = hotel_idx;
	  current_move_count = move_count;
	}
      }
    }

    printf("%d %d\n",min_cost,min_move_count);
    for(int day=1;day<=total_days;day++){
      printf("%d\n",next_hotel);
      int tmp_hotel = dp[day][next_hotel][current_move_count].next;
      if(tmp_hotel != next_hotel) current_move_count--;
      next_hotel = tmp_hotel;
    }
  }
  return 0;
}
