
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

bool dp[1000001];
int main(){
	int n,a,b;
	while(~scanf("%d %d %d",&n,&a,&b)){
		if(n==0 && a==0 && b==0) break;

		memset(dp,0,sizeof(dp));

		dp[0] = true;

		for(int i=0;i<=n;i++){
			if(i+a <= 1000000) dp[i+a] |= dp[i];
			if(i+b <= 1000000) dp[i+b] |= dp[i];
		}

		int c=0;
		for(int i=0;i<=n;i++){
			if(!dp[i]){
				c++;
			}
		}

		printf("%d\n",c);
	}
}

