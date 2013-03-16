
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

using namespace std;

typedef long long ll;
typedef pair<char,int> P;

static const double eps = 10e-9;

int getNum(int num){
	int a = num * num;
	int res=0;
	a/=100;
	for(int i=0;i<4;i++){
		res += (a % 10) * pow(10.0,i);
		a/=10;
	}

	return res;
}

int main(){
	int n;
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){
			int num;
			scanf("%d",&num);
			printf("Case %d:\n",i+1);
			for(int j=0;j<10;j++){
				num = getNum(num);
				printf("%d\n",num);
			}
		}
	}
}

