
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

typedef long long ll;
using namespace std;

typedef pair<int,int> P;

void seek_lcs(int a,int b,int dp[10+1][10+1],int* num,int* base,vector<int>& idx){
	if(a==0 || b==0){
		return;
	}

	if(num[a] == base[b]){
		seek_lcs(a-1,b-1,dp,num,base,idx);
		idx.push_back(num[a]);
	}
	else{
		if(dp[a-1][b] >= dp[a][b-1]){
			seek_lcs(a-1,b,dp,num,base,idx);
		}
		else{
			seek_lcs(a,b-1,dp,num,base,idx);
		}
	}

}

int main()
{
	int T;
	cin >> T;
	for(int t=0;t<T;t++){

		int num[10+1];
		int base[10+1];
		int dp[10+1][10+1];

		memset(dp,0,sizeof(dp));

		for(int i=1;i<=10;i++){
			scanf("%d",num+i);
			base[i]=i;
		}
		num[0]=0;
		base[0]=0;

		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				if(num[i+1]==base[j+1]){
					dp[i+1][j+1] = max(dp[i+1][j],max(dp[i][j+1],dp[i][j]+1));
				}
				else{
					dp[i+1][j+1] = max(dp[i+1][j],max(dp[i][j+1],dp[i][j]));
				}
			}
		}

		vector<int> idx;
		stack<int> stk;
		seek_lcs(10,10,dp,num,base,idx);

		for(int i=1;i<=10;i++){
			if(find(idx.begin(),idx.end(),num[i]) != idx.end()){
				continue;
			}

			if(stk.empty() || stk.top() < num[i]) stk.push(num[i]);
		}

		printf("%s\n",idx.size() + stk.size() == 10 ? "YES" : "NO");
	}
}

