
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
	int K,c;
	while(~scanf("%d",&K)){
		if(K==0) break;
		int sum=0;
		for(int i=0;i<K*(K-1)/2;i++){
			int c;
			scanf("%d",&c);
			sum += c;
		}

		printf("%d\n",sum/(K-1));
	}
}

