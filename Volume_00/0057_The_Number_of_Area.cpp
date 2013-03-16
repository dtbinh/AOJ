
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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;

int main(){

	int n;
	while(~scanf("%d",&n)){
		int sum=1;
		for(int i=0;i<n;i++){
			sum += i+1;
		}
		cout << sum << endl;
	}
}

