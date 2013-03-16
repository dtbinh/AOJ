
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
typedef pair<int,int> P;

static const double eps = 10e-6;

int dp[101][101];

int main(){
	int n;
	scanf("%d",&n);

	vector<P> cards;
	memset(dp,0x2,sizeof(dp));
	for(int i=0;i<n;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		cards.push_back(P(a,b));
	}

	for(int i=0;i<=n;i++) dp[i][i]=0;

	for(int len=1;len<n;len++){
		for(int i=0;i<n-len;i++){
			for(int j=i;j<i+len;j++){
				int cost = cards[i].first * cards[j].second * cards[j+1].first * cards[i+len].second;
				dp[i][i+len] = min(dp[i][i+len],dp[i][j] + dp[j+1][i+len] + cost);
			}
		}
	}

	cout << dp[0][n-1] << endl;
}

