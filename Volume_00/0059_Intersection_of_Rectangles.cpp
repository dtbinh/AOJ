
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
typedef long double ld;
typedef pair<int,int> P;

int main(){

	double xa1,ya1,xa2,ya2,xb1,yb1,xb2,yb2;
	while(~scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
		&xa1,&ya1,&xa2,&ya2,&xb1,&yb1,&xb2,&yb2)){
			if(xb2 < xa1 || xa2 < xb1 || yb1 > ya2 || yb2 < ya1){
				cout << "NO" << endl;
			}
			else{
				cout << "YES" << endl;
			}
	}
}

