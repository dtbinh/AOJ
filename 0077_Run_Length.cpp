
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
typedef pair<int,int> P;

int main(){
	string str;
	while(cin >> str){
		string res;
		for(int i=0;i<str.size();i++){
			if(str[i]!='@') res.push_back(str[i]);
			else {
				char a = str[i+2];
				int n = str[i+1]-'0';
				string tmp="";
				for(int j=0;j<n;j++) tmp.push_back(a);
				res+=tmp;
				i+=2;
			}
		}

		cout << res << endl;
	}
}

