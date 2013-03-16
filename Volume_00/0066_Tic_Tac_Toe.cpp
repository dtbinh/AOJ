
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
typedef long double ld;
typedef pair<int,int> P;

int is_col_ok(int stage[3][3],int type){
	for(int y=0;y<3;y++){
		if(stage[y][0] == stage[y][1] &&
			stage[y][1] == stage[y][2] &&
			stage[y][2] == type){
				return true;
		}
	}

	return false;
}

bool is_row_ok(int stage[3][3],int type){
	for(int x=0;x<3;x++){
		if(stage[0][x] == stage[1][x] &&
			stage[1][x] == stage[2][x] &&
			stage[2][x] == type){
				return true;
		}
	}

	return false;
}

bool is_diag_ok(int stage[3][3],int type){
	if(stage[0][0] == stage[1][1] &&
		stage[1][1] == stage[2][2] &&
		stage[2][2] == type){
			return true;
	}

	else if(stage[0][2] == stage[1][1] &&
		stage[1][1] == stage[2][0] &&
		stage[2][0] == type){
			return true;
	}

	return false;
}


int main(){
	string str;
	int stage[3][3];

	while(getline(cin,str)){
		for(int i=0;i<str.size();i++){
			int y = i / 3;
			int x = i % 3;

			if(str[i]=='s'){
				stage[y][x] = 0;
			}
			else if(str[i]=='o'){
				stage[y][x] = 1;
			}
			else if(str[i]=='x'){
				stage[y][x] = -1;
			}	
		}

		if(is_col_ok(stage,1) || is_row_ok(stage,1) || is_diag_ok(stage,1)){
			cout << "o" << endl;
		}

		else if(is_col_ok(stage,-1) || is_row_ok(stage,-1) || is_diag_ok(stage,-1)){
			cout << "x" << endl;
		}
		else{
			cout << "d" << endl;
		}
	}
}

