
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

	int n;
	 
	while(~scanf("%d",&n)){
		if(n==0) break;

		vector<P> data;
		for(int i=0;i<n;i++){
			int c1,m1,s1,m2,s2,m3,s3,m4,s4;
			scanf("%d %d %d %d %d %d %d %d %d",&c1,&m1,&s1,&m2,&s2,&m3,&s3,&m4,&s4);
			int sum = 60*(m1+m2+m3+m4)+(s1+s2+s3+s4);
			data.push_back(P(sum,c1));
		}

		sort(data.begin(),data.end());

		printf("%d\n",data[0].second);
		printf("%d\n",data[1].second);
		printf("%d\n",data[data.size()-2].second);
	}
}

