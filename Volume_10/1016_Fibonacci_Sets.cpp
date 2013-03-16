
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
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

const static ll N = 1001;

short fib_table[10000000];

int fib(int n){
	if(n==-1 || n==0) return 1;
	else if(fib_table[n]!=-1) return fib_table[n];
	else return (fib_table[n] = ((fib(n-1) % N) + (fib(n-2) %N)) % N);
}

int main(){
	memset(fib_table,-1,sizeof(fib_table));

	int V,d;
	while(~scanf("%d %d",&V,&d)){
		int rank[N];
		int par[N];

		vector<int> fibs;
		for(int i=1;i<=V;i++){
			fibs.push_back(fib(i));
		}

		sort(fibs.begin(),fibs.end());
		int res=1;
		for(int i=1;i<fibs.size();i++){
			if(fibs[i]-fibs[i-1]>=d) res++;
		}

		cout << res << endl;
	}
}



