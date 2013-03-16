
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


int main(){
	int W;
	int idx=1;
	while(~scanf("%d",&W)){
		if(W==0) break;
		int N;
		vector<P> bag;

		cin >> N;

		int** dp = new int*[N+1];
		for(int i=0;i<N+1;i++){
			dp[i] = new int[1000]();
		}



		for(int i=0;i<N;i++){
			int v,w;
			scanf("%d,%d",&v,&w);
			bag.push_back(P(v,w));
		}

		for(int i=0;i<bag.size();i++){
			for(int j=0;j<=W;j++){
				if(j < bag[i].second){
					dp[i+1][j] = dp[i][j];
				}
				else{
					dp[i+1][j] = max(dp[i][j], dp[i][j-bag[i].second] + bag[i].first);
				}
			}
		}


		int max_v=-1;
		int max_w=-1;
		for(int j=0;j<=W;j++){
			if(max_v < dp[N][j]){

				max_v = dp[N][j];
				max_w = j;
			}
		}

		printf("Case %d:\n%d\n%d\n",idx++,max_v,max_w);
	}


}


