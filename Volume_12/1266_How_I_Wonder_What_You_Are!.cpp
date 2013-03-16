
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

int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

static const double EPS = 1e-8;

class Stars{
public:
	double x;
	double y;
	double z;
	Stars(double _x,double _y,double _z) : x(_x),y(_y),z(_z) {}
};

class Teles : public Stars{
public:
	double phi;
	Teles(double _x,double _y,double _z,double _phi) : Stars(_x,_y,_z),phi(_phi) {}
};

int main(){
	int n,m;
	while(~scanf("%d",&n)){
		if(n==0) break;
		vector<Stars> stars;
		vector<Teles> teles;
		for(int i=0;i<n;i++){
			//stars
			double sx,sy,sz;
			scanf("%lf %lf %lf",&sx,&sy,&sz);
			stars.push_back(Stars(sx,sy,sz));

		}
		scanf("%d",&m);
		for(int i=0;i<m;i++){
			//telescopes
			double tx,ty,tz,phi;
			scanf("%lf %lf %lf %lf",&tx,&ty,&tz,&phi);
			teles.push_back(Teles(tx,ty,tz,phi));
		}

		int res=0;
		for(int i=0;i<stars.size();i++){

			bool isok = false;			
			for(int j=0;j<teles.size();j++){
				double inner = 
					stars[i].x * teles[j].x
					+ stars[i].y * teles[j].y
					+ stars[i].z * teles[j].z;

				double scaleS = 
					sqrt(stars[i].x * stars[i].x
					+ stars[i].y * stars[i].y
					+ stars[i].z * stars[i].z);

				double scaleT = 
					sqrt(teles[j].x * teles[j].x
					+ teles[j].y * teles[j].y
					+ teles[j].z * teles[j].z);

				double theta = acos(inner/(scaleS*scaleT));

				if(theta < teles[j].phi){
					isok = true;
					break;
				}
			}

			if(isok) res++;
		}

		printf("%d\n",res);
	}
}

