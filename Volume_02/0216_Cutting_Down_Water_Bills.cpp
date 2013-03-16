
#define _USE_MATH_DEFINES
#define INF 10000000
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
#include <list>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

static const double eps = 1e-8;

int main(){
	int w;
	while(~scanf("%d",&w)){
		if(w==-1) break;
		printf("%d\n",4280 - (1150 + (w > 30 ? 125 * 10 + 140 * 10 + 160 * (w-30)
			: w > 20 ? 125 * 10 + 140 * (w-20)
			: w > 10 ? 125 * (w-10)
			: 0)));
	}
}


