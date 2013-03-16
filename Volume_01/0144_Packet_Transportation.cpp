
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

using namespace std;

typedef long long ll;
typedef pair<double,int> P;

static const double eps = 10e-6;

int dp[101][101];

int main(){
	int n;

	memset(dp,0x2,sizeof(dp));
	scanf("%d",&n);	
	for(int i=0;i<n;i++){
		int r,k,t;
		scanf("%d %d",&r,&k);
		for(int j=0;j<k;j++){
			scanf("%d",&t);
			dp[r][t] = 1;
		}
	}

	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				dp[j][k] = min(dp[j][i]+dp[i][k],dp[j][k]);
			}
		}
	}


	int p;
	scanf("%d",&p);
	for(int i=0;i<p;i++){
		int s,d,v;
		scanf("%d %d %d",&s,&d,&v);

		char buf[128];
		sprintf(buf,"%d",dp[s][d]+1);
		printf("%s\n", dp[s][d] >= v ? "NA" : buf);

	}
}

