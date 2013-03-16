
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

	int* dp = new int[60001];

	fill((int*)dp,(int*)dp+60001,1);

	dp[0]=0;
	dp[1]=0;

	for(int i=2;i<=60000;i++){
		if(dp[i]){
			for(int j=i+i;j<=60000;j+=i){
				dp[j]=0;
			}
		}
	}

	int num;
	while(~scanf("%d",&num)){
		for(int i=num-1;i>=0;i--){
			if(dp[i]){
				cout << i << " ";
				break;
			}
		}

		for(int i=num+1;i<=60000;i++){
			if(dp[i]){
				cout << i << endl;
				break;
			}
		}
	}
}


