
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
typedef pair<int,string> P;

static const double eps = 1e-8;

int main(){
	int L;
	while(~scanf("%d",&L)){
		if(L==0) break;
		int sum=0;
		int res=INF;
		for(int i=0;i<12;i++){
			int M,N;
			scanf("%d %d",&M,&N);
			sum += M-N;
			if(sum >= L){
				res = min(i+1,res);
			}
		}

		if(res==INF) printf("NA\n");
		else printf("%d\n",res);
	}
}

