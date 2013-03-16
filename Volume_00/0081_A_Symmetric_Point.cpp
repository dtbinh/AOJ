
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
#include <set>
#include <deque>

using namespace std;

typedef long long ll;

int main(){

	double x1,y1,x2,y2,xq,yq;
	while(~scanf("%lf,%lf,%lf,%lf,%lf,%lf",&x1,&y1,&x2,&y2,&xq,&yq)){
		double vx = x2-x1;
		double vy = y2-y1;

		double lb=-10000000.0;
		double ub=10000000.0;
		double cx,cy,vqx,vqy,md;
		for(int i=0;i < 100; i++){
			md = (lb+ub)/2.0;
			cx = x1 + vx*md;
			cy = y1 + vy*md;

			vqx = cx - xq;
			vqy = cy - yq;

			double slope = vx * vqx + vy* vqy;

			if(slope < 0){
				lb = md;
			}
			else if(slope>0){
				ub = md;
			}

			if(abs(slope) < 10e-9){
				printf("%f %f\n",2.0*cx-xq,2.0*cy-yq);
				break;
			}
		}
	}
}

