
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
#include <bitset>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 10e-6;

int amount[101];
int num[101];
int dp[101][1001];

int main(){
	string str;
	vector<string> data;
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		memset(amount,0,sizeof(amount));
		memset(num,0,sizeof(num));
		memset(dp,0,sizeof(dp));

		for(int i=0;i<n;i++){
			int a,b;
			scanf("%d %d",&a,&b);
			amount[i] = b;
			num[i] = a;
		}

		dp[0][0] = 1;


		for(int i=0;i<n;i++){		
				for(int j=0;j<=amount[i];j++){
					for(int k=0;k<=1000;k++){
					if(k - num[i]*j >= 0){
						dp[i+1][k] += dp[i][k-num[i]*j];
					}
				}
			}
		}

		int g;
		scanf("%d",&g);
		for(int i=0;i<g;i++){
			int c;
			scanf("%d",&c);
			printf("%d\n",dp[n][c]);
		}
	}
}

