
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
#include <bitset>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 10e-8;

int main(){
	ll n;
	while(~scanf("%lld",&n)){
		if(n==0) break;
		int res=0;
		while(n!=1){
			if(n%2) n=n*3+1;
			else n/=2;
			res++;
		}

		printf("%d\n",res);
	}
}

