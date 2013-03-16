
#define _USE_MATH_DEFINES
#define INF 100000000
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

using namespace std;

typedef long long ll;
typedef pair <double,double> P;
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

int main(){

	double x,y;
	int n;
	int seq=1;
	
	while(~scanf("%d",&n)){
		if(n==0) break;
		vector<P> v;
		for(int i=0;i<n;i++){
			scanf("%lf %lf",&x,&y);
			v.push_back(P(x,y));
		}

		double S=0;
		for(int i=0;i<v.size();i++){
			int idx1 = i;
			int idx2 = (i+1) % v.size();
			S += 0.5*(v[idx2].first - v[idx1].first)*(v[idx1].second + v[idx2].second) + EPS;
		}

		printf("%d %.1lf\n",seq++,S);
	}
}

