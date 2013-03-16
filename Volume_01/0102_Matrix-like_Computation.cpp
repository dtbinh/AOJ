
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
typedef pair<int,int> P;

int main(){

	string str;
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;

		int** mat = new int*[n+1];
		for(int i=0;i<n+1;i++) mat[i] = new int[n+1];
		for(int y=0;y<n;y++){
			for(int x=0;x<n;x++){
				int num;
				scanf("%d",&num);
				mat[y][x] = num;
			}
		}

		int sum=0;
		int col=0;
		for(int y=0;y<n;y++){
			for(int x=0;x<n;x++){
				col += mat[y][x];
			}
			mat[y][n]=col;
			sum+=col;
			col=0;
		}

		int row=0;
		for(int x=0;x<n;x++){
			for(int y=0;y<n;y++){
				row += mat[y][x];
			}
			mat[n][x]=row;
			row=0;
		}

		mat[n][n] = sum;

		for(int y=0;y<=n;y++){
			for(int x=0;x<=n;x++){
				printf("%5d%s",mat[y][x],x==n ? "\n" : "");
			}
		}

		for(int i=0;i<n+1;i++) delete[] mat[i];
		delete[] mat;
	}
}

