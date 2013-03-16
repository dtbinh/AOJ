
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
	double eps = 10e-9;
	
	int num;

	while(~scanf("%d",&num)){
		if(num==0) break;

		int sum=0;
		while(num > 0){
			sum += num / 5;
			num = num / 5;
		}

		cout << sum << endl;
	}
}


