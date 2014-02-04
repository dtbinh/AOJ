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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int gcd(int a,int b){
  if(b==0) return a;
  return gcd(b,a%b);
}

class BipartiteGraph {
private:
  int V;
  vector<int>* G;
  int* match;
  bool* used;
public:
  BipartiteGraph(int n){
    V = n;
    match = new int[n];
    used = new bool[n];
    G = new vector<int>[n];
  }

  ~BipartiteGraph(){
    delete[] match;
    delete[] used;
    delete[] G;
  }

  void add_edge(int u,int v){
    G[u].push_back(v);
    G[v].push_back(u);
  }

  bool dfs(int v){
    used[v] = true;
    for(int i=0;i<G[v].size();i++){
      int u = G[v][i];
      int w = match[u];
      if(w < 0 || (!used[w] && dfs(w))){
	match[v] = u;
	match[u] = v;
	return true;
      }
    }
    return false;
  }

  int bipartite_matching() {
    int res = 0;
    fill(match,match+V,-1);
    for(int v=0; v < V;v++){
      if(match[v] < 0){
	fill(used,used+V,false);
	if(dfs(v)){
	  res++;
	}
      }
    }
    return res;
  }
};

int main(){
  int total_blue_cards;
  int total_red_cards;
  while(~scanf("%d %d",&total_blue_cards,&total_red_cards)){
    if(total_blue_cards == 0 && total_red_cards == 0) break;

    int red_cards[501];
    int blue_cards[501];

    for(int blue_card_idx = 0; blue_card_idx < total_blue_cards; blue_card_idx++){
      int num;
      scanf("%d",&num);
      blue_cards[blue_card_idx] = num;
    }
    for(int red_card_idx = 0; red_card_idx < total_red_cards; red_card_idx++){
      int num;
      scanf("%d",&num);
      red_cards[red_card_idx] = num;
    }

    BipartiteGraph bg(total_blue_cards + total_red_cards);
    for(int blue_card_idx = 0; blue_card_idx < total_blue_cards; blue_card_idx++){
      for(int red_card_idx = 0; red_card_idx < total_red_cards; red_card_idx++){
	int div = gcd(blue_cards[blue_card_idx],red_cards[red_card_idx]);
	if(div != 1){
	  bg.add_edge(blue_card_idx,total_blue_cards+red_card_idx);
	}
      }
    }

    printf("%d\n",bg.bipartite_matching());
  }
}
