
#define _USE_MATH_DEFINES
#define INF 100000000
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

int main(){
	int n;
	while(~scanf("%d",&n)){
		int* data = new int[n];
		for(int i=0;i<n;i++){
			scanf("%d",data+i);
		}

		sort(data,data+n);
		int con=0;
		int sum=0;
		for(int i=0;i<n;i++){
			sum += con + data[i];
			con += data[i];
		}
		printf("%d\n",sum);
	}
}

