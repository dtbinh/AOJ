
#define _USE_MATH_DEFINES
#define INF 100000000
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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

static const double EPS = 1e-8;

int main(){
	map<string,string> button;
	button["1"] = "'"; button["11"] = ","; button["111"] = "."; 
	button["1111"] = "!"; button["11111"] = "?";
	button["2"] = "a"; button["22"] = "b"; button["222"] = "c";
	button["2222"] = "A"; button["22222"] = "B"; button["333333"] = "C";
	button["3"] = "d"; button["33"] = "e"; button["333"] = "f"; 
	button["3333"] = "D"; button["33333"] = "E"; button["333333"] = "F";
	button["4"] = "g"; button["44"] = "h"; button["444"] = "i";
	button["4444"] = "G"; button["44444"] = "H"; button["444444"] = "I";
	button["5"] = "j"; button["55"] = "k"; button["555"] = "l"; 
	button["5555"] = "J"; button["55555"] = "K"; button["555555"] = "L";
	button["6"] = "m"; button["66"] = "n"; button["666"] = "o"; 
	button["6666"] = "M"; button["66666"] = "N"; button["666666"] = "O";
	button["7"] = "p"; button["77"] = "q"; button["777"] = "r"; 
	button["7777"] = "s"; button["77777"] = "P"; button["777777"] = "Q"; button["7777777"] = "R"; button["77777777"] = "S";
	button["8"] = "t"; button["88"] = "u"; button["888"] = "v"; 
	button["8888"] = "T"; button["88888"] = "U"; button["888888"] = "V";
	button["9"] = "w"; button["99"] = "x"; button["999"] = "y";
	button["9999"] = "z"; button["99999"] = "W"; button["999999"] = "X"; button["9999999"] = "Y"; button["99999999"] = "Z";

	string str;
	while(cin >> str){
		//if(cin.eof()) break;
		string res="";
		for(int i=0;i<str.size();){
			bool found = false;
			for(int len=8;len>=1;len--){
				if(button.find(str.substr(i,len)) != button.end()){
					res+=button[str.substr(i,len)];
					i+=len;
					found = true;
					break;
				}
			}
			if(!found){
				int c=0;
				for(int pos=0;;pos++){
					if(str[i+pos]=='0') c++;
					else break;
				}
				i+=c;
				while(--c) res.append(" "); 

			}
		}
		cout << res <<  endl;
	}
}

