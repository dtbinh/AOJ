
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
typedef pair<double,int> P;

static const double eps = 10e-6;

class intersect_triangle{
private:
	double dst[3];
	double orig[3], dir[3];
	double vert0[3],vert1[3],vert2[3];

	double dot(double v1[3],double v2[3]){
		return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];
	}
	void cross(double dest[3],double v1[3],double v2[3]){
		dest[0] = v1[1]*v2[2]-v1[2]*v2[1];
		dest[1] = v1[2]*v2[0]-v1[0]*v2[2];
		dest[2] = v1[0]*v2[1]-v1[1]*v2[0];
	}

	void sub(double dest[3],double v1[3], double v2[3]){
		dest[0] = v1[0]-v2[0];
		dest[1] = v1[1]-v2[1];
		dest[2] = v1[2]-v2[2];
	}
public:
	intersect_triangle(double xp1,double yp1,double xp2,double yp2,double xp3,double yp3,
		double xk,double yk){
		vert0[0] = xp1;
		vert0[1] = yp1;
		vert0[2] = 0;

		vert1[0] = xp2;
		vert1[1] = yp2;
		vert1[2] = 0;

		vert2[0] = xp3;
		vert2[1] = yp3;
		vert2[2] = 0;

		orig[0] = xk;
		orig[1] = yk;
		orig[2] = -1;

		dst[0] = xk;
		dst[1] = yk;
		dst[2] = 1;

		double len = sqrt(pow(dst[0]-orig[0],2.0)+pow(dst[1]-orig[1],2.0)+pow(dst[2]-orig[2],2.0));
		dir[0] = (dst[0]-orig[0])/len;
		dir[1] = (dst[1]-orig[1])/len;
		dir[2] = (dst[2]-orig[2])/len;
	}

	bool is_intersect(){
		double edge1[3],edge2[3],tvec[3],pvec[3],qvec[3];
		double det,inv_det,t=0,v=0,u=0;

		sub(edge1,vert1,vert0);
		sub(edge2,vert2,vert0);

		cross(pvec,dir,edge2);

		det=dot(edge1,pvec);

		if(det > -eps && det < eps) return false;

		inv_det = 1.0/det;

		sub(tvec,orig,vert0);

		u=dot(tvec,pvec)*inv_det;
		if(u < 0.0 || u > 1.0) return false;

		cross(qvec,tvec,edge1);

		v=dot(dir,qvec) * inv_det;
		if(v < 0.0 || u+v > 1.0) return false;

		t = dot(edge2,qvec) * inv_det;

		return true;

	}
};

int main(){
	int n;
	scanf("%d",&n);

	for(int i=0;i<n;i++){
		double xp1,yp1,xp2,yp2,xp3,yp3,xk,yk,xs,ys;
		scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
			&xp1,&yp1,&xp2,&yp2,&xp3,&yp3,&xk,&yk,&xs,&ys);
		intersect_triangle inter_t1(xp1,yp1,xp2,yp2,xp3,yp3,xk,yk);
		intersect_triangle inter_t2(xp1,yp1,xp2,yp2,xp3,yp3,xs,ys);
		printf("%s\n",(inter_t1.is_intersect() && inter_t2.is_intersect()) 
			|| (!inter_t1.is_intersect() && !inter_t2.is_intersect())
			? "NG" : "OK");
	}
}

