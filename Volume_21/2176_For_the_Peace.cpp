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
  int total_countries;
  int tolerated_difference;
  while(~scanf("%d %d",&total_countries,&tolerated_difference)){
    if(total_countries == 0) break;
    deque<int> country[100];
    int sum[100];
    memset(sum,0,sizeof(sum));
    for(int country_idx=0;country_idx < total_countries; country_idx++){
      int total_missiles;
      scanf("%d",&total_missiles);
      for(int missile_idx=0; missile_idx < total_missiles; missile_idx++){
	int missile_ability;
	scanf("%d",&missile_ability);
	country[country_idx].push_back(missile_ability);
	sum[country_idx] += missile_ability;
      }
    }

    for(;;){
      bool can_update = false;
      for(int country_idx = 0;country_idx < total_countries; country_idx++){
	if(country[country_idx].size() == 0) continue;

	int back_num = country[country_idx].back();
	sum[country_idx] -= back_num;
	country[country_idx].pop_back();

	int max_v = 0;
	int min_v = INF;
	for(int country_idx2 = 0;country_idx2 < total_countries; country_idx2++){
	  max_v = max(max_v,sum[country_idx2]);
	  min_v = min(min_v,sum[country_idx2]);
	}

	if(tolerated_difference < (max_v - min_v)){
	  sum[country_idx] += back_num;
	  country[country_idx].push_back(back_num);
	}
	else{
	  can_update = true;
	}
      }
      if(!can_update) break;
    }

    int final_sum = 0;
    for(int country_idx = 0;country_idx < total_countries; country_idx++){
      final_sum += sum[country_idx];
    }
    printf("%s\n",final_sum == 0 ? "Yes" : "No");
  }
}
