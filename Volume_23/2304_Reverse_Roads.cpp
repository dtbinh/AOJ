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

int path[301][301];

class Edge{
public:
  int _to;
  int _capacity;
  int _reverse;
  int _id;
  Edge(int to,int capacity,int reverse) :
    _to(to), _capacity(capacity), _reverse(reverse) {}
  Edge(int to,int capacity,int reverse,int id) :
    _to(to), _capacity(capacity), _reverse(reverse),_id(id) {}
};

class FordFulkerson {
private:
  int _n;
  bool *_used;
  vector<Edge>* _edges;
  void fill_used(){
    fill(_used,_used + (_n+1) ,false);
  }
public:
  FordFulkerson(int n){
    _n = n;
    _edges = new vector<Edge>[n+1];
    _used = new bool[n+1]();
  }

  void add_edge(int from,int to,int capacity,int id){
    _edges[from].push_back(Edge(to,capacity,_edges[to].size(),id));
    _edges[to].push_back(Edge(from,capacity,_edges[from].size()-1,-id));
  }

  int dfs(int current,int sink,int flow){
    if(current == sink) return flow;
    _used[current] = true;
    for(int i=0;i<_edges[current].size();i++){
      Edge& e = _edges[current][i];
      int to = e._to;
      if(_used[to] || e._capacity <= 0) continue;

      int d = dfs(to,sink,min(flow,e._capacity));
      if(d <= 0) continue;
      
      e._capacity -= d;
      _edges[to][e._reverse]._capacity += d;
      path[current][to] -= d;
      path[to][current] += d;
      return d;
    }
    
    return 0;
  }

  int compute_max_flow(int source,int sink){
    int res = 0;
    while(true){
      fill_used();
      int tmp = dfs(source,sink,INF);
      if(tmp == 0) break;
      res += tmp;
    }
    return res;
  }

  set<int> compute_reverse(const vector<P>& roads,int path[301][301]){
    set<int> res;
    for(int road_i = 0; road_i < roads.size();road_i++){
      int from = roads[road_i].first;
      int to = roads[road_i].second;

      if(path[to][from] == 0){
	 res.insert(road_i + 1);
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

    memset(path,0,sizeof(path));
    vector<P> roads;
    for(int road_i = 1; road_i <= num_of_roads; road_i++){
      int from,to;
      scanf("%d %d",&from,&to);
      fordfulkerson.add_edge(from,to,1,road_i);
      path[from][to] = path[to][from] = 1;
      roads.push_back(P(from,to));
    }

    int source,sink;
    scanf("%d %d",&source,&sink);
    cout << fordfulkerson.compute_max_flow(source,sink) << endl;
    
    set<int> res = fordfulkerson.compute_reverse(roads,path);
    cout << res.size() << endl;
    for(set<int>::iterator it = res.begin(); it != res.end(); it++){
      cout << *it << endl;
    }
  }
}
