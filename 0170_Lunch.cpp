
#define _USE_MATH_DEFINES
#define MAX_N 1000000
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

static const double eps = 1e-8;

struct FOOD{
	string name;
	int w;
	int s;
};

bool checkWeight(const struct FOOD* food,const int* table,int n){
	
	int sum=0;
	for(int i=n-1,j=n-2;i>=1,j>=0;i--,j--){
		sum += food[table[i]].w;
		if(food[table[j]].s < sum) return false;
	}

	return true;
}

double getG(const struct FOOD* food,const int* table,int n){

	double G=0;
	double sum=0;
	for(int i=0;i<n;i++){
		G += (double)food[table[i]].w * (i+1);
		sum += (double)food[table[i]].w;
	}
	return G / sum;
}

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;

		struct FOOD* food = new struct FOOD[n];

		for(int i=0;i<n;i++){
			char buf[64];
			int w,s;
			scanf("%s %d %d",buf,&w,&s);
			food[i].name = buf;
			food[i].s = s;
			food[i].w = w;
		}

		int* table = new int[n];
		for(int i=0;i<n;i++) table[i] = i;

		int* res = new int[n]();
		double minG = 1000000.0;

		do{
			double tmpG;
			if(checkWeight(food,table,n) &&
				minG > (tmpG = getG(food,table,n))){
					copy(table,table+n,res);
					minG = tmpG;
			}
		}while(next_permutation(table,table+n));

		for(int i=0;i<n;i++){
			printf("%s\n",food[res[i]].name.c_str());
		}

		delete[] food;
		delete[] table;
	}
}

