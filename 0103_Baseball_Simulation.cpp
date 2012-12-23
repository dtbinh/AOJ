
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

int get_score(ll* men){
	int score=0;

	ll tmp = *men;
	tmp >>= 3;
	while(tmp > 0){
		if(tmp | 1){
			score++;
		}
		tmp >>= 1;
	}
	*men = *men & ((1<<3) - 1);

	return score;
}

int main(){

	string str;
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;

		string str;
		ll men=0;
		int c=0;
		int score=0;
		while(cin >> str){
			if(str == "OUT"){
				c++;
			}
			else if(str == "HIT"){
				men <<= 1;
				men |= 1;

				score += get_score(&men);
			}
			else if(str == "HOMERUN"){
				men <<= 1;
				men |= 1;
				men <<= 3;

				score += get_score(&men);
			}

			if(c==3){
				cout << score << endl;
				c=0;
				score=0;
				men=0;
			}
		}
	}
}

