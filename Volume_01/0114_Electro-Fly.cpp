
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

ll GCD(ll a ,ll b){
	return b > 0 ? GCD(b,a%b) : a;
}

ll LCM(ll a ,ll b){
	return a / GCD(a,b) * b;
}
int main(){
	int a[3],m[3];
	while(~scanf("%d %d %d %d %d %d",a,m,a+1,m+1,a+2,m+2)){
		int p[3]={1,1,1};
		int c[3]={0,0,0};
		bool end=true;
		for(int i=0;i<3;i++){
			if(a[i]!=0 || m[i]!=0){
				end = false;
				break;
			}
		}

		if(end) break;

		for(int i=0;i<3;i++){
			do{
				p[i] = a[i]*p[i]%m[i];
				c[i]++;
			}while(p[i] != 1);
		}
		cout << LCM(LCM(c[0],c[1]),c[2]) << endl;
	}
}


