
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
typedef pair<int,string> P;

static const double eps = 1e-8;

bool prime[1000001];
int dp[1000001];

int main(){

	fill((bool*)prime,(bool*)prime+1000000,true);

	prime[0] = false;
	prime[1] = false;
	for(int i = 2;i*i<=1000000;i++){
		if(prime[i]){
			for(int j=i+i;j<=1000000;j+=i){
				prime[j] = false;
			}
		}
	}

	int n,x;
	while(~scanf("%d %d",&n,&x)){
		if(n==x && x==0) break;

		memset(dp,0,sizeof(dp));
		vector<int> foods;
		for(int i=0;i<n;i++){
			int cost;
			scanf("%d",&cost);
			foods.push_back(cost);
			dp[cost] = 1;
		}

		sort(foods.begin(),foods.end());

		for(int i=0;i<=x;i++){
			for(int j=0;j<foods.size();j++){
				if(i - foods[j] >= 0 && dp[i - foods[j]]){
					dp[i] = 1;
					break;
				}
			}
		}

		int res = -1;
		for(int i=x;i>=1;i--){
			if(!prime[i]) continue;
			

			if(dp[i]){
				res = i;
				goto found;
			}
		}
found:;
		if(res==-1) printf("NA\n");
		else printf("%d\n",res);
	}
}

