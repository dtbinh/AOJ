
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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;

int main(){

	int* sieve = new int[50001];
	fill((int*)sieve,(int*)sieve+50001,1);
	sieve[0]=0;
	sieve[1]=0;
	for(int i=2; i<= 50000; i++){
		if(sieve[i]==1){
			for(int j=i+i;j<=50000;j+=i){
				sieve[j]=0;
			}
		}
	}

	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		int sum=0;
		for(int i=1;i<=n/2;i++){
			if(sieve[n-i] == 1 && sieve[i] == 1){
				//cout << sum << endl;
				sum++;
			}
		}

		cout << sum << endl;
	}
}

