
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

using namespace std;

typedef long long ll;
typedef pair<double,int> P;

static const double eps = 10e-9;

int main(){
	double a,b;
	double eyesight[] = {0.2,0.6,1.1};
	int lFreq[4]={0,0,0,0};
	int rFreq[4]={0,0,0,0};

	while(~scanf("%lf %lf",&a,&b)){
		int idx1 = 3;
		int idx2 = 3;
		for(int i=0;i<3;i++){
			if(a < eyesight[i]){
				idx1 = i;
				break;
			}
		}

		for(int i=0;i<3;i++){
			if(b < eyesight[i]){
				idx2 = i;
				break;
			}
		}

		lFreq[idx1]++;
		rFreq[idx2]++;
	}

	for(int i=3;i>=0;i--){
		printf("%d %d\n",lFreq[i],rFreq[i]);
	}
}


