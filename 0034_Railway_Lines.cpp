
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
	int l[10];
	int v1,v2;
	while(~scanf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		l,l+1,l+2,l+3,l+4,l+5,l+6,l+7,l+8,l+9,&v1,&v2)){
			double lb=0.0;
			double ub=1000000000;

			int sum = 0;
			for(int i=0;i<10;i++) sum+=l[i];
			for(int i=0;i<100;i++){
				double md = (ub+lb)/2.0;
				if((md/3600.0)*v1 +(md/3600.0)*v2 > sum) ub = md;
				if((md/3600.0)*v1 +(md/3600.0)*v2 < sum) lb = md;
			}

			double dist_t = v1*lb/3600.0;

			double dist_l = 0;
			for(int i=0;i<10;i++){
				dist_l += (double)l[i];
				if(dist_l >= dist_t){
					cout << i+1 << endl;
					break;
				}
			}
			//printf("%f\n",ub);
			//printf("%f\n",lb);
	}
}

