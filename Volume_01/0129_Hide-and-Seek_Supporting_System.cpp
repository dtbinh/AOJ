
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
typedef pair<int,int> P;
typedef pair<P,int> PP;

bool isInCircle(double px,double py,double cx,double cy, double r){
	double a = pow(px - cx,2.0) + pow(py - cy,2.0);
	return a < r*r ? true : false;
}

bool isIntersectCircleAndLine(double px1,double py1,double px2, double py2,double cx,double cy, double r){
	if(isInCircle(px1,py1,cx,cy,r) && isInCircle(px2,py2,cx,cy,r)) return false;

	//vector1: from the center of the circle to the staring point
	double vx1 = (cx - px1);
	double vy1 = (cy - py1);

	//vector2: from the starting point to the ending point
	double vx2 = (px2 - px1);
	double vy2 = (py2 - py1);


	double n1=vx1*vx2 + vy1*vy2;
	double n2=vx2*vx2 + vy2*vy2;
	double n3=vx1*vx1 + vy1*vy1;
	

	if(n1 < 0){
		//distance between the starting point and the center of the circle
		return (pow(px1 - cx,2.0) + pow(py1 - cy,2.0) <= r*r) ? true : false;
	}

	else if(n1 > n2){
		//distance between the ending point and the center of the circle
		return (pow(px2 - cx,2.0) + pow(py2 - cy,2.0) <= r*r) ? true : false;
	}
	else{
		if(n2<=0) return (n3*n2 - n1*n1 >= r*r*n2) ? true : false; 
		else return (n3*n2 - n1*n1 <= r*r*n2) ? true : false; 
	}
}

int main(){
	
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		vector<PP> wall;
		for(int i=0;i<n;i++){
			int x,y,r;
			scanf("%d %d %d",&x,&y,&r);
			wall.push_back(PP(P(x,y),r));
		}

		int m;
		scanf("%d",&m);
		for(int i=0;i<m;i++){
			double tx,ty,sx,sy;
			scanf("%lf %lf %lf %lf",&tx,&ty,&sx,&sy);
			bool isSafe = false;
			for(int i=0;i<wall.size();i++){
				if(isIntersectCircleAndLine(tx,ty,sx,sy,wall[i].first.first,
					wall[i].first.second,wall[i].second)){
						isSafe = true;
				}
			}

			printf("%s\n",isSafe ? "Safe" : "Danger");
		}
	}
}


