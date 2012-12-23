
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
	int n;
	scanf("%d",&n);
		for(int i=0;i<n;i++){
			int src,dst;
			scanf("%d %d",&src,&dst);
			if(src <= 5 && dst <= 5){
				if(src < dst){
					for(int j=src;j<=dst;j++){
						printf("%d%s",j,j == dst ? "\n" : " ");
					}
				}
				else if(src > dst){
					for(int j=src;j>=dst;j--){
						printf("%d%s",j,j == dst ? "\n" : " ");
					}
				}
			}
			else if(src >= 5 && dst >= 5){
				if(src < dst){
					for(int j=src;j<=dst;j++){
						printf("%d%s",j,j == dst ? "\n" : " ");
					}
				}
				else if(src > dst){
					for(int j=src;j<=9;j++){
						printf("%d ",j);
					}

					if(dst == 5){
						cout << 5 << endl;
						continue;
					}
					for(int j=5;j>=0;j--){
						printf("%d ",j);
					}

					for(int j=1;j<=4;j++){
						printf("%d ",j);
					}

					for(int j=5;j<=dst;j++){
						printf("%d%s",j,j == dst ? "\n" : " ");
					}
				}
			}

			else{
				if(src < dst){
					for(int j=src;j<=dst;j++){
						printf("%d%s",j,j == dst ? "\n" : " ");
					}
				}
				else if(src > dst){
					for(int j=src;j<=9;j++){
						printf("%d ",j);
					}

					for(int j=5;j>=dst;j--){
						printf("%d%s",j,j == dst ? "\n" : " ");
					}
				}
			}

		}
}


