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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 

static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-10;

int total_players;
int total_messages;

int find(int idx,int parent[21]){
  if(parent[idx] == idx) return idx;
  else return find(parent[idx],parent);
}


vector<int> child[21];
int level[21];
bool visited[21];

class State {
public:
  int node;
  int level;
  State(int _n,int _l)
    : node(_n), level(_l) {}
  bool operator<(const State& s) const{
    return level < s.level;
  }
  bool operator>(const State& s) const{
    return level > s.level;
  }
};

int bfs(int root){
  queue<State> que;
  que.push(State(root,0));
  while(!que.empty()){
    State current = que.front();
    que.pop();

    for(int i=0;i<child[current.node].size();i++){
      int next = child[current.node][i];
      level[next] = max(current.level + 1,level[next]);
      que.push(State(next,current.level + 1));
    }
  }
}

int main(){
  while(~scanf("%d %d",&total_players,&total_messages)){
    for(int i=1;i<=20;i++){
      child[i].clear();
    }

    bool has_parent[21];

    memset(has_parent,false,sizeof(has_parent));
    for(int i=1;i<=20;i++){
      level[i] = 1;
    }
    
    for(int message_idx = 0; message_idx < total_messages; message_idx++){
      int x,y;
      //x entered the room earlier than y
      scanf("%d %d",&x,&y);
      child[x].push_back(y);
      has_parent[y] = true;
    }

    memset(visited,false,sizeof(visited));

    for(int i=1;i<=total_players;i++){
      if(has_parent[i]) continue;
      child[0].push_back(i);
    }

    bfs(0);
    
    vector<State> res;
    for(int i=1;i<=total_players;i++){
      res.push_back(State(i,level[i]));
    }
    sort(res.begin(),res.end());
    for(int i=0;i<res.size();i++){
      printf("%d\n",res[i].node);
    }
  }
}
