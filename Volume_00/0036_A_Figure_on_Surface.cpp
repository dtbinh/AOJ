
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

typedef long long ll;
using namespace std;

bool in(int i,int j){
	if(i >= 0 && i<8 && j>=0 && j<8) return true;
	return false;
}

bool is_A(int i,int j,int table[8][8])
{
	if(table[i][j]==1
		&& in(i,j+1) && table[i][j+1]==1 
		&& in(i+1,j) && table[i+1][j]==1
		&& in(i+1,j+1) && table[i+1][j+1]==1
		) return true;

	return false;
}

bool is_B(int i,int j,int table[8][8])
{
	if(table[i][j]==1
		&& in(i+1,j) && table[i+1][j]==1 
		&& in(i+2,j) && table[i+2][j]==1
		&& in(i+3,j) && table[i+3][j]==1
		) return true;

	return false;
}

bool is_C(int i,int j,int table[8][8])
{
	if(table[i][j]==1
		&& in(i,j+1) && table[i][j+1]==1 
		&& in(i,j+2) && table[i][j+2]==1
		&& in(i,j+3) && table[i][j+3]==1
		) return true;

	return false;
}

bool is_D(int i,int j,int table[8][8])
{
	if(table[i][j]==1
		&& in(i,j+1) && table[i][j+1]==1 
		&& in(i-1,j+1) && table[i-1][j+1]==1
		&& in(i+1,j) && table[i+1][j]==1
		) return true;

	return false;
}

bool is_E(int i,int j,int table[8][8])
{
	if(table[i][j]==1
		&& in(i,j+1) && table[i][j+1]==1 
		&& in(i+1,j+1) && table[i+1][j+1]==1
		&& in(i+1,j+2) && table[i+1][j+2]==1
		) return true;

	return false;
}

bool is_F(int i,int j,int table[8][8]){
	if(table[i][j]==1
		&& in(i+1,j) && table[i+1][j]==1 
		&& in(i+1,j+1) && table[i+1][j+1]==1
		&& in(i+2,j+1) && table[i+2][j+1]==1
		) return true;

	return false;
}

bool is_G(int i,int j,int table[8][8]){
	if(table[i][j]==1
		&& in(i,j+1) && table[i][j+1]==1
		&& in(i+1,j-1) && table[i+1][j-1]==1
		&& in(i+1,j) && table[i+1][j]==1 		
		) return true;

	return false;
}

int main()
{
	int table[8][8];
	

	while(1){
		bool is_eof = false;
		memset(table,0,sizeof(table));
		for(int i=0;i<8;i++){
			char buf[32];
			if(scanf("%s",buf)==EOF){
				is_eof = true;
				break;
			}
			for(int j=0;j<8;j++){
				table[i][j]=buf[j]-'0';
			}
		}
		
		if(is_eof) break;

		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(is_A(i,j,table)){
					cout << 'A' << endl;
					goto found;
				}
				else if(is_B(i,j,table)){
					cout << 'B' << endl;
					goto found;
				}
				else if(is_C(i,j,table)){
					cout << 'C' << endl;
					goto found;
				}
				else if(is_D(i,j,table)){
					cout << 'D' << endl;
					goto found;
				}
				else if(is_E(i,j,table)){
					cout << 'E' << endl;
					goto found;
				}
				else if(is_F(i,j,table)){
					cout << 'F' << endl;
					goto found;
				}
				else if(is_G(i,j,table)){
					cout << 'G' << endl;
					goto found;
				}
			}
		}
found:;
	}
}

