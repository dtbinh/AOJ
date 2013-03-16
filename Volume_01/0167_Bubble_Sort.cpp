
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
		if(n==0) break;

		int* a = new int[n];
		for(int i=0;i<n;i++){
			scanf("%d",a+i);
		}

		int res=0;
		for(int i=0;i<n;i++){
			for(int j=0;j+1<n;j++){
				if(a[j]>a[j+1]){
					swap(a[j],a[j+1]);
					res++;
				}
			}
		}

		printf("%d\n",res);

		delete[] a;
	}
}

