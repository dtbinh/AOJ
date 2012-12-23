
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
typedef pair<int,int> P;


int main(){
	int v,n;
	int sum=0;
	double avr=0;
	double idx=0;
	while(~scanf("%d,%d",&v,&n)){
		sum += v*n;
		avr += n;
		idx++;
	}

	cout << sum << endl;
	double res = avr/idx + 0.5 + 10e-9;
	printf("%.0f\n",res);
}


