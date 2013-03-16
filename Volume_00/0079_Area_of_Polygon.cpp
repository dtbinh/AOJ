
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
typedef pair<double,double> P;

int main(){

	double x,y;
	vector<P> v;
	while(~scanf("%lf,%lf",&x,&y)){
		v.push_back(P(x,y));
	}
	
	double cx = (v[0].first + v[1].first + v[2].first) / 3.0;
	double cy = (v[0].second + v[1].second + v[2].second) / 3.0;
	
	double S=0;
	for(int i=0;i<v.size();i++){
		int idx1 = i;
		int idx2 = (i+1) % v.size();
		double a = sqrt(pow(v[idx1].first - v[idx2].first,2.0) + pow(v[idx1].second - v[idx2].second,2.0));
		double b = sqrt(pow(v[idx1].first - cx,2.0) + pow(v[idx1].second - cy,2.0));
		double c = sqrt(pow(v[idx2].first - cx,2.0) + pow(v[idx2].second - cy,2.0));

		double z = (a+b+c)/2.0;
		double tmp_s = sqrt(z*(z-a)*(z-b)*(z-c));
		S+=tmp_s;
	}

	printf("%.7f\n",S);

}

