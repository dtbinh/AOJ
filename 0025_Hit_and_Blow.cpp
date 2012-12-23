
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>

typedef long long ll;
using namespace std;

int main()
{
	int c[8];
	while(~scanf("%d",c)){
		for(int i=1;i<8;i++){
			scanf("%d",c+i);
		}
		int h=0;
		int b=0;

		for(int i=0;i<4;i++){
			if(c[i]==c[i+4]){
				h++;
			}
		}

		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(c[i]==c[j+4] && i!=j){
					b++;
				}
			}
		}
		printf("%d %d\n",h,b);
	}
}

