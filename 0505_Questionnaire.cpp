
#define _USE_MATH_DEFINES
#define INF 100000000
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

static const double eps = 1e-8;

class mycmp{
public:
	bool operator()(const P p1,const P p2){
		if(p1.first != p2.first) return p1.first > p2.first;
		else return p1.second < p2.second;
	}
};

int main(){
	int n,m;
	while(~scanf("%d %d",&n,&m)){
		if(n==m && m==0) break;
		vector<P> freq(m);
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				int isok;
				scanf("%d",&isok);
				freq[j].first += isok;
				freq[j].second = j+1;
			}
		}

		sort(freq.begin(),freq.end(),mycmp());

		for(int i=0;i<m;i++){
			printf("%s%d",i==0 ? "" : " ", freq[i].second);
		}
		printf("\n");
	}
}

