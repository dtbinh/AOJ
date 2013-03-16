
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
typedef pair<string,int> P;

int main(){
	int n;
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){
			int stage[9][9];

			int freq_x[9][10];
			int freq_y[9][10];
			int sect[9][10];

			memset(freq_x,0,sizeof(freq_x));
			memset(freq_y,0,sizeof(freq_y));
			memset(sect,0,sizeof(sect));

			for(int y=0;y<9;y++){
				for(int x=0;x<9;x++){
					scanf("%d",&stage[y][x]);
				}
			}

			for(int y=0;y<9;y++){
				for(int x=0;x<9;x++){
					freq_x[y][stage[y][x]]++;
				}
			}

			for(int x=0;x<9;x++){
				for(int y=0;y<9;y++){
					freq_y[x][stage[y][x]]++;
				}
			}

			for(int sx=0;sx<9;sx+=3){
				for(int sy=0;sy<9;sy+=3){
					for(int y=sy,i=0;i<3;y++,i++){
						for(int x=sx,j=0;j<3;x++,j++){
							sect[sy+sx/3][stage[y][x]]++;
						}
					}			
				}
			}

			for(int y=0;y<9;y++){
				for(int x=0;x<9;x++){
					printf("%s%d%s",(freq_x[y][stage[y][x]] > 1 
						|| freq_y[x][stage[y][x]] > 1
						|| sect[(y/3)*3+x/3][stage[y][x]] > 1) ? "*" : " ",stage[y][x],x == 9-1 ? "\n" : "");
				}
			}

			printf("%s",i!=n-1 ? "\n" : "");
		}
	}
}


