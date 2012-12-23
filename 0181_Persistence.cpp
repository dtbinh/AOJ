
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

int C(int* book,int n,int m,int w){
	int j=0;
	for(int i=0;i<m;i++){
		int tmp = w;
		for(;j<n;){
			tmp-= book[j];
			if(tmp >= 0) j++;
			else {
				break;
			}
		}
	}

	if(j<n) return false;
	else return true;

}

int main(){
	int m,n;
	while(~scanf("%d %d",&m,&n)){
		if(m==n && n==0) break;

		int *book = new int[n]();
		for(int i=0;i<n;i++){
			scanf("%d",book+i);
		}

		int lb = 1;
		int ub = 1500000;
		int md;

		for(int i=0;i<100;i++){
			md = (lb+ub)/2;
			if(C(book,n,m,md)) ub = md;
			else lb = md;
		}

		printf("%d\n",ub);
		delete[] book;
	}
}

