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

class RelationShip{
public:
  int _to;
  int _friendliness;
  RelationShip(int to,int friendliness) :
    _to(to), _friendliness(friendliness) {}
  bool operator<(const RelationShip &r) const {
    return _friendliness < r._friendliness;
  }
  bool operator>(const RelationShip &r) const {
    return _friendliness > r._friendliness;
  }
};


bool used[101];
vector<RelationShip> edges[101];
int idx[101][101];
int total_rabbits;
int total_pairs;

int dfs(int last){
  int res = 0;

  int sum = 0;
  for(int orig=0; orig <= last; orig++){
    if(!used[orig]) continue;

    int tmp = INF;
    for(int next_i = 0; next_i < edges[orig].size(); next_i++){
      int next = edges[orig][next_i]._to;
      if(!used[next]) continue;
      tmp = min(tmp,edges[orig][next_i]._friendliness);
    }
    if(tmp != INF) sum += tmp;
  }
  
  res = max(sum,res);

  for(int next=last + 1; next < total_rabbits; next++){
    bool isok = true;
    for(int prev = 0; prev <= last; prev++){
      if(used[prev] && idx[prev][next] == -1) {
	isok = false;
	break;
      }
    }

    if(!isok) continue;
    used[next] = true;
    res = max(res,dfs(next));
    used[next] = false;
  }
  return res;
}

int main(){
  while(~scanf("%d %d",&total_rabbits,&total_pairs)){
    for(int i=0;i<total_rabbits;i++){
      edges[i].clear();
    }
    memset(used,false,sizeof(used));   
    memset(idx,-1,sizeof(idx));

    for(int pair_i = 0; pair_i < total_pairs; pair_i++){
      int from,to,friendliness;
      scanf("%d %d %d",&from,&to,&friendliness);
      from--; to--;
      edges[from].push_back(RelationShip(to,friendliness));
      edges[to].push_back(RelationShip(from,friendliness));
      idx[from][to] = edges[from].size() - 1;
      idx[to][from] = edges[to].size() - 1;
    }

    cout << dfs(-1) << endl;
  }
}
