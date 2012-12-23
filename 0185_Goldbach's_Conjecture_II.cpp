
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

int main(){

	bool table[1000001];
	fill((bool*)table,(bool*)table+1000001,true);

	table[0]=false;
	table[1]=false;
	for(int i=2;i*i<=1000000;i++){
		if(table[i]){
			for(int j=i+i;j<=1000000;j+=i){
				table[j]=false;
			}
		}
	}

	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;

		int res=0;
		for(int i=n,j=0;j<=n/2;j++,i--){
			if(table[i] && table[j]) res++;
		}

		printf("%d\n",res);
	}
}

