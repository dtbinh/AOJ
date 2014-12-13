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

typedef complex<double> Point;
const static double EPS = 1e-12;
const static int MAX_V = 501;

class UnionFindTree {
  int* par;
  int* rank;
  UnionFindTree(int N){
    par = new int[N];
    rank = new int[N];
    for(int i = 0; i < N; i++){
      par[i] = i;
      rank[i] = 0;
    }
  }
  ~UnionFindTree(){
    delete[] par;
    delete[] rank;
  }

  int find(int u){
    if(par[u] == u) return u;
    return find(par[u]);
  }

  bool unite(int u,int v){
    u = find(u);
    v = find(v);
    if(u == v) return false;

    if(rank[u] >= rank[v]){
      par[u] = v;
      rank[v] += rank[u] + 1;
    }
    else{
      par[v] = u;
      rank[u] += rank[v] + 1;
    }
    return true;
  }
};

int main(){
  
}
