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

static const int MAX_BUCKET = 1000;
vector<int> bucket[MAX_BUCKET];

int compute_dist(int dist,int lhs,int rhs){
  return min(dist-abs(lhs-rhs),abs(lhs-rhs));
}

int main(){
  int total_dist,store_num,order_num;
  while(~scanf("%d",&total_dist)){
    if(total_dist == 0) break;
    scanf("%d",&store_num);
    scanf("%d",&order_num);

    vector<int> store;
    store.push_back(0);
    for(int i=0;i<store_num-1;i++){
      int num;
      scanf("%d",&num);
      store.push_back(num);
    }
    sort(store.begin(),store.end());

    int cost = 0;
    for(int i=0;i<order_num;i++){
      int num;
      scanf("%d",&num);

      int idx = lower_bound(store.begin(),store.end(),num) - store.begin();
      int min_dist = compute_dist(total_dist,store[idx],num);
      
      for(int j=idx-1;j>=0;j--){
	min_dist = min(min_dist,compute_dist(total_dist,store[j],num));
      }
      cost += min_dist;
    }
    printf("%d\n",cost);
  }
}
