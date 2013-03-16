
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
typedef pair <P,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

int main(){
	int n,m;
	while(~scanf("%d %d",&n,&m)){
		if(n==m && m==0) break;
		int* bag = new int[n];
		for(int i=0;i<n;i++){
			scanf("%d",bag+i);
		}

		sort(bag,bag+n,greater<int>());

		int sum = 0;
		for(int i=1;i<=n;i++){
			if(i%m==0) continue;
			sum += bag[i-1];
		}
		printf("%d\n",sum);
		delete[] bag;
	}
}

