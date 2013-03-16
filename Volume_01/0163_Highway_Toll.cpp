
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

struct IC{
	int fare;
	int dist;
};

int main(){
	int dpt,arv;

	struct IC ic[] = {
		300,6,
		500,13,
		600,18,
		700,23,
		1350,43,
		1650,58,

		350,7,
		450,12,
		600,17,
		1150,37,
		1500,52,

		250,5,
		400,10,
		1000,30,
		1350,45,

		250,5,
		850,25,
		1300,40,

		600,20,
		1150,35,

		500,15,
	};

	while(~scanf("%d",&dpt)){
		if(dpt==0) break;
		
		int hDpt,mDpt;
		scanf("%d %d",&hDpt,&mDpt);
		scanf("%d",&arv);
		int hArv,mArv;
		scanf("%d %d",&hArv,&mArv);

		int DptT = hDpt*60+mDpt;
		int ArvT = hArv*60+mArv;


		int idx=0;
		int fare=0,dist=0;
		for(int i=1;i<=7;i++){
			for(int j=i+1;j<=7;j++){
				if(i==dpt && j==arv){
					fare = ic[idx].fare;
					dist = ic[idx].dist;
					goto found;
				}
				idx++;
			}
		}

found:;

		if(((17*60+30 <= DptT && DptT <= 19*60+30)
			|| (17*60+30 <= ArvT && ArvT <= 19*60+30))
			&& dist <= 40){
				fare /=2;
		}

		int tmp = fare / 50;
		if(fare % 50) fare = 50 * (tmp+1);

		printf("%d\n",fare);
	}
}

