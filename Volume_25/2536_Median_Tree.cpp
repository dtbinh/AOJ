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

class UnionFindTree{
private:
  int* mParent;
  int* mRank;
  int mSize;

public:
  UnionFindTree(int n){
    mSize = n;
    mParent = new int[n];
    mRank = new int[n];

    for(int i=0; i < n; i++){
      mParent[i] = i;
      mRank[i] = 0;
    }
  }

  bool same(int lhs,int rhs){
    return (find(lhs) == find(rhs) ? true : false);
  }

  int find(int pos){
    if(pos == mParent[pos]) return pos;
    return find(mParent[pos]);
  }
  
  void unite(int lhs,int rhs){
    lhs = find(lhs);
    rhs = find(rhs);
    
    if(mRank[lhs] > mRank[rhs]){
      mParent[lhs] = rhs;
      mRank[lhs] = 0;
      mRank[rhs]++;
    }
    else{
      mParent[rhs] = lhs;
      mRank[rhs] = 0;
      mRank[lhs]++;
    }
  }

  int size() const{
    return mSize;
  }
};

int main(){
  int num_of_nodes;
  int num_of_edges;
  while(~scanf("%d",&num_of_nodes,&num_of_edges)){
    if(num_of_nodes == 0 && num_of_edges == 0) break;

    for(int edge_idx = 0; edge_idx < num_of_edges; edge_idx++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);
    }
  }
}

