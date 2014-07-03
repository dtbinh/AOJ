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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;


int str2num(const string& station,map<string,int>& dict){
  if(dict.find(station) == dict.end()){
    int idx = dict.size();
    dict[station] = idx;
    return idx;
  }
  return dict[station];
}

int dp[1001][1001];

int main(){
  int total_stations;
  int total_lines;

  while(~scanf("%d %d",
	       &total_stations,
	       &total_lines)){
    if(total_lines == 0) break;

    map<string,int> dict;
    string shirokuro_location;
    string R2d_location;
    string Aizu_location;

    cin >> shirokuro_location >> R2d_location >> Aizu_location;
    memset(dp,0x3f,sizeof(dp));

    for(int line_idx = 0; line_idx < total_lines; line_idx++){
      string from,to;
      int distance;
      int delay;
      cin >> from >> to >> distance >> delay;
      int cost = distance / 40 + delay;
      dp[str2num(from,dict)][str2num(to,dict)] = cost;
      dp[str2num(to,dict)][str2num(from,dict)] = cost;
    }

    for(int k=0;k<total_stations;k++){
      for(int i=0;i<total_stations;i++){
	for(int j=0;j<total_stations;j++){
	  dp[i][j] = min(dp[i][j],dp[i][k] + dp[k][j]);
	}
      }
    }

    printf("%d\n",dp[str2num(shirokuro_location,dict)][str2num(R2d_location,dict)]
	   + dp[str2num(R2d_location,dict)][str2num(Aizu_location,dict)]);
  }
}
