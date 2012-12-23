
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

	double eps = 10e-7;
	double xA,yA,xB,yB,xC,yC,xD,yD;
	while(~scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
		&xA,&yA,&xB,&yB,&xC,&yC,&xD,&yD)){
			if((xB-xA)*(xD-xC)+(yB-yA)*(yD-yC) == 0){
				cout << "YES" << endl;
			}else{
				cout << "NO" << endl;
			}
	}
}

