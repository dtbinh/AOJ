
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

static const double eps = 10e-8;

bool primeTable[1000001];
int primeBIT[1000001];

int sumBIT(int i,int* bit){
	int s = 0;
	while(i > 0){
		s += bit[i];
		i -= i & -i;
	}
	return s;
}

void addBIT(int i, int x,int* bit,int n){
	while(i <= n){
		bit[i] += x;
		i += i & -i;
	}	
}

int main(){
	fill((bool*)primeTable,(bool*)primeTable+1000001,true);
	fill((int*)primeBIT,(int*)primeBIT+1000001,0);

	primeTable[0] = false;
	primeTable[1] = false;

	for(int i=1;i*i<=1000000;i++){
		if(primeTable[i]){
			for(int j=i+i;j<=1000000;j+=i){
				primeTable[j] = false;
			}
		}
	}

	for(int i=1;i<=1000000;i++){
		addBIT(i,primeTable[i],primeBIT,1000000);
	}


	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;

		int sum=0;
		for(int i=0;i<n;i++){
			int p,m;
			scanf("%d %d",&p,&m);

			int tmp=0;
			tmp = sumBIT(p+m >=1000000 ? 1000000 : p+m,primeBIT) 
				- sumBIT(p-m-1 >= 0 ? p-m-1 : 0,primeBIT);

			tmp > 0 ? sum+=tmp-1 : sum--;
		}

		printf("%d\n",sum >= 0 ? sum : 0);
	}
}

