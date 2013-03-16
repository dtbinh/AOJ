
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

bool is_change(string str,char* tmp,int pos, int len){
	const char A[] = {'p','e','a','c','h'};
	const char B[] = {'a','p','p','l','e'};
	if(str.substr(pos,len) == "apple"){
		for(int i=pos,j=0;i<pos+len,j<5;i++,j++){
			tmp[i] = A[j];
		}
		return true;
	}

	else if(str.substr(pos,len) == "peach"){
		for(int i=pos,j=0;i<pos+len,j<5;i++,j++){
			tmp[i] = B[j];
		}

		return true;
	}

	return false;
}

int main(){

	string str;
	while(getline(cin,str)){
		char tmp[1024];
		strcpy(tmp,str.c_str());
		for(int i=0;i+4<str.size();i++){
			if(is_change(str,tmp,i,5)) i+=5;
		}

		cout << tmp << endl;
	}
}


