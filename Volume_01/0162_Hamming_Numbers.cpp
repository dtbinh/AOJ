
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
#include <bitset>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 10e-8;

vector<int> split(string delim,string str){
	vector<int> res;
	str += delim;
	for(int i=0;i<str.size();i++){
		for(int j=1;i+j<=str.size();j++){
			if(str.substr(i,j).find(delim) != string::npos){
				int num = atoi(str.substr(i,j-1).c_str());
				if(str.substr(i,j-1).size() >0 ) res.push_back(num);
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
		vector<int> data = split(" ",str);
		if(data.size() == 1 && data[0] == 0) break;

		int res=0;
		for(int i=data[0];i<=data[1];i++){
			int tmp = i;
			while(tmp % 2 == 0){
				tmp /=2;
			}

			while(tmp % 3 == 0){
				tmp /=3;
			}

			while(tmp % 5 == 0){
				tmp /=5;
			}

			if(tmp==1) res++;
		}

		printf("%d\n",res);
	}
}

