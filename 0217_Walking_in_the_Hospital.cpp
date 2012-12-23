
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
	int n;	
	while(~scanf("%d",&n)){	
		if(n==0) break;
		priority_queue<P> que;
		for(int i=0;i<n;i++){
			int p,d1,d2;
			scanf("%d %d %d",&p,&d1,&d2);
			que.push(P(d1+d2,p));
		}

		printf("%d %d\n",que.top().second,que.top().first);
	}
}

