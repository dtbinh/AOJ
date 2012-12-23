
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

static const double eps = 10e-6;

int main(){
	int n;
	int* primeTable = new int[100001];
	fill((int*)primeTable,(int*)primeTable+100001,1);

	primeTable[0] = 0;
	primeTable[1] = 0;

	for(int i=2;i*i<=100000;i++){
		if(primeTable[i] != 1) continue;
		for(int j=i+i;j<=100000;j+=i){
			primeTable[j] = 0;
		}
	}

	while(~scanf("%d",&n)){
		if(n==0) break;
		for(int i=n;i-2>=0;i--){
			if(primeTable[i] && primeTable[i-2]){
				printf("%d %d\n",i-2,i);
				break;
			}
		}
	}
}

