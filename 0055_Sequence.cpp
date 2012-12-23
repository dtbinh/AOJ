
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

	double n;
	while(~scanf("%lf",&n)){
		double seq[11];
		seq[1]=n;
		for(int i=2;i<=10;i++){
			seq[i] = i%2 ? seq[i-1] / 3.0 : seq[i-1] * 2.0;
		}

		double sum=0;
		for(int i=1;i<=10;i++){
			sum += seq[i];
		}
		printf("%.9f\n",sum);
	}
}

