
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
typedef pair<double,int> P;

static const double eps = 10e-9;

bool isA(string str){
	if(str.size() >= 1 && str[0] != '>') return false;
	if(str.size() >= 2 && str[1] != '\'') return false;

	int hist[] = {0,0};
	for(int i=2,j=0;i<str.size()-1;i++){
		if(str[i] == '='){
			hist[j]++;
		}
		else if(str[i] == '#') j++;
		else return false;
	}

	if(hist[0] != hist[1]) return false;
	if(hist[0] == 0 || hist[1] == 0) return false;
	if(str[str.size()-1] != '~') return false;

	return true;

}

bool isB(string str){
	if(str.size() >= 1 && str[0] != '>') return false;
	if(str.size() >= 2 && str[1] != '^') return false;

	if(str.size() <= 3) return false;

	string rear = str.substr(2,str.size()-2);

	bool isok=false;
	int i;
	for(i=0;i+1<rear.size();){
		if(rear.substr(i,2) == "Q="){
			isok=true;
			i+=2;
		}
		else break;
	}

	return (i+2 == rear.size() && isok && rear.substr(i,2) == "~~");
}

int main(){
	int n;
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){
			string str;
			cin >> str;

			if(isA(str)) cout << "A" << endl;
			else if(isB(str)) cout << "B" << endl;
			else cout << "NA" << endl;
		}
	}
	
}


