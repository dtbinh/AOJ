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

bool check(const deque<complex<double> >& deq,double limit_rad){
  complex<double> src = deq[0];
  complex<double> mid = deq[1];
  complex<double> dst = deq[2];

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
  deque<complex<double> > deq;
  State(int _ct,int _c,double _r,const deque<complex<double> >& _d) :
    city(_ct), carrots(_c), remaining_distance(_r),deq(_d) {}

  State(int _ct,int _c,double _r,complex<double> _d) :
    city(_ct), carrots(_c), remaining_distance(_r) {
    deq.push_back(_d);
  }

  bool operator <(const State& s) const{
    return carrots < s.carrots;
  }
};

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
    que.push(State(0,0,r,cities[0]));
    int max_carrots = 0;
    while(!que.empty()){
      State s = que.top();
      que.pop();
      max_carrots = max(s.carrots,max_carrots);

      for(int to=0;to<cities.size();to++){
	if(to == s.city) continue;
	
	double dist = abs(cities[to] - cities[s.city]);
	deque<complex<double> > deq = s.deq;
	
	deq.push_back(cities[to]);
	while(deq.size() > 3) deq.pop_front();

	if(deq.size()==3){
	  if(!check(deq,limit_rad)) continue;
	}
	if(s.remaining_distance - dist <= 0) continue;

	State next(to,s.carrots+1,s.remaining_distance - dist,deq);
	que.push(next);
      }
    }

    printf("%d\n",max_carrots);
  }
}
