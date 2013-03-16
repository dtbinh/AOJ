
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

static const double EPS = 1e-8;

int tx[] = {1,0};
int ty[] = {0,1};


int main(){
	int n;
	scanf("%d",&n);

	vector<P> points(n);
	int a,b,c,d;
	while(~scanf("%d %d %d %d",&a,&b,&c,&d)){
		points[a-1].second = a;
		points[b-1].second = b;
		if(c>d){
			points[a-1].first += 3;
			
		}
		else if(c<d){
			points[b-1].first += 3;
		}
		else{
			points[a-1].first += 1;
			points[b-1].first += 1;
		}
	}

	sort(points.begin(),points.end(),greater<P>());

	vector<int> rank(n);

	int maxV = INF;
	int idx=0;
	int tmp=1;
	for(int i=0;i<points.size();i++){
		if(maxV > points[i].first){
			idx+=tmp;
			tmp=1;
			maxV = points[i].first;
			rank[points[i].second-1] = idx;
		}
		else if(maxV == points[i].first){
			rank[points[i].second-1] = idx;
			tmp++;
		}
	}

	for(int i=0;i<rank.size();i++){
		printf("%d\n",rank[i]);
	}
}

