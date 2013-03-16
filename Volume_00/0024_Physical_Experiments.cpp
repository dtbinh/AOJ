
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>

typedef long long ll;
using namespace std;

int main()
{
	double cv;
	while(~scanf("%lf",&cv)){
		//v=9.8t
		//y=4.9t^2

		int lb=1;
		int ub=100000000;
		
		for(int i=0;i<100;i++){
			int md = (lb+ub)/2;
			if(sqrt((5*md-5)/4.9) * 9.8 > cv) ub = md;
			else if(sqrt((5*md-5)/4.9) * 9.8 < cv) lb = md;			
		}

		cout << ub << endl;

	}
}

