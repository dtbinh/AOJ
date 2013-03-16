
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

queue<string> split(string delim,string str){
	queue<string> res;
	str += delim;
	for(int i=0;i<str.size();i++){
		for(int j=1;i+j<=str.size();j++){
			if(str.substr(i,j).find(delim) != string::npos){
				//cout << str.substr(i,j) << endl;
				if(str.substr(i,j-1).size() > 0 ) res.push(str.substr(i,j-1));
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
		stack<double> stk;
		queue<string> res = split(" ",str);
	
		while(!res.empty()){
			string now = res.front();
			res.pop();


			if(now == "+"){
				double a = stk.top();
				stk.pop();
				double b = stk.top();
				stk.pop();

				stk.push(b+a);
			}
			else if(now == "/"){
				double a = stk.top();
				stk.pop();
				double b = stk.top();
				stk.pop();

				stk.push(b/a);
			}
			else if(now == "*"){
				double a = stk.top();
				stk.pop();
				double b = stk.top();
				stk.pop();

				stk.push(b*a);
			}
			else if(now == "-"){
				double a = stk.top();
				stk.pop();
				double b = stk.top();
				stk.pop();

				stk.push(b-a);
			}

			else{
				double num;
				sscanf(now.c_str(),"%lf",&num);
				stk.push(num);
			}
		}

		printf("%.6f\n",stk.top());
	}

}

