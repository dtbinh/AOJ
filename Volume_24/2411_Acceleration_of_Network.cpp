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

int is_on[10001];
ll recover_log[3652426];

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
    memset(is_on,-1,sizeof(is_on));

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
    memset(recover_log,0,sizeof(recover_log));
    
    vector<Service> provider;
    ll current = 0;
    for(int service_idx = 0; service_idx < total_services;){
      if(services[service_idx].lower_bound <= recover_level){
	recover_log[service_idx] = current;
	provider.push_back(services[service_idx]);
	service_idx++;
      }
      else{
	if(!provider.empty()){
	  // cout << "bsearch begin" << endl;
	  ll max_add_day = MAX;
	  ll min_add_day = 0;
	  ll add_recover_level = 0;
	  ll unsatisfied_recover_level = 0;

	  for(int round=0;round < 80; round++){
	    ll mid = (max_add_day + min_add_day) / 2;
	    
	    ll tmp_recover_level = 0;
	    for(int i=0;i<provider.size();i++){
	      tmp_recover_level += provider[i].compute_recover(current - recover_log[provider[i].service_idx],
							       (current - recover_log[provider[i].service_idx]) + mid);
	    }

	    if(tmp_recover_level + recover_level + mid >= services[service_idx].lower_bound){
	      add_recover_level = tmp_recover_level + mid;
	      max_add_day = mid;
	    }
	    else if(tmp_recover_level + recover_level + mid < services[service_idx].lower_bound){
	      unsatisfied_recover_level = tmp_recover_level + mid;
	      min_add_day = mid;
	    }
	  }

	  if(max_add_day < MAX){

	    // cout << "add_recover_level:" << add_recover_level << endl;
	    // cout << "add_day:" << max_add_day << endl;

	    recover_level += add_recover_level;
	    current += max_add_day;
	    // cout << "day:" << current << endl;

	    //erase from provider
	    for(vector<Service>::iterator it = provider.begin();
		it != provider.end();
		it++){
	      if(current - recover_log[it->service_idx] > it->speed_up_duration){
		vector<Service>::iterator next = provider.erase(it);
		if(next == provider.end()) break;
		it = next;
	      }
	    }
	    // cout << "bsearch end" << endl;
	  }
	  else{
	    recover_level += unsatisfied_recover_level;
	    current += min_add_day;
	    provider.erase(provider.begin(), provider.end());
	  }
	}
	else{
	  // cout << "no provider" << endl;
	  recover_level++;
	  current++;
	}
      }
    }


    for(int service_idx = 0; service_idx < total_services;service_idx++){
      if(recover_log[service_idx] > 3652425){
	printf("Many years later\n");
      }
      else {
	printf("%lld\n",recover_log[service_idx]);
      }
    }

    for(int seek_idx = 0; seek_idx < seek_duration; seek_idx++){
      int day;
      scanf("%d",&day);
      ll tmp_recover_level = 0;
      for(int service_idx = 0; service_idx < total_services;service_idx++){
	if(recover_log[service_idx] < day){
	  tmp_recover_level
	    += services[service_idx].compute_recover(1,(day - recover_log[service_idx]));
	}
      }

      printf("%lld\n",tmp_recover_level + day);
    }
  }
}
