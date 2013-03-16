
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
	int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		double xa,ya,ra,xb,yb,rb;
		scanf("%lf %lf %lf %lf %lf %lf",&xa,&ya,&ra,&xb,&yb,&rb);
		double dist = sqrt(pow((xa-xb),2.0) + pow((ya-yb),2.0));

		int res=1;
		if(dist > ra + rb){
			res=0;
		}
		else if(dist <= ra+ rb){
			if(ra > dist +rb){
				res=2; 
			}
			else if(rb > dist + ra){
				res=-2;
			}
		}

		cout << res << endl;
	}
}

