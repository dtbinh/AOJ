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

class UnionFindTree {
private:
  int* par;
public:
  UnionFindTree(int n){
    par = new int[n]();
    for(int i=0;i<n;i++){
      par[i] = i;
    }
  }

  ~UnionFindTree(){
    delete[] par;
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
    par[x] = y;
  }

  bool same(int x,int y){
    return find(x) == find(y);
  }
};

int power[100001];

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

	power[players[1]] = power[players[0]] + up;
	power[players[1]] += up;
	power[players[0]] += up;
	
	uft.unite(players[0],players[1]);
      }
      else if(command == "COMPARE"){
	int players[2];
	cin >> players[0] >> players[1];
	if(!uft.same(players[0],players[1])){
	  printf("WARNING\n");
	}
	else{
	  printf("%d\n",power[players[1]] - power[players[0]]);
	}
      }
    }
  }
}
