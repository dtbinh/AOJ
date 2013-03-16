
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
typedef pair<string,int> P;

int main(){
	string str;

	map<string,string> table;
	for(int y=1;y<=6;y++){
		for(int x=1;x<=5;x++){
			string key="";
			key = (char)(y+'0');
			key = key + (char)(x+'0');
			table[key]='a'+(x-1)+(y-1)*5;
		}
	}
	table["62"] = ".";
	table["63"] = "?";
	table["64"] = "!";
	table["65"] = " ";

	while(getline(cin,str)){

		string res="";
		for(int i=0;i<str.size();){
			if(table.find(str.substr(i,2)) != table.end()){
				res += table[str.substr(i,2)];
				i+=2;
			}
			else{
				res = "NA";
				break;
			}
		}

		cout << res << endl;
	}
}


