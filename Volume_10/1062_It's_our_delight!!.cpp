
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
		if(n==0) break;

		int L_count=0;
		int L_ok=0;
		int D_count=0;
		int D_ok=0;
		int M_count=0;
		int M_ok=0;
		for(int i=0;i<n;i++){
			int h,m,d;
			scanf("%d:%d %d",&h,&m,&d);
			int time = (d-m >= 0 ? d-m : (60+d-m));
			bool isok = (time <= 8 ? true : false);

			int t = h*60+m;

			if(11*60 <= t && t <= 14*60 + 59){
				if(isok) L_ok++;
				L_count++;
			}
			else if(18*60 <= t && t <= 20*60 + 59){
				if(isok) D_ok++;
				D_count++;
			}
			else if((21*60 <= t && t <= 24*60)
				|| (0 <= t && t <= 1*60+59)){
					if(isok) M_ok++;
					M_count++;
			}
		}
		
		if(L_count==0){
			printf("lunch no guest\n");
		}
		else{
			printf("lunch %.0lf\n",floor(((L_ok)/(double)L_count + EPS) * 100.0));
		}

		if(D_count==0){
			printf("dinner no guest\n");
		}
		else{
			printf("dinner %.0lf\n",floor(((D_ok)/(double)D_count + EPS) * 100.0));
		}

		if(M_count==0){
			printf("midnight no guest\n");
		}
		else{
			printf("midnight %.0lf\n",floor(((M_ok)/(double)M_count + EPS) * 100.0));
		}
	}
}

