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
  int total_points;
  Company(int _p[51],int _s[51],int _t) : total_points(_t){
    memcpy(points,_p,sizeof(int)*51);
    memcpy(slopes,_s,sizeof(int)*51);
  }
  Company(){}
};

int fares[21][20001];
int dist[21][101][101];

int compute_fare(int company,int z,const Company companies[21]){
  if(z == 0) return 0;
  if(fares[company][z] != -1) return fares[company][z];

  int idx = lower_bound(companies[company].points,companies[company].points + (companies[company].total_points + 1),z) - companies[company].points;
  return (fares[company][z] = (compute_fare(company,z-1,companies) + companies[company].slopes[idx]));
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

    memset(fares,-1,sizeof(fares));
    int total_point[21];

    vector<Edge> edges[101];
    Company companies[21];

    memset(dist,0x3f,sizeof(dist));

    for(int line_idx = 1; line_idx<=total_lines;line_idx++){
      int stations[2];
      int distance;
      int company;
      scanf("%d %d %d %d",&stations[0],&stations[1],&distance,&company);
      edges[stations[0]].push_back(Edge(stations[1],distance,company));
      edges[stations[1]].push_back(Edge(stations[0],distance,company));

      dist[company][stations[1]][stations[0]]
	= dist[company][stations[0]][stations[1]]
	= min(distance,dist[company][stations[1]][stations[0]]);
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

      companies[company_idx] = Company(points,slopes,total_point[company_idx]);
    }

    for(int company=1;company <= total_companies; company++){
      for(int mid=1;mid<=total_stations;mid++){
	for(int start=1;start<=total_stations;start++){
	  for(int end=1;end<=total_stations;end++){
	    dist[company][start][end] = min(dist[company][start][end],dist[company][start][mid] + dist[company][mid][end]);
	  }
	}
      }
    }

    int dp[101][101];
    memset(dp,0x3f,sizeof(dp));

    for(int i=1;i<=total_stations;i++){
      dp[i][i] = 0;
    }

    for(int start=1;start<=total_stations;start++){
      for(int end=1;end<=total_stations;end++){
	for(int company = 1; company <= total_companies; company++){
	  if(dist[company][start][end] >= INF) continue;
	  dp[end][start] = dp[start][end] = min(dp[start][end],compute_fare(company,dist[company][start][end],companies));
	}
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
