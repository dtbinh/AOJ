
#define _USE_MATH_DEFINES
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

typedef long long ll;
using namespace std;

struct Point{
	double x;
	double y;
};

bool is_inter(struct Point p1,struct Point p2,
	struct Point p3, struct Point p4)
{
	if(((p1.x-p2.x) * (p3.y - p1.y) + (p1.y - p2.y) * (p1.x - p3.x))
		* ((p1.x - p2.x) * (p4.y - p1.y) + (p1.y - p2.y) * (p1.x - p4.x)) < 0){
			return true;
	}

	return false;
}

int main()
{
	double xa, ya, xb, yb, xc, yc, xd, yd;
	Point a,b,c,d;
	while(~scanf("%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
		&xa, &ya, &xb, &yb, &xc, &yc, &xd, &yd)){
			a.x = xa;
			a.y = ya;
			b.x = xb;
			b.y = yb;
			c.x = xc;
			c.y = yc;
			d.x = xd;
			d.y = yd;

			printf("%s\n",is_inter(a,c,b,d) && is_inter(b,d,a,c) ? "YES" : "NO");
	}
}

