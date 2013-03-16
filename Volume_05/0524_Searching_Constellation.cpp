
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


int main(){
	int m;
	while(~scanf("%d",&m)){
		if(m==0) break;
		vector<P> stars;
		for(int i=0;i<m;i++){
			int x,y;
			scanf("%d %d",&x,&y);
			stars.push_back(P(x,y));
		}
		int n;
		vector<P> sky;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			int x,y;
			scanf("%d %d",&x,&y);
			sky.push_back(P(x,y));
		}

		map<P,int> diff;
		for(int i=0;i<sky.size();i++){
			for(int j=0;j<stars.size();j++){
				int diff_x = sky[i].first - stars[j].first;
				int diff_y = sky[i].second - stars[j].second;
				diff[P(diff_x,diff_y)]++;
			}
		}

		int x,y;
		for(map<P,int>::iterator it = diff.begin(); it != diff.end(); it++){
			if(it->second == stars.size()){
				x = it->first.first;
				y = it->first.second;
				break;
			}
		}
		printf("%d %d\n",x,y);
	}
}

