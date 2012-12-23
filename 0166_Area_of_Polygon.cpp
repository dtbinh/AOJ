
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
#include <bitset>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 1e-8;

int main(){

	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;

		double areaA=0,areaB=0;
		int remain=360;
		for(int i=0;i<n-1;i++){
			double rad;
			int angle;
			scanf("%d",&angle);
			remain-=angle;
			rad = (double)angle / 180.0 * M_PI;
			areaA += 0.5*sin(rad);
		}

		areaA += 0.5*sin((double)remain / 180.0 * M_PI);

		remain=360;
		scanf("%d",&n);
		for(int i=0;i<n-1;i++){
			double rad;
			int angle;
			scanf("%d",&angle);
			remain-=angle;
			rad = (double)angle / 180.0 * M_PI;
			areaB += 0.5*sin(rad);
		}

		areaB += 0.5*sin((double)remain / 180.0 * M_PI);

		printf("%d\n",abs(areaA - areaB) < eps ? 0 :
			areaA > areaB ? 1 : 2);
	}
}

