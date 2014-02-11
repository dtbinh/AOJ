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

int compute_fare(int z,int points[51],int total_points,int slopes[51]){
  if(z == 0) return 0;
  int idx = lower_bound(points,points+(total_points+1),z) - points;
  return compute_fare(z-1,points,total_points,slopes) + slopes[idx];
}

int main(){
  int total_stations;
  int total_lines;
  int total_companies;
  int start_idx;
  int goal_idx;
  while(~scanf("%d %d %d %d %d",
	       &total_stations,
	       &total_lines,
	       &total_companies,
	       &start_idx,
	       &goal_idx)){
    int total_point[21];

    vector<Edge> edges[101];
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

      for(int z=1;z<=9;z++){
	cout << compute_fare(z,points,total_point[company_idx],slopes) << endl;
      }
    }
    
  }
}
