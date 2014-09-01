#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-8;

class Edge{
public:
  int _to;
  int _capacity;
  int _reverse;
  Edge(int to,int capacity,int reverse) :
    _to(to), _capacity(capacity), _reverse(reverse) {}
};

class FordFulkerson {
private:
  int _n;
  bool* _used;
  vector<Edge>* _edges;
  map<P,int> _id;
public:
  FordFulkerson(int n){
    _n = n;
    _used = new bool[n+1]();
    _edges = new vector<Edge>[n+1];
  }
  void set_id(map<P,int> id){
    _id = id;
  }
  
  void add_edge(int from,int to,int capacity = 1){
    _edges[from].push_back(Edge(to,capacity,_edges[to].size()));
    _edges[to].push_back(Edge(from,capacity,_edges[from].size()-1));
  }

  int dfs(int current,int sink,int flow){
    if(current == sink) return flow;
    _used[current] = true;
    for(int i=0;i<_edges[current].size();i++){
      int to = _edges[current][i]._to;
      if(_used[to]) continue;

      int d = dfs(to,sink,min(flow,_edges[current][i]._capacity));
      if(d <= 0) continue;
      
      _edges[current][i]._capacity -= d;
      _edges[to][_edges[current][i]._reverse]._capacity += d;
      return d;
    }
    
    return 0;
  }

  int compute_max_flow(int source,int sink){
    int res = 0;
    while(true){
      int tmp = dfs(source,sink,INF);
      if(tmp == 0) break;
      res += tmp;
    }
    return res;
  }

  set<int> compute_reverse(){
    set<int> res;
    for(map<P,int>::iterator it = _id.begin(); it != _id.end(); it++){
      int from = it->first.first;
      int to = it->first.second;
      for(int i = 0; i < _edges[from].size();i++){
      	if(to == _edges[from][i]._to){
	  if(_edges[from][i]._capacity > 0){
	    res.insert(it->second);
	  }
      	}
      }
    }
    return res;
  }
};

int main(){
  int num_of_crossings;
  int num_of_roads;
  while(~scanf("%d %d",
	       &num_of_crossings,
	       &num_of_roads)){
    
    FordFulkerson fordfulkerson(num_of_crossings);
    map<P,int> id;
    for(int road_i = 0; road_i < num_of_roads; road_i++){
      int from,to;
      scanf("%d %d",&from,&to);
      fordfulkerson.add_edge(from,to);
      // fordfulkerson.add_edge(to,from);
      id[P(from,to)] = id.size();
    }
    int source,sink;
    scanf("%d %d",&source,&sink);
    cout << fordfulkerson.compute_max_flow(source,sink) << endl;
    
    fordfulkerson.set_id(id);
    set<int> res = fordfulkerson.compute_reverse();
    cout << res.size() << endl;
    for(set<int>::iterator it = res.begin(); it != res.end(); it++){
      cout << *it << endl;
    }
  }
}
