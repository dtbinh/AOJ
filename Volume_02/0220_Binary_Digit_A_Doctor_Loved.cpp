
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
#include <list>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

static const double eps = 1e-8;

int main(){
	double n;	
	while(~scanf("%lf",&n)){
		if(n==-1.0) break;
		int a = n;
		double b = n - (double)a;

		bitset<8> front;
		for(int i=0;i<8;i++){
			if(a & (1<<i)) front |= (1<<i);
		}

		bitset<4> rear;
		for(int i=0;i<4;i++){
			b*=2.0;
			if(b + eps > 1.0){
				rear |= (1<<i);
				b -= 1.0;
			}
		}

		if(!(b+eps > 0.0 && b-eps < 0.0) || a != front.to_ulong()) {
			printf("NA\n");
		}
		
		
		else {
			string r = rear.to_string();
			reverse(r.begin(),r.end());
			printf("%s.%s\n",front.to_string().c_str(),r.c_str());
		}
	}
}

