
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

		int* a = new int[n];
		for(int i=0;i<n;i++){
			scanf("%d",a+i);
		}

		int dst;
		scanf("%d",&dst);
		
		int lb = 0;
		int ub = n-1;

		int res=0;
		for(int i=0;i<50;i++){
			res++;
			int md = (lb+ub)/2;

			if(dst == a[md]){
				break;
			}
			else if(dst < a[md]){
				ub = md-1;
			}
			else{
				lb = md+1;
			}
			
			if(ub<lb){
				break;
			}
		}
		printf("%d\n",res);
		delete[] a;
	}
}

