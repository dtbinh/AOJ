
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

int change(int n){
	int res = 0;
	res += n / 500;
	n %= 500;
	res += n / 100;
	n %= 100;
	res += n / 50;
	n %= 50;
	res += n / 10;
	n %= 10;
	res += n / 5;
	n %= 5;
	res += n;
	return res;
}

int main(){
	int P;
	int N1,N5,N10,N50,N100,N500;
	while(~scanf("%d %d %d %d %d %d %d",&P,&N1,&N5,&N10,&N50,&N100,&N500)){
		if(P==0) break;
		int res = numeric_limits<int>::max();
		for(int i=P;i<=P+500;i++){
			int rem = i;
			int c=0;
			for(int j=1;j<=N500;j++){
				if(rem-500 >= 0){
					rem -= 500;
					c++;
				}
				else break;
			}
			for(int j=1;j<=N100;j++){
				if(rem-100 >= 0){
					rem -= 100;
					c++;
				}
				else break;
			}
			for(int j=1;j<=N50;j++){
				if(rem-50 >= 0){
					rem -= 50;
					c++;
				}
				else break;
			}
			for(int j=1;j<=N10;j++){
				if(rem-10 >= 0){
					rem -= 10;
					c++;
				}
				else break;
			}
			for(int j=1;j<=N5;j++){
				if(rem-5 >= 0){
					rem -= 5;
					c++;
				}
				else break;
			}
			for(int j=1;j<=N1;j++){
				if(rem-1 >= 0){
					rem -= 1;
					c++;
				}
				else break;
			}

			if(rem != 0) continue;
			res = min(c+change(i-P),res);
		}
		printf("%d\n",res);
	}
}



