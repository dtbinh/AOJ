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

const static double EPS = 1e-12;

struct Obstacle {
  double pos;
  double height;
  Obstacle(double pos,double height) :
    pos(pos), height(height) {}
};

double h(double g,double vix,double viy,double x){
  return -(g / (2.0 * vix * vix)) * x * x + (viy / vix) * x;
}

double compute_interval(double g,double vix,double viy){
  double a = - (g / (2.0 * vix * vix));
  double b = viy / vix;
  double c = 0.0;
  return (-b - sqrt(b * b - 4 * a * c)) / (2.0 * a);
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
    double max_viy = 100000000.0;
    double min_viy = EPS;

    for(int round = 0; round < 50; round++){
      double viy = min_viy + (max_viy - min_viy) / 2.0;
      bool has_path = false;
      for(double div = 1.0; div <= 15.0; div+=1.0){
	double vix = (distance/div * g) / (2.0 * viy);
	double interval = compute_interval(g,vix,viy);
	if(interval < EPS) continue;
	if((int)(distance / (interval + EPS)) > bounce_limit) continue;

	bool isok = true;
	for(int obstacle_i = 0; obstacle_i < num_of_obstacles; obstacle_i++){
	  // cout << h(g,vx,vy,obstacles[obstacle_i].pos) << endl;
	  int offset = (int)(obstacles[obstacle_i].pos / interval + EPS);
	  if(h(g,vix,viy,obstacles[obstacle_i].pos - ((double)offset * interval)) < obstacles[obstacle_i].height){
	    isok = false;
	    break;
	  }
	}
	if(isok){
	  has_path = true;
	  if(res > sqrt(vix * vix + viy * viy)){
	    res = sqrt(vix * vix + viy * viy);
	    max_viy = viy;
	  }
	}
      }
      if(!has_path) {
	min_viy = viy;
      }
    }
    printf("%lf\n",res);
  }
}
