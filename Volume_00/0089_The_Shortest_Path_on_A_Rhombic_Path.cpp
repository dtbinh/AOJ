
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

vector<int> split(string delim,string str){
	vector<int> res;
	str += delim;
	for(int i=0;i<str.size();i++){
		for(int j=1;i+j<=str.size();j++){
			if(str.substr(i,j).find(delim) != string::npos){
				//cout << str.substr(i,j) << endl;
				int num;
				sscanf(str.substr(i,j-1).c_str(),"%d",&num);
				if(str.substr(i,j-1).size() > 0 ) res.push_back(num);
				i+=j-1;
				break;
			}
		}
	}

	return res;
}

int main(){
	string str;

	vector<vector<int> > table;

	while(getline(cin,str)){
		vector<int> tmp = split(",",str);
		table.push_back(tmp);
	}


	for(int i=0;i+1<table.size();i++){
		if(table[i].size() < table[i+1].size()){
			for(int j=0;j<table[i+1].size();j++){
				if(j==0){
					table[i+1][j]=table[i][j] + table[i+1][j];
				}
				else if(j==table[i+1].size()-1){
					table[i+1][j]=table[i][j-1] + table[i+1][j];
				}
				else{
					table[i+1][j]=max(table[i][j-1]+table[i+1][j],table[i][j]+table[i+1][j]);
				}			
			}
		}
		else{
			for(int j=0;j<table[i+1].size();j++){
				table[i+1][j]=max(table[i][j]+table[i+1][j],table[i][j+1]+table[i+1][j]);
			}
		}
	}

	cout << table[table.size()-1][0] << endl;
}

