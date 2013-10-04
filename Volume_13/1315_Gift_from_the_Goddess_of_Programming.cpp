#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
#include <iostream>
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
typedef pair <int,P > PP;

int time2min(int month,int day,int hour,int min){
  const int total_day_of_month[]
    = {31,28,31,30,31,30,31,31,30,31,30,31};
  int total = 0;
  for(int i=1;i<month;i++){
    total += total_day_of_month[i]*24*60;
  }
  for(int i=1;i<day;i++){
    total += 24*60;
  }
  total += hour * 60 + min;

  return total;
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N==0) break;

    map<int,vector<int> > log;
    for(int i=0;i<N;i++){
      int month,day,hour,min,id;
      char action[2];
      scanf("%d/%d %d:%d %s %d",
	    &month,&day,&hour,&min,action,
	    &id);
      
      int t = time2min(month,day,hour,min);
      log[id].push_back(t);
    }

    int total[1000];
    memset(total,0,sizeof(total));
    
    for(int i=0;i+1<log[0].size();i+=2){
      int god_start = log[0][i];
      int god_end = log[0][i+1];

      for(map<int,vector<int> >::iterator it = log.begin();
	  it != log.end();
	  it++){
	int id = it->first;
	if(id == 0) continue;
	vector<int>& schedule = it->second;
	for(int j=0;j<schedule.size();j+=2){
	  int ppl_start = schedule[j];
	  int ppl_end = schedule[j+1];
	  int start = max(god_start,ppl_start);
	  int end = min(god_end,ppl_end);
	  total[id] += max(0,end-start);
	}
      }
    }

    int max_v = 0;
    for(int id=0;id<1000;id++){
      max_v = max(total[id],max_v);
    }
    printf("%d\n",max_v);
  }
}
