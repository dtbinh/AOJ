
#define _USE_MATH_DEFINES
#define MAX_N 1000000
#include <iostream>
#include <sstream>
#include <cmath>
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 1e-8;

const static double r = 6378.1;

int main(){
	double f1,g1,f2,g2;
	//ido,kedo
	while(~scanf("%lf %lf %lf %lf",&f1,&g1,&f2,&g2)){
		if(f1==g1 && g1==f2 && f2==g2 && g2 == -1) break;

		f1 = (90.0-f1) * M_PI / 180.0;
		g1 = g1 * M_PI / 180.0;

		f2 = (90.0-f2) * M_PI / 180.0;
		g2 = g2 * M_PI / 180.0;

		double x1 = r * sin(f1) * cos(g1);
		double y1 = r * sin(f1) * sin(g1);
		double z1 = r*cos(f1);

		double x2 = r * sin(f2) * cos(g2);
		double y2 = r * sin(f2) * sin(g2);
		double z2 = r*cos(f2);

		double dist = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);

		int res = r*acos(1-dist/(2*r*r))+0.50+eps;
		printf("%d\n",res);
	}
}

