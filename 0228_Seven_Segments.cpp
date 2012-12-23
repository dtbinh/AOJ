
#define _USE_MATH_DEFINES
#define INF 10000000
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
#include <list>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <P,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

static const string numbers[] = {"1111110","0110000","1101101","1111001","0110011",
	"1011011","1011111","1110010","1111111","1111011"};
static const int order[] = {'g'-'a','f'-'a','e'-'a','d'-'a','c'-'a','b'-'a','a'-'a'};

string changeOrder(string numbers){
	reverse(numbers.begin(),numbers.end());
	return numbers;
}

void setStage(bitset<7>& stage,bitset<7>& next){
	for(int i=0;i<7;i++){
		if(next[i] & 1){
			stage[i] = ~stage[i];
		}
	}
}

int main(){

	int n;	
	while(~scanf("%d",&n)){
		if(n==-1) break;
		bitset<7> next;
		bitset<7> stage;
		for(int i=0;i<n;i++){
			int light;
			scanf("%d",&light);
			bitset<7> num(changeOrder(numbers[light]));
			next = stage ^ num;	
			setStage(stage,next);
			printf("%s\n",next.to_string().c_str());
			
		}
	}
}

