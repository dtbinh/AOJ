
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
	
	int d;
	string ge5[] = {"* ="," *="};
	string lt5[] = {" ****","* ***","** **","*** *", "**** "};
	bool isnl=false;
	while(~scanf("%d",&d)){
		if(isnl) cout << endl;
		vector<string> res;

		string str;
		while(d>0){ str += (d % 10) + '0'; d/=10;}
		reverse(str.begin(),str.end());

		//for(int i=0;i<str.size();i++){if(!isdigit(str[i])) str = str.substr(0,i); break;}
		while(str.size()<5) str = "0" + str;
		for(int i=0;i<str.size();i++){
			string tmp="";
			tmp = ge5[(str[i]-'0') >= 5 ? 1 : 0];
			tmp = tmp + lt5[(str[i]-'0') % 5];
			res.push_back(tmp);
		}

		while(res.size()<5) res.push_back(ge5[0]+lt5[0]);

		char table[8][5];
		for(int i=0;i<8;i++){
			for(int j=0;j<5;j++){
				table[i][j]=res[j][i];
				//printf("%c%s",res[j][i],j==res.size()-1 ? "\n" : "");
			}
		}

		for(int i=0;i<8;i++){
			for(int j=0;j<5;j++){
				cout << table[i][j];
			}
			cout << endl;
		}
		isnl = true;
	}

	exit(0);
}


