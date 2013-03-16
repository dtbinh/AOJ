
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

	string str;
	map<string,int> freq;
	while(getline(cin,str,',')){
		string str2;
		cin >> str2;

		freq[str2]++;
	}

	cout << freq["A"] << endl;
	cout << freq["B"] << endl;
	cout << freq["AB"] << endl;
	cout << freq["O"] << endl;
}

