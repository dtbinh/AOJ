
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

int main(){

	int year,month,day;
	while(~scanf("%d %d %d",&year,&month,&day)){
		char buf[64];
		sprintf(buf,"%04d%02d%02d",year,month,day);
		string str = buf;

		if("18680908" <= str && str <= "19120729"){
			printf("meiji %d %d %d\n",year-1868+1,month,day);
		}
		else if("19120730" <= str && str <= "19261224"){
			printf("taisho %d %d %d\n",year-1912+1,month,day);
		}
		else if("19261225" <= str && str <= "19890107"){
			printf("showa %d %d %d\n",year-1926+1,month,day);
		}
		else if("19890108" <= str){
			printf("heisei %d %d %d\n",year-1989+1,month,day);
		}
		else{
			printf("pre-meiji\n");
		}
	}
}

