
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

int main(){
	double d,w,h;
	while(~scanf("%lf %lf %lf",&d,&w,&h)){
		if(d==w && w==h && h==0) break;
		int n;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			double r;
			scanf("%lf",&r);
			if((d/2.0)*(d/2.0) + (h/2.0)*(h/2.0) < r*r
				|| (d/2.0)*(d/2.0) + (w/2.0)*(w/2.0) < r*r
				|| (w/2.0)*(w/2.0) + (h/2.0)*(h/2.0) < r*r)
			{
				cout << "OK" << endl;
			}
			else{
				cout << "NA" << endl;
			}
		}
	}
}

