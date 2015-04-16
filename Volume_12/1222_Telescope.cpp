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
#include <iterator>
#include <complex>
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <double,double> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  int num_of_circumference_points;
  int num_of_polygon_vertices;
  while(~scanf("%d %d",
	       &num_of_circumference_points,
	       &num_of_polygon_vertices)){
    if(num_of_circumference_points == 0
       && num_of_polygon_vertices == 0) break;

    vector<double> points;
    for(int i = 0; i < num_of_circumference_points; i++){
      double p;
      cin >> p;
      points.push_back(p);
    }
  }
}
