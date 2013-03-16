
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

int main(){
	double x,h;
	while(~scanf("%lf",&x)){
		scanf("%lf",&h);

		if(x==h && x==0) break;

		double a = x / 2.0;
		double b = sqrt(a*a + h*h);

		printf("%0.7f\n",x*b*2.0+x*x);
	}
}

