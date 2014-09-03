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
  int _from;
  int _to;
  int _friendliness;
  RelationShip(int from,int to,int friendliness) :
    _from(from), _to(to), _friendliness(friendliness) {}
  bool operator<(const RelationShip &r) const {
    return _friendliness < r._friendliness;
  }
  bool operator>(const RelationShip &r) const {
    return _friendliness > r._friendliness;
  }
};

class UnionFindTree {
private:
  int* par;
  int* rank;
  int* weight;
public:
  UnionFindTree(int n){
    par = new int[n]();
    rank = new int[n]();
    weight = new int[n]();
    for(int i=0;i<n;i++){
      par[i] = i;
      rank[i] = 0;
      weight[i] = 1;
    }
  }

  ~UnionFindTree(){
    delete[] rank;
    delete[] par;
    delete[] weight;
  }

  int find(int x){
    if(par[x] == x){
      return x;
    } else {
      return par[x] = find(par[x]);
    }
  }

  void unite(int x,int y){
    x = find(x);
    y = find(y);
    if (x == y) return;

    if(rank[x] < rank[y]){
      par[x] = y;
      weight[y] += weight[x];
    } else {
      par[y] = x;
      weight[x] += weight[y];
      if (rank[x] == rank[y]) rank[x]++;
    }
  }

  int count(int x){
    return weight[find(x)];
  }
  bool same(int x,int y){
    return find(x) == find(y);
  }
};

int main(){
  int total_rabbits;
  int total_pairs;
  while(~scanf("%d %d",&total_rabbits,&total_pairs)){
    UnionFindTree uft(total_rabbits);

    priority_queue<RelationShip> que;
    for(int pair_i = 0; pair_i < total_pairs; pair_i++){
      int from,to,friendliness;
      scanf("%d %d %d",&from,&to,&friendliness);
      from--; to--;
      que.push(RelationShip(from,to,friendliness));
    }


    int res = 0;
    while(!que.empty()){
      RelationShip rs = que.top();
      que.pop();
      if(uft.same(rs._from,rs._to)) continue;
      uft.unite(rs._from,rs._to);
      res += rs._friendliness;
    }

    printf("%d\n",res);
  }
}
