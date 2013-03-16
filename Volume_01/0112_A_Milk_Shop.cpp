
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		ll* ppl = new ll[n];
		for(int i=0;i<n;i++){
			scanf("%lld",ppl+i);
		}

		sort(ppl,ppl+n);
		ll wait=0;
		ll sum=0;
		for(int i=0;i<n-1;i++){
			wait += ppl[i];
			sum+=wait;
		}

		delete[] ppl;

		cout << sum << endl;
	}
}

