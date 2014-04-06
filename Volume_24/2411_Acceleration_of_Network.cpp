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
ll level_log[3652426];

struct Service{
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
  bool operator<(const ll _v) const{
    return lower_bound < _v;
  }
  bool operator>(const ll _v) const{
    return lower_bound > _v;
  }

  ll compute_recover(ll passed_days){
    if(type == 0){
      return 1;
    }
    else if(type == 1){
      return passed_days;
    }
    else if(type == 2){
      return passed_days * passed_days;
    }
  }
  ll compute_recover(ll first,ll last){
    last = min((ll)speed_up_duration,last);
    first = min((ll)speed_up_duration+1,first);

    ll minus = 0; 
    if(first > 0){
      if(type == 0){
	minus = first - 1;
      }
      else if(type == 1){
	minus = (first-1) * (1 + (first-1)) / 2;
      }
      else if(type == 2){
	minus = (first-1)*(first)*(2*(first-1)+1) / 6;
      }
    }

    if(type == 0){
      return last - minus;
    }
    else if(type == 1){
      return last * (1 + last) / 2 - minus;
    }
    else if(type == 2){
      return last*(last+1)*(2*last+1) / 6 - minus;
    }
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

    sort(services.begin(),services.end());
    ll recover_level = 0;
    memset(recover_log,-1,sizeof(recover_log));   
    memset(level_log,-1,sizeof(level_log));

    list<Service> provider;
    
    int next_target = 0;
    for(int day=0;day <= 3652425;day++){
      ll add_recover_level = 0;

      if(!provider.empty()){
	for(list<Service>::iterator it = provider.begin();
	    it != provider.end();
	){
	  ll passed_days = day - recover_log[it->service_idx];
	  if(passed_days > it->speed_up_duration){
	    list<Service>::iterator next = provider.erase(it);
	    if(next == provider.end()) break;
	    it = next;
	  }
	  else{
	    add_recover_level += it->compute_recover(passed_days);
	    it++;
	    if(it == provider.end()) break;
	  }
	}
      }

      for(int i = next_target; i < total_services; i++){
	if(services[i].lower_bound > recover_level + add_recover_level) break;
	if(recover_log[i] != -1) break;
	recover_log[i] = day;
	provider.push_back(services[i]);
	next_target = i+1;
      }

      level_log[day] = recover_level + add_recover_level;      
      recover_level += add_recover_level + 1;
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
      printf("%lld\n",level_log[day]);
    }
  }
}
