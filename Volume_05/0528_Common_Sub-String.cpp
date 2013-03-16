
#define _USE_MATH_DEFINES
#define INF 100000000
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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
typedef pair <int,int> P;

static const double EPS = 1e-8;

short dp[4001][4001];

int main(){
	string str1;
	while(cin>> str1){
		memset(dp,0,sizeof(dp));

		string str2;
		cin >> str2;

		short res = 0;
		for(int i=0;i<str1.size();i++){
			for(int j=0;j<str2.size();j++){
				if(str1[i] == str2[j]){
					dp[i+1][j+1] = dp[i][j]+1;
					res = max(res,dp[i+1][j+1]);
				}
				else{
					dp[i+1][j+1] = 0;
				}
			}
		}

		printf("%d\n",res);
	}
}

