
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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;


void bottom(string str,string& ans){
	if(str.size() == 1){
		ans = str;
		return;
	}

	string next;

	for(int i=0;i<str.size()-1;i++){
		next.push_back((str[i]-'0'+str[i+1]-'0') % 10 + '0');
	}

	bottom(next,ans);
}

int main(){
	string str;
	while(cin>>str){
		string res;
		bottom(str,res);
		cout << res << endl;
	}
}

