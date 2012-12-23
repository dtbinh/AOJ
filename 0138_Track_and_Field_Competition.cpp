
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

static const double eps = 10e-9;

int main(){
	int n;
	vector<P> remain;
	for(int i=0;i<3;i++){
		vector<P> men;
		for(int j=0;j<8;j++){
			int num;
			double time;
			
			scanf("%d %lf",&num,&time);
			men.push_back(P(time,num));
		}

		sort(men.begin(),men.end());
		printf("%d %.2lf\n",men[0].second,men[0].first);
		printf("%d %.2lf\n",men[1].second,men[1].first);
		for(int j=2;j<men.size();j++) remain.push_back(men[j]);
	}

	sort(remain.begin(),remain.end());
	printf("%d %.2lf\n",remain[0].second,remain[0].first);
	printf("%d %.2lf\n",remain[1].second,remain[1].first);

}

