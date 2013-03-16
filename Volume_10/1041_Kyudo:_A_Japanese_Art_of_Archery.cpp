
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

static const double EPS = 1e-8;

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		int sum=0;
		for(int i=0;i<n/4;i++){
			int p;
			scanf("%d",&p);
			sum += p;
		}
		printf("%d\n",sum);
	}
}

