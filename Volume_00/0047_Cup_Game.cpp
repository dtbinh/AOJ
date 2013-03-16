
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

	char buf[8];
	int cups[] ={0,1,2};
	while(~scanf("%s,%s",buf)){
		swap(cups[buf[0]-'A'],cups[buf[2]-'A']);		
	}

	for(int i=0;i<3;i++){
		if(cups[i] == 0){
			printf("%c\n",i+'A');
		}
	}
	
}


