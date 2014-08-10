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

class Facility {
public:
  bool is_cake_store;
  int cal;
  vector<int> to;
  Facility() {}
};

int edges[201][201];
Facility nodes[101];

int main(){
  int num_of_cake_stores;
  int num_of_landmarks;
  int consume_cal_per_unit;
  int num_of_distance_datas;
  while(~scanf("%d %d %d %d",
	       &num_of_cake_stores,
	       &num_of_landmarks,
	       &consume_cal_per_unit,
	       &num_of_distance_datas)){
    for(int cake_store_idx = 0; cake_store_idx < num_of_cake_stores; cake_store_idx++){
      int cal;
      scanf("%d",&cal);
      nodes[num_of_landmarks + cake_store_idx + 1].is_cake_store = true;
      nodes[num_of_landmarks + cake_store_idx + 1].cal = cal;
    }

    for(int dist_idx = 0; dist_idx < num_of_distance_datas; dist_idx++){
      string from,to;
      int distance;
      int from_pos;
      int to_pos;
      cin >> from >> to >> distance;
      
      if(from[0] == 'H'){
	from_pos = 0;
      }

      else if(from[0] == 'D'){
	from_pos = num_of_landmarks + num_of_cake_stores;
      }

      else if(from[0] == 'L'){
	from_pos = atoi(from.substr(1,from.size()-1).c_str());
      }

      else if(from[0] == 'C'){
	from_pos = atoi(from.substr(1,from.size()-1).c_str()) + num_of_landmarks;
      }

      if(to[0] == 'H'){
	to_pos = 0;
      }

      else if(to[0] == 'D'){
	to_pos = num_of_landmarks + num_of_cake_stores;
      }

      else if(to[0] == 'L'){
	to_pos = atoi(to.substr(1,to.size()-1).c_str());
      }

      else if(to[0] == 'C'){
	to_pos = atoi(to.substr(1,to.size()-1).c_str()) + num_of_landmarks;
      }
      
      edges[from_pos][to_pos] = distance;
      edges[to_pos][from_pos] = distance;

      nodes[from_pos].to.push_back(to_pos);
      nodes[to_pos].to.push_back(from_pos);
    }
  }
}
