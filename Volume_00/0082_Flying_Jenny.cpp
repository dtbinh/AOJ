
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

int array2num(int* arg){
	int res=0;
	int mul=1;
	for(int i=8-1;i>=0;i--){
		res += arg[i]*mul;
		mul*=10;
	}
	return res;
}

int main(){

	int men[8];
	int merry[8]={1,2,1,2,1,4,1,4};

	while(~scanf("%d %d %d %d %d %d %d %d",men,men+1,men+2,men+3,men+4,men+5,men+6,men+7)){
		int min_score=numeric_limits<int>::max();
		int res[8];

		for(int i=0;i<8;i++){
			int merry_r[8];
			int count = 0;
			int idx=0;

			for(int j=i;;j++){
				if(j%8==i) count++;
				if(count >=2) break;
				merry_r[idx++]=merry[j%8];
			}

			int score=0;
			for(int j=0;j<8;j++){
				score += men[j]-merry_r[j] >= 0 ? men[j]-merry_r[j] : 0;
			}

			if(score < min_score){
				min_score = score;
				copy(merry_r,merry_r+8,res);
			}

			else if(score == min_score){
				int a = array2num(res);
				int b = array2num(merry_r);
				if(a > b){
					copy(merry_r,merry_r+8,res);
				}
			}
		}

		for(int i=0;i<8;i++){
			printf("%d%s",res[i],i==7 ? "\n" : " ");
		}
	}
}

