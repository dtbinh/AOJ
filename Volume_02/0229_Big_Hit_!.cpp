
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
typedef pair <P,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

int main(){

	int b,r,g,c,s,t;
	while(~scanf("%d %d %d %d %d %d",&b,&r,&g,&c,&s,&t)){
		if(b==r && r==g && g==c && c==s && s==t && t==0) break;
		int big = -3 * b + 15 * b + (15 - 2) * b * 5;
		int bar = -3 * r + 15 * r + (15 - 2) * r * 3;
		int sum = 100 + big + bar -3 * g + 7 * g + (-3 * c + 2 * c) + (-3 * s)
			-3 * (t-(b+b*5)-(r+r*3)-g-c-(s*2));
		cout << sum << endl;
	}
}

