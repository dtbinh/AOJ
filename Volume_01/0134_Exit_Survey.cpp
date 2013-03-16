
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
typedef pair<char,int> P;

static const double eps = 10e-9;

int main(){

	int n;
	while(~scanf("%d",&n)){
		double sum=0.0;
		for(int i=0;i<n;i++){
			double val;
			scanf("%lf",&val);
			sum += val/n;
		}

		printf("%.0lf\n",sum);
	}
}

