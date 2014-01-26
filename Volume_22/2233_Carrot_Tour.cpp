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
#include <iterator>
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

bool check(const deque<int>& deq,double limit_rad,
	   const vector<complex<double> >& cities){
  complex<double> src = cities[deq[0]];
  complex<double> mid = cities[deq[1]];
  complex<double> dst = cities[deq[2]];

  src -= mid;
  dst -= mid;

  return (limit_rad >= M_PI - min(abs(arg(src) - arg(dst)),
				  abs(2.0*M_PI - arg(src) - arg(dst))));
}
class State {
public:
  int carrots;
  int city;
  double remaining_distance;
  deque<int> deq;
  State(int _ct,int _c,double _r,const deque<int>& _d) :
    city(_ct), carrots(_c), remaining_distance(_r),deq(_d) {}

  State(int _ct,int _c,double _r,int _d) :
    city(_ct), carrots(_c), remaining_distance(_r) {
    deq.push_back(_d);
  }

  bool operator <(const State& s) const{
    if(carrots == s.carrots){
      return remaining_distance < s.remaining_distance;
    }
    return carrots < s.carrots;
  }
};

bool dp[5001][9000]; //dp[carrot][visit history] := remaining distance

int main(){
  int total_cities;
  while(~scanf("%d",&total_cities)){
    double r,theta;
    vector<complex<double> > cities;
    scanf("%lf %lf",&r,&theta);
    double limit_rad = theta * M_PI / 180.0;
    for(int city_idx = 0; city_idx < total_cities; city_idx++){
      int x,y;
      scanf("%d %d",&x,&y);
      cities.push_back(complex<double>(x,y));
    }

    priority_queue<State> que;
    que.push(State(0,0,r,0));
    int max_carrots = 0;
    memset(dp,0,sizeof(dp));

    while(!que.empty()){
      State s = que.top();
      que.pop();
      max_carrots = max(s.carrots,max_carrots);

      while(s.deq.size() > 3) s.deq.pop_front();
      int history = 0;
      int digit = 1;

      for(int i=0;i<s.deq.size();i++){
	history += (s.deq[i]+1) * digit;
	digit *= 21;
      }

      if(dp[s.carrots][history]) continue;
      dp[s.carrots][history] = true;

      for(int to=0;to<cities.size();to++){
	if(to == s.city) continue;
	
	double dist = abs(cities[to] - cities[s.city]);
	deque<int> deq = s.deq;
	
	deq.push_back(to);
	while(deq.size() > 3) deq.pop_front();

	if(deq.size()==3){
	  if(!check(deq,limit_rad,cities)) continue;
	}
	if(s.remaining_distance - dist <= 0) continue;

	State next(to,s.carrots+1,s.remaining_distance - dist,deq);
	que.push(next);
      }
    }

    printf("%d\n",max_carrots);
  }
}
