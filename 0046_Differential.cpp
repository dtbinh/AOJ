
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;


int main(){
	double maxp=numeric_limits<double>::min();
	double minp=numeric_limits<double>::max();

	double peak;
	while(~scanf("%lf",&peak)){
		maxp = max(peak,maxp);
		minp = min(peak,minp);
	}

	printf("%lf\n",maxp-minp);
}

