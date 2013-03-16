
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double eps = 1e-8;

double dp[101][101];
double table[100][100];

int main(){

	int n,m;
	while(~scanf("%d %d",&n,&m)){
		if(n==m && m==0) break;
		for(int y=0;y<n;y++){
			for(int x=0;x<n;x++){
				scanf("%lf",&table[y][x]);
			}
		}

		fill((double*)dp,(double*)dp+101*101,0.0);
		for(int i=0;i<n;i++) dp[0][i] = 1.0;

		for(int k=0;k<m-1;k++){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					dp[k+1][i] = max(dp[k][j]*table[j][i],dp[k+1][i]);
				}
			}
		}

		double res = -1.0;
		for(int i=0;i<n;i++) res = max(res,dp[m-1][i]);

		printf("%.2lf\n",res);
	}
}

