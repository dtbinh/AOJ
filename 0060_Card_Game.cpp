
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

	int c1,c2,c3;
	bool cards[10+1];	

	while(~scanf("%d %d %d",&c1,&c2,&c3)){
		fill(cards,cards+11,true);
		cards[c1]=false;
		cards[c2]=false;
		cards[c3]=false;

		int total=0;
		int c=0;
		for(int i=1;i<=10;i++){
			if(cards[i]){
				total++;
				if(c1+c2+i <= 20){
					c++;
				}
			}
		}

		if(c*2 >= total){
			cout << "YES" << endl;
		}

		else{
			cout << "NO" << endl;
		}


	}
}

