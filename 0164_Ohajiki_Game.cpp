
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
#include <deque>
#include <bitset>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 10e-8;

int main(){
	int len;
	while(~scanf("%d",&len)){
		if(len==0) break;
		int* a = new int[len];
		for(int i=0;i<len;i++){
			scanf("%d",a+i);
		}

		int n=32;
		int idx=0;
		while(n>0){
			n -= (n-1) % 5;
			printf("%d\n",n);
			n -= a[idx % len] >= n ? n : a[idx % len];
			printf("%d\n",n);
			idx++;
		}

		delete[] a;
	}
}

