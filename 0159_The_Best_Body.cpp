
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

static const double eps = 10e-8;

int main(){

	int i,n;
	double h,w;
	
	while(~scanf("%d",&n)){
		if(n==0) break;
		double diff = 1000000;
		int res=10000000;

		for(int j=0;j<n;j++){
			scanf("%d %lf %lf",&i,&h,&w);
			if(diff > abs(22.0-(w / ((h/100.0)*(h/100.0))))){
				diff = abs(22.0-(w / ((h/100.0)*(h/100.0))));
				res = i;
			}
			else if(diff == abs(22.0-(w / ((h/100.0)*(h/100.0))))){
				res = min(res,i);
			}
		}
		printf("%d\n",res);
	}
}

