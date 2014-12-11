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

const static double EPS = 1e-10;

struct Obstacle {
  double pos;
  double height;
  Obstacle(double pos,double height) :
    pos(pos), height(height) {}
};

double h(double g,double vix,double viy,double x){
  return -(g / (2.0 * vix * vix)) * x * x + (viy / vix) * x;
}

double compute_viy(double g,double interval,double vi){
  double a = 4.0;
  double b = - 4 * vi * vi;
  double c = interval * interval * g * g;
  if(b * b - 4 * a * c < 0) return -1;

  return sqrt((-b + sqrt(b * b - 4 * a * c)) / (2.0 * a));
}

int main(){
  double distance;
  int num_of_obstacles;
  int bounce_limit;
  while(~scanf("%lf %d %d",&distance,&num_of_obstacles,&bounce_limit)){
    vector<Obstacle> obstacles;
    for(int obstacle_i = 0; obstacle_i < num_of_obstacles; obstacle_i++){
      double pos,height;
      scanf("%lf %lf",&pos,&height);
      obstacles.push_back(Obstacle(pos,height));
    }

    double g = 1.0;
    double res = numeric_limits<double>::max();

    for(int div = 1; div <= bounce_limit + 1; div++){
      double rhs = 10000.0;
      double lhs = 0;
      double interval = distance / div;

      for(int round = 0; round < 50; round++){
	double vi = lhs + (rhs - lhs) / 2.0;
	double viy = compute_viy(g,interval,vi);
	if(viy < 0) {
	  lhs = vi;
	  continue;
	}

	double vix = sqrt(vi * vi - viy * viy);

	bool isok = true;
	for(int obstacle_i = 0; obstacle_i < num_of_obstacles; obstacle_i++){
	  int offset = (int)(obstacles[obstacle_i].pos / (interval + EPS) );
	  if(h(g,vix,viy,obstacles[obstacle_i].pos - ((double)offset * interval)) < obstacles[obstacle_i].height){
	    isok = false;
	    break;
	  }
	}
	if(isok){
	  rhs = vi;
	  res = min(res,vi);
	}
	else{
	  lhs = vi;
	}
      }
    }
    printf("%.5lf\n",res);
  }
}
