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

ll sum_d2[10001];
ll sum_d[10001];
ll sum[10001];
int is_on[10001];
ll recover_log[3652426];

struct Service{
  ll lower_bound;
  int type;
  int speed_up_duration;
  Service(ll _l,int _t,int _s)
    : lower_bound(_l),type(_t),speed_up_duration(_s){}
};

int main(){
  int total_services;
  int seek_duration;

  memset(sum_d2,0,sizeof(sum_d2));
  memset(sum_d,0,sizeof(sum_d));
  memset(sum,0,sizeof(sum));
  for(int day=1;day<=10000;day++){
    sum_d2[day] = sum_d2[day-1] + day * day;
    sum_d[day] = sum_d[day-1] + day;
    sum[day] = sum[day-1] + 1;
  }

  while(~scanf("%d %d",&total_services,&seek_duration)){
    memset(is_on,-1,sizeof(is_on));

    vector<Service> services;
    for(int service_idx = 0; service_idx < total_services; service_idx++){
      ll lower_bound;
      int type;
      int speed_up_duration;
      scanf("%lld %d %d",&lower_bound,&type,&speed_up_duration);
      services.push_back(Service(lower_bound,type,speed_up_duration));
    }

    ll recover_level = 0;

    memset(recover_log,0,sizeof(recover_log));
    for(int day=0;day<=3652425;day++){
      for(int service_idx = 0; service_idx < total_services; service_idx++){
	if(is_on[service_idx] != -1
	   && day > is_on[service_idx]
	   && (day - is_on[service_idx]
	       <= services[service_idx].speed_up_duration)){
	  
	  if(services[service_idx].type == 0){
	    recover_level += 1;
	  }
	  else if(services[service_idx].type == 1){
	    recover_level += (day - is_on[service_idx]);
	  }
	  else if(services[service_idx].type == 2){
	    recover_level += (day - is_on[service_idx]) * (day - is_on[service_idx]);
	  }
	}
      }
	
      for(int service_idx = 0; service_idx < total_services; service_idx++){
	if(recover_level >= services[service_idx].lower_bound
	   && is_on[service_idx] == -1){
	  is_on[service_idx] = day;
	}
      }
      recover_log[day] = recover_level;
      recover_level++;
    }

    for(int service_idx = 0; service_idx < total_services; service_idx++){
      if(is_on[service_idx] != -1){
	printf("%d\n",is_on[service_idx]);
      }
      else {
	printf("Many years later\n");
      }
    }

    for(int seek_idx = 0; seek_idx < seek_duration; seek_idx++){
      int day;
      scanf("%d",&day);
      printf("%lld\n",recover_log[day]);
    }
  }
}
