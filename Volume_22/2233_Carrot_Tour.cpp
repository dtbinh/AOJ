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
 
static const double EPS = 1e-12;

bool check(int city,int prev,int old,double limit_rad,
	   const vector<complex<double> >& cities){
  complex<double> src = cities[old];
  complex<double> dst = cities[city];

  src -= cities[prev];
  dst -= cities[prev];
  double computed_arg = abs(arg(src) - arg(dst));

  return (limit_rad >= M_PI - min(computed_arg,
				  abs(2.0*M_PI - computed_arg)) - EPS);
}
class State {
public:
  int carrots;
  int city;
  int prev;
  int old;
  double remaining_distance;
  State(int _ct,int _p,int _o,int _c,double _r) :
    city(_ct),prev(_p),old(_o), carrots(_c), remaining_distance(_r) {}

  State(int _ct,int _c,double _r,int _d) :
    city(_ct), carrots(_c), remaining_distance(_r) {
    prev = 20;
    old = 20;
  }

  bool operator <(const State& s) const{
    return remaining_distance < s.remaining_distance;
  }
};

double dp[5001][21][21]; //dp[carrot][prev][now] := remaining distance
bool isok[21][21][21]; //cur,prev,old
double city_distance[21][21];

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

    memset(isok,true,sizeof(isok));
    for(int old = 0; old < total_cities; old++){
      for(int prev = 0; prev < total_cities; prev++){
	for(int cur = 0; cur < total_cities; cur++){
	  isok[cur][prev][old] = check(cur,prev,old,limit_rad,cities);
	  city_distance[cur][prev] = abs(cities[cur] - cities[prev]);
	}
      }
    }

    priority_queue<State> que;
    que.push(State(0,0,r,0));
    int max_carrots = 0;
    memset(dp,0,sizeof(dp));

    while(!que.empty()){
      State s = que.top();
      que.pop();

      if(dp[s.carrots][s.prev][s.city] >= s.remaining_distance - EPS) continue;
      dp[s.carrots][s.prev][s.city] = s.remaining_distance;
      max_carrots = max(s.carrots,max_carrots);

      int next_city,next_prev,next_old;
      for(int to=0;to<total_cities;to++){
	if(to == s.city) continue;

	next_city = to;
	next_prev = s.city;
	next_old = s.prev;
	if(!isok[next_city][next_prev][next_old]) continue;
	if(dp[s.carrots+1][s.city][to] >= s.remaining_distance - city_distance[next_city][next_prev] - EPS) continue;

	que.push(State(next_city,next_prev,next_old,
		       s.carrots+1,s.remaining_distance - city_distance[next_city][next_prev]));
      }
    }

    printf("%d\n",max_carrots);
  }
}
