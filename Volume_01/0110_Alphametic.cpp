
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
typedef pair<int,int> P;

vector<string> split(string delim,string str){
	vector<string> res;
	str += delim;
	for(int i=0;i<str.size();i++){
		for(int j=1;i+j<=str.size();j++){
			if(str.substr(i,j).find_first_of(delim) != string::npos){
				//cout << str.substr(i,j) << endl;
				if(str.substr(i,j-1).size() > 0 ){
					//int num;
					//sscanf(str.substr(i,j-1).c_str(),"%d",&num);
					//res.push_back(num);
					res.push_back(str.substr(i,j-1));

				}
				i+=j-1;
				break;
			}
		}
	}

	return res;
}

string calc(string a,string b){
	string res;
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	int carry = 0;
	int idx;
	for(int j=0;j<min(a.size(),b.size());j++){
		int lhs = a[j] - '0';
		int rhs = b[j] - '0';
		res.push_back((carry + lhs + rhs) % 10 + '0');
		carry = (carry + lhs + rhs) / 10 ? 1 : 0;
		idx =j;
	}

	for(int j=idx+1;j<max(a.size(),b.size());j++){
		if(a.size() > b.size()){
			int lhs = a[j] - '0';
			res.push_back((carry + lhs) % 10 + '0');
			carry = (carry + lhs) / 10 ? 1 : 0;
		}
		else{
			int rhs = b[j] - '0';
			res.push_back((carry + rhs) % 10 + '0');
			carry = (carry + rhs) / 10 ? 1 : 0;
		}
	}
	if(carry) res.push_back(carry+'0');
	reverse(res.begin(),res.end());

	return res;
}

int main(){
	string str;
	while(getline(cin,str)){
		vector<string> data = split("+=",str);

		for(int i=0;i<=9;i++){
			vector<string> tmp = data;
			for(int j=0;j<3;j++){
				replace(tmp[j].begin(),tmp[j].end(),'X',(char)('0'+i));
			}

			if(calc(tmp[0],tmp[1]) == tmp[2]){
				cout << i << endl;
				goto next;
			}
		}
		cout << "NA" << endl;
next:;
	}
}

