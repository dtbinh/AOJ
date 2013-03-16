
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

ll sum(int i,ll* bit){
	int s = 0;
	while(i > 0){
		s += bit[i];
		i -= i & -i;
	}
	return s;
}

void add(int i, ll x,ll* bit,ll n){
	while(i <= n){
		bit[i] += x;
		i += i & -i;
	}	
}

int main(){
	int* dp = new int[1000000];
	fill((int*)dp,(int*)dp + 1000000,1);
	dp[0]=0;
	dp[1]=0;
	for(int i=2;i<1000000;i++){
		if(dp[i] != 0){
			for(int j=i+i;j<1000000;j+=i){
				dp[j] = 0;
			}
		}
	}

	int idx=1;
	ll* bit = new ll[1000000];
	fill((ll*)bit,(ll*)bit + 1000000,0);

	for(int i=2;i<1000000;i++){
		if(dp[i] != 0){
			add(idx++,i,bit,1000000);
		}
	}

	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		cout << sum(n,bit) << endl;
	}
}


