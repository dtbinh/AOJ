
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

bool is_change(string& str,int pos, int len){
	const char A[] = {'H','o','s','h','i','n','a'};
	if(str.substr(pos,len) == "Hoshino"){
		for(int i=pos,j=0;i<pos+len,j<7;i++,j++){
			str[i] = A[j];
		}
		return true;
	}

	return false;
}

int main(){

	string str;
	while(getline(cin,str)){
		int n;
		sscanf(str.c_str(),"%d",&n);
		for(int idx=0;idx<n;idx++){
			getline(cin,str);
			for(int i=0;i+6<str.size();i++){
				if(is_change(str,i,7)) i+=6;
			}

			cout << str << endl;
		}
	}
}

