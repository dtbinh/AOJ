
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
typedef pair<int,int> P;

static const double eps = 1e-8;

int main(){
	const char oct[] = {'0','1','2','3','5','7','8','9'};
	ll n;
	while(~scanf("%lld",&n)){
		if(n==0) break;
		char buf[11];
		sprintf(buf,"%llo",n);

		for(int i=0;i<=10;i++){
			if(buf[i]=='\0') break;
			buf[i] = oct[buf[i]-'0'];
		}
		printf("%s\n",buf);
	}
}

