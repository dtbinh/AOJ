
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
	int n;

	while(~scanf("%d",&n)){
		if(n==0) break;
		int table[7];
		memset(table,0,sizeof(table));
		for(int i=0;i<n;i++){
			int age;
			scanf("%d",&age);
			table[age/10 >= 6 ? 6 : age/10]++; 
		}

		for(int i=0;i<7;i++){
			printf("%d\n",table[i]);
		}
	}
}

