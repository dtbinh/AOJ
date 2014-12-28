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
#include <complex>
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <double,double> P;
 
static const int tx[] = {+0,+1,+0,-1};
static const int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

typedef complex<double> Point;

namespace std {
  bool operator < (const Point& a, const Point& b) {
    return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
  }
}

double cross(const Point& a, const Point& b) {
  return imag(conj(a)*b);
}
double dot(const Point& a, const Point& b) {
  return real(conj(a)*b);
}

struct Line : public vector<Point> {
  Line(const Point &a, const Point &b) {
    push_back(a); push_back(b);
  }
};

int ccw(Point a, Point b, Point c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}

bool intersectSS(const Line &s, const Line &t) {
  return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
    ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}

Point crosspoint(const Line &l, const Line &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
  return m[0] + B / A * (m[1] - m[0]);
}

double compute_area(const Point &l,const Point &m){
  return abs(cross(l,m)) / 2.0;
}

bool is_equal(const Point &l,const Point &m){
  return ((abs(real(l) - real(m)) < EPS) && (abs(imag(l) - imag(m) < EPS)));
}

class State {
public:
  int pos;
  double cost;
  State(int pos,double cost) :
    pos(pos), cost(cost) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

double dp[3001];
vector<State> costs[3001];

int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n == 0) break;

    double vw,vc;    
    scanf("%lf %lf",&vw,&vc);
    vector<Point> points;
    for(int i = 0; i < n; i++){
      double x,y;
      scanf("%lf %lf",&x,&y);
      points.push_back(Point(x,y));
    }

    for(int i = 0; i <= 2000; i++){
      dp[i] = 1e10;
      costs[i].clear();
    }
    vector<double> x;
    for(int i = 0; i < n; i++){
      x.push_back(points[i].real());
      Line here2right(points[i],Point(1e10,points[i].imag()));
      for(int j = i + 1; j + 1 < n; j++){
	if(points[i].imag() + EPS >= points[j].imag()) break;
	Line target(points[j],points[j+1]);
	if(intersectSS(here2right,target)){
	  x.push_back(crosspoint(here2right,target).real());
	  break;
	}
      }

      Line here2left(Point(-1e10,points[i].imag()),points[i]);
      for(int j = i - 1; j - 1 >= 0; j--){
	if(points[i].imag() + EPS >= points[j].imag()) break;
	Line target(points[j-1],points[j]);
	if(intersectSS(here2left,target)){
	  x.push_back(crosspoint(here2left,target).real());
	  break;
	}
      }
    }
    sort(x.begin(),x.end());
    x.erase(unique(x.begin(),x.end()),x.end());

    for(int i = 0; i < n; i++){
      int from = lower_bound(x.begin(),x.end(),points[i].real() - EPS) - x.begin();
      if(i + 1 < n){
	int to = lower_bound(x.begin(),x.end(),points[i+1].real() - EPS) - x.begin();  
	costs[from].push_back(State(to,abs(points[i+1]-points[i])/vw));
	costs[to].push_back(State(from,abs(points[i+1]-points[i])/vw));
      }
      Line here2right(points[i],Point(1e10,points[i].imag()));
      for(int j = i + 1; j + 1 < n; j++){
	if(points[i].imag() + EPS >= points[j].imag()) break;
	Line target(points[j],points[j+1]);
	if(intersectSS(here2right,target)){
	  Point p = crosspoint(here2right,target);
	  int lhs = lower_bound(x.begin(),x.end(),points[j].real() - EPS) - x.begin();  
	  int mid = lower_bound(x.begin(),x.end(),p.real() - EPS) - x.begin();
	  int rhs = lower_bound(x.begin(),x.end(),points[j+1].real() - EPS) - x.begin();  

	  costs[from].push_back(State(mid,abs(p - points[i])/vc));
	  costs[mid].push_back(State(from,abs(p - points[i])/vc));

	  costs[lhs].push_back(State(mid,abs(p - points[j])/vw));
	  costs[mid].push_back(State(rhs,abs(p - points[j+1])/vw));

	  costs[mid].push_back(State(lhs,abs(p - points[j])/vw));
	  costs[rhs].push_back(State(mid,abs(p - points[j+1])/vw));
	  break;
	}
      }

      Line here2left(Point(-1e10,points[i].imag()),points[i]);
      for(int j = i - 1; j - 1 >= 0; j--){
	if(points[i].imag() + EPS >= points[j].imag()) break;
	Line target(points[j-1],points[j]);
	if(intersectSS(here2left,target)){
	  Point p = crosspoint(here2left,target);
	  int rhs = lower_bound(x.begin(),x.end(),points[j].real() - EPS) - x.begin();  
	  int mid = lower_bound(x.begin(),x.end(),p.real() - EPS) - x.begin();
	  int lhs = lower_bound(x.begin(),x.end(),points[j-1].real() - EPS) - x.begin();  

	  costs[from].push_back(State(mid,abs(p - points[i])/vc));
	  costs[mid].push_back(State(from,abs(p - points[i])/vc));

	  costs[rhs].push_back(State(mid,abs(p - points[j])/vw));
	  costs[mid].push_back(State(rhs,abs(p - points[j])/vw));

	  costs[mid].push_back(State(lhs,abs(p - points[j-1])/vw));
	  costs[lhs].push_back(State(mid,abs(p - points[j-1])/vw));
	  break;
	}
      }
    }
    
    int goal_pos = x.size() - 1;
    dp[0] = 0.0;
    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(0,0));

    while(!que.empty()){
      State s = que.top();
      que.pop();
      if(s.pos == goal_pos) break;

      for(int i = 0; i < costs[s.pos].size(); i++){
	int next_pos = costs[s.pos][i].pos;
	double next_cost = costs[s.pos][i].cost;
	if(dp[next_pos] > s.cost + next_cost){
	  dp[next_pos] = s.cost + next_cost;
	  que.push(State(next_pos,s.cost + next_cost));
	}
      }
    }
    printf("%.7lf\n",dp[goal_pos]);
  }
}
