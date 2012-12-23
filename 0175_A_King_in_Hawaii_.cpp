
#define _USE_MATH_DEFINES
#define MAX_N 1000000
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

static const double eps = 1e-8;

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==-1) break;
		stack<int> stk;
		while(n>0){
			stk.push(n%4);
			n/=4;
		}

		if(stk.empty()) {
			printf("0\n");
			continue;
		}

		while(!stk.empty()){
			printf("%d",stk.top());
			stk.pop();
		}

		printf("\n");
	}
		
}

