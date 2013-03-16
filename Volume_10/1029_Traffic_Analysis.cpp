
#define _USE_MATH_DEFINES
#define INF 100000000
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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

static const double EPS = 1e-8;

int main(){
	int n,m;
	while(~scanf("%d %d",&n,&m)){
		if(n==m && m==0) break;

		vector<int> elapsedTime;
		elapsedTime.push_back(0);

		for(int i=0;i<n;i++){
			int t;
			scanf("%d",&t);
			elapsedTime.push_back(t);
		}
		for(int i=0;i<m;i++){
			int t;
			scanf("%d",&t);
			elapsedTime.push_back(t);
		}

		sort(elapsedTime.begin(),elapsedTime.end());

		int diff=0;
		for(int i=0;i+1<elapsedTime.size();i++){
			diff = max(diff,abs(elapsedTime[i+1]-elapsedTime[i]));
		}

		printf("%d\n",diff);
	}
}

