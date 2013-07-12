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

void make_bucket(const vector<int>& store){
  int n = floor(sqrt(store.size())+EPS);

  int bucket_num = 0;
  vector<int> nums;
  for(int i=0;i<store.size();i++){
    if(i != 0 && i % n == 0){
      bucket_num++;
    }
    bucket[bucket_num].push_back(store[i]);
  }
}

void clear_bucket(){
  for(int i=0;i<MAX_BUCKET;i++){
    bucket[i].clear();
  }
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
    
    clear_bucket();
    make_bucket(store);
    int b_num = floor(sqrt(store.size()) + EPS);
    
    int cost = 0;
    for(int i=0;i<order_num;i++){
      int num;
      scanf("%d",&num);
      int minv = numeric_limits<int>::max();
      vector<int> min_bucket_idx;

      for(int j=0;j<store.size()/b_num;j++){
	int dist = min(compute_dist(total_dist,num,bucket[j][0]),
		       compute_dist(total_dist,num,bucket[j][bucket[j].size()-1]));
	if(dist < minv){
	  minv = dist;
	  min_bucket_idx.clear();
	  min_bucket_idx.push_back(j);
	}
	else if(dist == minv){
	  min_bucket_idx.push_back(j);
	}
      }

      for(int j=0;j<min_bucket_idx.size();j++){
	int idx = min_bucket_idx[j];
	for(int k=0;k<bucket[idx].size();k++){
	  // cout << "store" << bucket[idx][k] << endl;
	  int dist = compute_dist(total_dist,num,bucket[idx][k]);
	  minv = min(minv,dist);
	}
      }
      cost += minv;
    }
    printf("%d\n",cost);
  }
}
