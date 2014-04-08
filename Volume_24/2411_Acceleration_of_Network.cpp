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
static const ll MAX = 1e15;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

ll recover_log[100001];
ll all_log[3652427];
ll sub_a[3652427];
ll sub_b[3652427];
ll sub_c[3652427];

class Service{
public:
  ll lower_bound;
  int type;
  int speed_up_duration;
  int service_idx;
  Service(ll _l,int _t,int _s,int _si)
    : lower_bound(_l),type(_t),speed_up_duration(_s),service_idx(_si){}
  bool operator<(const Service& s) const{
    return lower_bound < s.lower_bound;
  }
  bool operator>(const Service& s) const{
    return lower_bound > s.lower_bound;
  }
};

int main(){
  int total_services;
  int seek_duration;

  while(~scanf("%d %d",&total_services,&seek_duration)){

    vector<Service> services;
    for(int service_idx = 0; service_idx < total_services; service_idx++){
      ll lower_bound;
      int type;
      int speed_up_duration;
      scanf("%lld %d %d",&lower_bound,&type,&speed_up_duration);
      services.push_back(Service(lower_bound,type,speed_up_duration,service_idx));
    }

    memset(recover_log,-1,sizeof(recover_log));   
    memset(all_log,0,sizeof(all_log));

    memset(sub_a,0,sizeof(sub_a));
    memset(sub_b,0,sizeof(sub_b));
    memset(sub_c,0,sizeof(sub_c));

    int next_target = 0;
    ll a=0,b=0,c=1;//f = ax^2 + b^x+c

    sort(services.begin(),services.end());

    for(ll day=1;day <= 3652425 + 1;day++){

      ll recover_level = all_log[day-1];

      while(next_target < total_services 
	    && services[next_target].lower_bound <= recover_level){
	recover_log[services[next_target].service_idx] = day - 1;

	if(services[next_target].type == 0){
	  c++;
	  if(day + services[next_target].speed_up_duration <= 3652425 + 1) {
	    sub_c[day+services[next_target].speed_up_duration]++;
	  }
	}
	else if(services[next_target].type == 1){
	  b++;
	  c += -(day - 1);
	  if(day + services[next_target].speed_up_duration <= 3652425 + 1) {
	    sub_b[day+services[next_target].speed_up_duration]++;
	    sub_c[day+services[next_target].speed_up_duration] += -(day-1);
	  }
	}
	else if(services[next_target].type == 2){
	  a++;
	  b += -2*(day-1);
	  c += (day-1)*(day-1);
	  if(day + services[next_target].speed_up_duration <= 3652425 + 1) {
	    sub_a[day+services[next_target].speed_up_duration]++;
	    sub_b[day+services[next_target].speed_up_duration] += -2*(day-1);
	    sub_c[day+services[next_target].speed_up_duration] += (day-1) * (day-1);
	  }
	}
	next_target++;
      }

      a -= sub_a[day];
      b -= sub_b[day];
      c -= sub_c[day];
      all_log[day] = recover_level + a * day * day + b * day + c;
    }

    for(int service_idx = 0; service_idx < total_services;service_idx++){
      if(recover_log[service_idx] == -1){
	printf("Many years later\n");
      }
      else {
	printf("%lld\n",recover_log[service_idx]);
      }
    }

    for(int seek_idx = 0; seek_idx < seek_duration; seek_idx++){
      int day;
      scanf("%d",&day);
      printf("%lld\n",all_log[day]);
    }
  }
}
