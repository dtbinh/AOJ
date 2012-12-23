
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

int buy_A(int n){
	return 5*380*0.80*(int)(n/5) + 380 * (n%5);
}

int buy_B(int n){
	return 4*550*0.85*(int)(n/4) + 550 * (n%4);
}

int buy_C(int n){
	return 3*850*0.88*(int)(n/3) + 850 * (n%3);
}

int main(){
	int W;
	while(~scanf("%d",&W)){
		if(W==0) break;
		W/=100;
		int res=numeric_limits<int>::max();

		for(int a=0; a<=25;a++){
			for(int b=0; b<=17;b++){
				for(int c=0; c<=10;c++){
					if(a*2+b*3+c*5 - W == 0){
						res = min(res,buy_A(a)+buy_B(b)+buy_C(c));
					}

				}
			}

		}

		cout << res << endl;

	}
}

