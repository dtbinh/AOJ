
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
typedef pair<int,int> P;

int main(){
	int a;
	double b,c;
	while(~scanf("%d,%lf,%lf",&a,&b,&c)){
		if(b/(c*c) >= 25){
			cout << a << endl;
		}
	}
}

