
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
typedef pair <int,int> P;
typedef pair <int,P > PP;

static const double eps = 1e-8;

bool isPrime[10000001];

int main(){

	fill((bool*)isPrime,(bool*)isPrime+10000001,true);
	isPrime[0] = isPrime[1] = false;
	
	for(int i=2;i*i<=10000000;i++){
		if(isPrime[i]){
			for(int j=i+i;j<=10000000;j+=i){
				isPrime[j] = false;
			}
		}
	}

	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		int res=-1;
		for(int i=n;i>=13;i--){
			if(isPrime[i] && isPrime[i-2]
			&& isPrime[i-6] && isPrime[i-8]){
				res = i;
				break;
			}
		}

		printf("%d\n",res);

	}
}

