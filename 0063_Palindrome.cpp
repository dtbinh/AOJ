
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

int main(){
	string str;
	int c=0;
	while(cin>>str){
		string tmp = str;
		reverse(str.begin(),str.end());
		if(tmp == str) c++;
	}
	cout << c << endl;
}

