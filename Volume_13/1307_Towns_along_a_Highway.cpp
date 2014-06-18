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

int N;
int freq[401];
int dist[401];

int compute_max(){
  for(int i=400;i>=0;i--){
    if(freq[i] > 0) return i;
  }
  return -1;
}

void dfs(int target,vector<int>& points){

  if(target == N){
    vector<int> tmp = points;
    sort(tmp.begin(),tmp.end());
    for(int i=0;i+1<tmp.size();i++){
      printf("%d ",tmp[i+1] - tmp[i]);
    }
    printf("\n");
    return;
  }
  
  int max_pos = compute_max();
  bool isok = true;
  points.push_back(max_pos);
  for(int i=0;i<target;i++){
    if(freq[abs(points[i] - max_pos)] == 0) {
      isok = false;
      for(int j=i-1;j>=0;j--){
	freq[abs(points[j] - max_pos)]++;
      }
      break;
    }
    freq[abs(points[i] - max_pos)]--;
  }

  if(isok){
    dfs(target+1,points);
    for(int i=0;i<target;i++){
      freq[abs(points[i] - max_pos)]++;
    }
  }

  points.pop_back();

  int inv_pos = points[1] - max_pos;
  points.push_back(inv_pos);
  bool isok_inv = true;
  points[target] = inv_pos;
  for(int i=0;i<target;i++){
    if(freq[abs(points[i] - inv_pos)] == 0) {
      isok_inv = false;
      for(int j=i-1;j>=0;j--){
	freq[abs(points[j] - inv_pos)]++;
      }
      break;
    }
    freq[abs(points[i] - inv_pos)]--;
  }

  if(isok_inv){
    dfs(target+1,points);
    for(int i=0;i<target;i++){
      freq[abs(points[i] - inv_pos)]++;
    }
  }

  points.pop_back();
}

int main(){

  while(~scanf("%d",&N)){
    if(N == 0) break;

    memset(freq,0,sizeof(freq));
    for(int i=0;i < N * (N-1) / 2;i++){
      scanf("%d",&dist[i]);
      freq[dist[i]]++;
    }
    sort(dist,dist + N * (N-1)/2);

    freq[dist[N*(N-1)/2 - 1]]--;
    vector<int> points;
    points.push_back(0);
    points.push_back(dist[N*(N-1)/2 - 1]);
    
    dfs(2,points);
    cout << "-----" << endl;
  }
}
