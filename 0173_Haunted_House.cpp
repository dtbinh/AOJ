
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
	char name[32];
	int am,pm;
	while(~scanf("%s %d %d",name,&am,&pm)){
		printf("%s %d %d\n",name,am+pm,am*200+pm*300);
	}
}

