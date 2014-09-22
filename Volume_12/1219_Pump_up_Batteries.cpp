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
#include <assert.h>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;

class State {
public:
  int _id;
  int _time;
  int _occupy;
  State(int id,int time,int occupy) : _id(id),_time(time), _occupy(occupy) {}
  bool operator<(const State& s) const {
    if(_time == s._time) return _id < s._id;
    return _time < s._time;
  }
  bool operator>(const State& s) const {
    if(_time == s._time) return _id > s._id;
    return _time > s._time;
  }
};

int main(){
  int num_of_guards;
  int simulation_duration;
  while(~scanf("%d %d",&num_of_guards,&simulation_duration)){
    if(num_of_guards == 0 && simulation_duration == 0) break;

    vector<int> time_table[101];
    for(int guard_i = 0; guard_i < num_of_guards; guard_i++){
      int comsuming_duration;
      int charging_duration;
      while(~scanf("%d",&comsuming_duration)){
	if(comsuming_duration == 0) break;
	scanf("%d",&charging_duration);
	time_table[guard_i].push_back(comsuming_duration);
	time_table[guard_i].push_back(charging_duration);
      }
    }
    
    int for_queue[101];
    int next_process[101];
    bool is_inque[101];
    memset(next_process,0,sizeof(next_process));
    memset(for_queue,0,sizeof(for_queue));
    memset(is_inque,false,sizeof(is_inque));

    priority_queue<State,vector<State>,greater<State> > que;
    int res = 0;
    for(int time = 0; time < simulation_duration;time++){
      char action[101];
      memset(action,'-',sizeof(action));
      for(int guard_i = 0; guard_i < num_of_guards; guard_i++){
	if(next_process[guard_i] % 2 == 0){ // to consume
	  if(is_inque[guard_i]){
	    continue;
	  }
	  for_queue[guard_i] = time_table[guard_i][next_process[guard_i] % time_table[guard_i].size()] - 1;
	  next_process[guard_i]++;
	  action[guard_i] = '*';
	}
	else{ //to charge
	  if(for_queue[guard_i] > 0){
	    action[guard_i] = '*';
	    for_queue[guard_i]--;
	    continue;
	  }

	  que.push(State(guard_i,time,time_table[guard_i][next_process[guard_i] % time_table[guard_i].size()]));
	  next_process[guard_i]++;
	  is_inque[guard_i] = true;
	}
      }
      if(!que.empty()){
	State s = que.top();
	que.pop();
	action[s._id] = '.';
	if(s._occupy - 1 > 0){
	  que.push(State(s._id,s._time,s._occupy-1));
	}
	else{
	  is_inque[s._id] = false;
	}
      }

      res += count(action,action+num_of_guards,'-');

      // for debug
      // printf("time:%d\n",time);
      // for(int guard_i = 0; guard_i < num_of_guards; guard_i++){
      // 	printf("%c\n",action[guard_i]);
      // }
      // printf("\n");
    }

    printf("%d\n",res);
  }
}
