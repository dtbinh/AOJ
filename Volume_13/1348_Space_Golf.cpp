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

struct Obstacle {
  int pos;
  int height;
  Obstacle(int pos,int height) :
    pos(pos), height(height) {}
};

int main(){
  int distance;
  int num_of_obstacles;
  int bounce_limit;
  while(~scanf("%d %d %d",&distance,&num_of_obstacles,&bounce_limit)){
    vector<Obstacle> obstacles;
    for(int obstacle_i = 0; obstacle_i < num_of_obstacles; obstacle_i++){
      int pos,height;
      scanf("%d %d",&pos,&height);
      obstacles.push_back(Obstacle(pos,height));
    }
  }
}
