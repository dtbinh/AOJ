
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
const int ty[] = {-1,0,1,0};

int students[100][100];

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;

		map<ll,int> stars;
		for(int i=0;i<n;i++){
			ll num;
			scanf("%lld",&num);
			stars[num]++;
		}

		int maxv=numeric_limits<int>::min();
		ll res = 0;
		for(map<ll,int>::iterator it = stars.begin(); it != stars.end(); it++){
			if(maxv < it->second){
				maxv = it->second;
				res = it->first;
			}
		}

		if(maxv > n/2) printf("%lld\n",res);
		else printf("NO COLOR\n");
	}
}

