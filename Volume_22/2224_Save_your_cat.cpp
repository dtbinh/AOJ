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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

class UnionFindTree{
private:
  int _size;
  int* _parent;
  int* _rank;
public:
  UnionFindTree(int n){
    _size = n;
    _parent = new int[_size]();
    _rank = new int[_size]();
    for(int i = 0; i < _size; i++){
      _parent[i] = i;
      _rank[i] = 0;
    }
  }

  ~UnionFindTree(){
    delete[] _parent;
    delete[] _rank;
  }

  int find(int child){
    int next = _parent[child];
    if(next == child) return child;
    else return find(next);
  }

  bool same(int lhs,int rhs){
    lhs = find(lhs);
    rhs = find(rhs);
    return (lhs == rhs);
  }
  
  bool unite(int lhs,int rhs){
    lhs = find(lhs);
    rhs = find(rhs);
    if(same(lhs,rhs)) return false;
    
    if(_rank[lhs] < _rank[rhs]){
      _parent[rhs] = lhs;
      _rank[lhs] += _rank[rhs];
    }
    else {
      _parent[lhs] = rhs;
      _rank[rhs] += _rank[lhs];
    }
    return true;
  }

};

class State {
public:
  int _from,_to;
  double _distance;
  State(int from,int to,double distance)
    : _from(from),_to(to),_distance(distance) {}
  bool operator<(const State& s) const {
    return _distance < s._distance;
  }
  bool operator>(const State& s) const {
    return _distance > s._distance;
  }
};

int main(){
  int num_of_magical_piles;
  int num_of_magical_fences;
  while(~scanf("%d %d",
	       &num_of_magical_piles,
	       &num_of_magical_fences)){
    
    vector<P> piles;
    for(int pile_i = 0; pile_i < num_of_magical_piles; pile_i++){
      int x,y;
      scanf("%d %d",&x,&y);
      piles.push_back(P(x,y));
    }

    double sum = 0;
    priority_queue<State,vector<State>,less<State> > que;

    for(int fence_i = 0; fence_i < num_of_magical_fences; fence_i++){
      int from,to;
      scanf("%d %d",&from,&to);
      from--; to--;
      int from_x = piles[from].first;
      int from_y = piles[from].second;

      int to_x = piles[to].first;
      int to_y = piles[to].second;

      double distance = sqrt((double)((from_x - to_x) * (from_x - to_x)
				      + (from_y - to_y) * (from_y - to_y)));
      sum += distance;
      que.push(State(from,to,distance));
    }

    UnionFindTree uft(num_of_magical_piles);
    double after_ruined = 0;
    while(!que.empty()){
      State s = que.top();
      que.pop();
      if(uft.same(s._from ,s._to)){
	continue;
      }
      uft.unite(s._from,s._to);
      after_ruined += s._distance;
    }
    printf("%lf\n",sum - after_ruined);
  }
}
