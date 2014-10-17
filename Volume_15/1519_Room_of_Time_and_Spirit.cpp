#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
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
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int power[100001];

struct Node{
  int par;
  int diff;
  Node() : par(0),diff(0) {}
  Node(int p,int d) : par(p),diff(d) {}
};

class UnionFindTree {
private:
  Node* nodes;
public:
  UnionFindTree(int n){
    nodes = new Node[n]();
    for(int i=0;i<n;i++){
      nodes[i].par = i;
    }
  }

  ~UnionFindTree(){
    delete[] nodes;
  }

  Node find(int x){
    if(nodes[x].par == x){
      return nodes[x];
    } else {
      Node ret = find(nodes[x].par);
      return nodes[x] = Node(ret.par,ret.diff + nodes[x].diff);
    }
  }

  void unite(int x,int y,int up){
    Node rx = find(x);
    Node ry = find(y);
    if (rx.par == ry.par){
      return;
    }

    //rx.par == rx
    //ry.par == ry
    nodes[rx.par].par = ry.par;
    nodes[rx.par].diff = (power[y] - power[x] - up) + (ry.diff - rx.diff);
  }

  int dist(int x,int y){
    Node rx = find(x);
    Node ry = find(y);
    if(rx.par != ry.par) return INF;
    return (ry.diff - rx.diff) + (power[y] - power[x]);
  }

  bool same(int x,int y){
    return find(x).par == find(y).par;
  }
};

int main(){
  int total_players;
  int total_queries;
  while(~scanf("%d %d",
	       &total_players,
	       &total_queries)){
    
    UnionFindTree uft(total_players+1);
    memset(power,0,sizeof(power));
    for(int query_i = 0; query_i <total_queries; query_i++){
      string command;
      cin >> command;
      if(command == "IN"){
	int players[2];
	int up;
	cin >> players[0] >> players[1] >> up;
	power[players[0]] += up;
	power[players[1]] += up;
	uft.unite(players[0],players[1],up);
      }
      else if(command == "COMPARE"){
	int players[2];
	cin >> players[0] >> players[1];
	if(!uft.same(players[0],players[1])){
	  printf("WARNING\n");
	}
	else{
	  printf("%d\n",uft.dist(players[0],players[1]));
	}
      }
    }
  }
}
