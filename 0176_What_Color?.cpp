
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

struct COLOR{
	string name;
	string R;
	string G;
	string B;
};

int hex2dec(string str){
	const char hex[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	return 16 * (int)lower_bound(hex,hex+16,str[0]) + (int)lower_bound(hex,hex+16,str[1]);
}

int main(){

	struct COLOR color[] = {
		"black","00","00","00",
		"blue","00","00","ff",
		"lime","00","ff","00",
		"aqua","00","ff","ff",
		"red","ff","00","00",
		"fuchsia","ff","00","ff",
		"yellow","ff","ff","00",
		"white","ff","ff","ff",
	};

	string str;
	while(cin >> str){
		if(str.size() == 1 && str[0] == '0') break;
		int r = hex2dec(str.substr(1,2));
		int g = hex2dec(str.substr(3,2));
		int b = hex2dec(str.substr(5,2));

		int dk = 10000000;
		int idx=0;
		for(int i=0;i<sizeof(color)/sizeof(struct COLOR); i++){
			int tmp;
			if(dk > (tmp=((r - hex2dec(color[i].R)) * (r - hex2dec(color[i].R))
				+ (g - hex2dec(color[i].G)) * (g - hex2dec(color[i].G))
				+ (b - hex2dec(color[i].B)) * (b - hex2dec(color[i].B))))){
					dk = tmp;
					idx=i;
			}
		}

		printf("%s\n",color[idx].name.c_str());
	}

}

