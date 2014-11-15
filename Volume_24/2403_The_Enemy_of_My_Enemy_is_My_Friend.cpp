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

int country2idx(map<string,int>& dict,string country){
  int idx = dict.size();
  if(dict.find(country) == dict.end()){
    dict[country] = idx;
    return idx;
  }
  return dict[country];
}

vector<int> edges[41];
bool used[41];
int power[41];

bool can_unite(int node){
  if(used[node]) return false;
  for(int i=0;i<edges[node].size();i++){
    if(used[edges[node][i]]) return false;
  }
  return true;
}

int dfs(int current,int sum,const vector<int>& subset){
  if(current == subset.size()) return sum;

  int res = sum;
  int next = subset[current];
  if(can_unite(next)){
    used[next] = true;
    res = max(res,dfs(current+1,sum + power[next],subset));
    used[next] = false;
  }
  res = max(res,dfs(current+1,sum,subset));
  return res;
}

class UnionFindTree {
private:
  int parent[41];
  int rank[41];
public:
  UnionFindTree(){
    for(int i = 0; i <= 40; i++){
      parent[i] = i;
      rank[i] = 0;
    }
  }

  void unite(int lhs,int rhs) {
    lhs = find(lhs);
    rhs = find(rhs);
    if(lhs == rhs) return;
    
    if(rank[lhs] < rank[rhs]){
      parent[rhs] = lhs;
      rank[rhs]++;
    }
    else{
      parent[lhs] = rhs;
      rank[lhs]++;
    }
  }

  int find(int current){
    if(current == parent[current]) return current;
    else find(parent[current]);
  }
};

int N;
void make_subset(UnionFindTree* uft,int root,vector<int>& subset){
  for(int i = 0; i < N; i++){
    if(uft->find(i) == root){
      subset.push_back(i);
    }
  }
}

int main(){
  while(~scanf("%d",&N)){
    if(N == 0) break;
    for(int i = 0; i <= 40; i++){
      edges[i].clear();
    }
    UnionFindTree uft;
    map<string,int> dict;
    for(int country_i = 0; country_i < N; country_i++){
      string country;
      int tmp_power;
      cin >> country >> tmp_power;
      int adjacent_countries;
      cin >> adjacent_countries;

      int root = country2idx(dict,country);
      power[root] = tmp_power;
      for(int adj_i = 0; adj_i < adjacent_countries; adj_i++){
	string adj_country;
	cin >> adj_country;
	int child = country2idx(dict,adj_country);
	edges[root].push_back(child);
	uft.unite(root,child);
      }
    }

    bool tree[41];
    memset(tree,false,sizeof(tree));

    int res = 0;
    for(int i = 0; i < N; i++){
      if(tree[uft.find(i)]) continue;
      tree[uft.find(i)] = true;
      int tmp = 0;
      vector<int> subset;
      make_subset(&uft,uft.find(i),subset);
      memset(used,false,sizeof(used));
      if(i == 0){
	used[0] = true;
	tmp = max(tmp,dfs(0,power[0],subset));
      }
      else{
	tmp = max(tmp,dfs(0,0,subset));
      }
      res += tmp;
    }
    printf("%d\n",res);
  }
}
