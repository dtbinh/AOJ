
#define _USE_MATH_DEFINES
#define INF 100000000
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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
#include <list>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {1,0,-1,0};

int main(){
	ll z;
	while(~scanf("%lld",&z)){
		if(z==0) break;

		ll maxv = -1;
		for(ll x=1;x*x*x<=z*z*z;x++){
			for(ll y=1;x*x*x+y*y*y<=z*z*z;y++){
				maxv = max(maxv,x*x*x+y*y*y);
			}
		}
		printf("%lld\n",z*z*z-maxv);
	}
}

