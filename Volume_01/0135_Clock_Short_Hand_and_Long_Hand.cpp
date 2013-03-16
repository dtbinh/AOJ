
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

string getAlert(double h,double m){
	double angleM = m * 6.0;
	double angleH = h * 30.0 + (m*6.0)/12.0;

	double dist = min(abs(angleH-angleM),360-abs(angleH-angleM));
	if(90 <= dist && dist <= 180) return "safe";
	else if(0 <= dist && dist < 30) return "alert";
	else return "warning";
}

int main(){
	int n;
	double h,m;
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){
			scanf("%lf:%lf",&h,&m);
			cout << getAlert(h,m) << endl;
		}
	}
}

