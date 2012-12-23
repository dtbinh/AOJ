
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

vector<string> split(string delim,string str){
	vector<string> res;
	str += delim;
	for(int i=0;i<str.size();i++){
		for(int j=1;i+j<=str.size();j++){
			if(str.substr(i,j).find(delim) != string::npos){
				if(str.substr(i,j-1).size() >0 ) res.push_back(str.substr(i,j-1));
				i+=j-1;
				break;
			}
		}
	}

	return res;
}

int main(){

	string str;
	while(getline(cin,str)){
		vector<string> res1;
		res1 = split(" ",str);

		vector<string> res2;
		for(int i=0;i<res1.size();i++){
			vector<string> tmp;
			tmp = split(",",res1[i]);
			for(int j=0;j<tmp.size();j++){
				res2.push_back(tmp[j]);
			}
		}

		vector<string> res3;
		for(int i=0;i<res2.size();i++){
			vector<string> tmp;
			tmp = split(".",res2[i]);
			for(int j=0;j<tmp.size();j++){
				res3.push_back(tmp[j]);
			}
		}

		vector<string> refined;
		for(int i=0;i<res3.size();i++){
			if(res3[i].size() <= 2 || res3[i].size() >=7) continue;
			refined.push_back(res3[i]);
		}
		

		for(int i=0;i<refined.size();i++){
			printf("%s%s",refined[i].c_str(),i==refined.size()-1 ? "\n" : " ");
		}
	}
}

