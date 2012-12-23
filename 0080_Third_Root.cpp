
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

	double q;
	while(~scanf("%lf",&q)){
		if(q==-1) break;
		double x=q/2;
		for(;;){
			x = x - (pow(x,3.0)-q)/(3*x*x);
			if(abs(pow(x,3.0)-q) < 0.00001*q) break;
		}

		printf("%.6f\n",x);
	}
}

