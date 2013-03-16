
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
	
	int arvH,arvM,arvS,dptH,dptM,dptS;
	while(~scanf("%d %d %d %d %d %d",&arvH,&arvM,&arvS,&dptH,&dptM,&dptS)){
		int diff = ((dptH*60*60+dptM*60+dptS)-(arvH*60*60+arvM*60+arvS));
		int H = diff/60/60;
		diff %= 3600;
		int M = diff/60;
		diff %= 60;
		int S = diff;
		printf("%d %d %d\n",H,M,S);
	}
}

