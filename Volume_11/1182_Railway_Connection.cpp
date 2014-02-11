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

class Edge {
public:
  int dst;
  int distance;
  int company;
  Edge(int _dst,int _dist,int _c) : dst(_dst),distance(_dist),company(_c){}
};

class Company{
public:
  int points[51];
  int slopes[51];
  Company(int _p[51],int _s[51]){
    memcpy(points,_p,sizeof(int)*51);
    memcpy(slopes,_s,sizeof(int)*51);
  }
  Company(){}
};

class State{
public:
  int station;
  int fare;
  State(int _s,int _f) : station(_s), fare(_f) {}
  State() : station(0),fare(0) {}
  bool operator<(const State& s) const{
    return fare < s.fare;
  }
  bool operator>(const State& s) const{
    return fare > s.fare;
  }
};

int compute_fare(int z,int points[51],int total_points,int slopes[51]){
  if(z == 0) return 0;
  int idx = lower_bound(points,points+(total_points+1),z) - points;
  return compute_fare(z-1,points,total_points,slopes) + slopes[idx];
}

void dfs(int org,int company,int distance ,int pos,int dp[101][101],
	 const vector<Edge> edges[101],Company companies[21],int total_point[21],bool visited[101]){
  if(visited[pos]) return;
  visited[pos] = true;
  for(int i=0;i<edges[pos].size();i++){
    int fare = compute_fare(distance,
			    companies[edges[pos][i].company].points,
			    total_point[edges[pos][i].company],
			    companies[edges[pos][i].company].slopes);
    if(company != -1 && edges[pos][i].company != company) return;
    dp[org][pos] = min(dp[org][pos],fare);
    dfs(org,edges[pos][i].company,distance + edges[pos][i].distance,edges[pos][i].dst,dp,edges,companies,total_point,visited);
  }
}

int main(){
  int total_stations;
  int total_lines;
  int total_companies;
  int start_station;
  int goal_station;
  while(~scanf("%d %d %d %d %d",
	       &total_stations,
	       &total_lines,
	       &total_companies,
	       &start_station,
	       &goal_station)){
    if(total_stations == 0 
       && total_lines == 0
       && total_companies == 0
       && start_station == 0
       && goal_station == 0) break;

    int total_point[21];

    vector<Edge> edges[101];
    Company companies[21];
    for(int line_idx = 1; line_idx<=total_lines;line_idx++){
      int stations[2];
      int distance;
      int company;
      scanf("%d %d %d %d",&stations[0],&stations[1],&distance,&company);
      edges[stations[0]].push_back(Edge(stations[1],distance,company));
      edges[stations[1]].push_back(Edge(stations[0],distance,company));
    }

    for(int company_idx = 1; company_idx <= total_companies;company_idx++){
      scanf("%d",total_point + company_idx);
    }
    for(int company_idx = 1; company_idx <= total_companies;company_idx++){
      int points[51];
      points[0] = 0;
      points[total_point[company_idx]] = INF;
      for(int point_idx = 1; point_idx <= total_point[company_idx]-1; point_idx++){
	int point;
	scanf("%d",points + point_idx);
      }
      int slopes[51];
      slopes[0] = INF;
      for(int point_idx = 1; point_idx <= total_point[company_idx]; point_idx++){
	scanf("%d",slopes + point_idx);
      }

      companies[company_idx] = Company(points,slopes);
      // for(int z=1;z<=9;z++){
      // 	cout <<  << endl;
      // }
    }

    int dp[101][101];
    memset(dp,0x3f,sizeof(dp));

    for(int i=1;i<=total_stations;i++){
      dp[i][i] = 0;
    }

    bool visited[101];
    for(int start=1;start<=total_stations; start++){
      memset(visited,false,sizeof(visited));
      dfs(start,-1,0,start,dp,edges,companies,total_point,visited);
    }

    for(int start=1;start<=total_stations; start++){
      for(int i=0;i<edges[start].size();i++){
	dp[edges[start][i].dst][start]
	  = dp[start][edges[start][i].dst]
	  = min(dp[start][edges[start][i].dst],
		compute_fare(edges[start][i].distance,
			     companies[edges[start][i].company].points,
			     total_point[edges[start][i].company],
			     companies[edges[start][i].company].slopes));
	
      }
    }

    for(int mid=1;mid<=total_stations;mid++){
      for(int start=1;start<=total_stations;start++){
	for(int end=1;end<=total_stations;end++){
	  dp[start][end] = min(dp[start][end],dp[start][mid] + dp[mid][end]);
	}
      }
    }

    printf("%d\n",dp[start_station][goal_station] >= INF ? -1 : dp[start_station][goal_station]);
  }
}
