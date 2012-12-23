
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>

typedef long long ll;
using namespace std;


void paint(int cell[10][10],int x, int y, int size,int *maxC){
	if(size == 3){
		for(int i=x-2;i<=x+2;i++){
			for(int j=y-2;j<=y+2;j++){
				if(sqrt(pow((double)i-(double)x,2.0) + pow((double)j-(double)y,2.0)) <= 2.0){
					if(i >=0 && i< 10 && j>= 0&& j<10){
						cell[j][i]++;
						*maxC = max(cell[j][i],*maxC);
					}
				}
			}
		}
	}

	if(size == 2){
		for(int i=x-1;i<=x+1;i++){
			for(int j=y-1;j<=y+1;j++){
				if(i >=0 && i< 10 && j>= 0&& j<10){
					cell[j][i]++;
					*maxC = max(cell[j][i],*maxC);
				}
			}
		}
	}

	if(size == 1){
		int tx[5] = {-1,0,1,0,0};
		int ty[5] = {0,1,0,-1,0};
		for(int i=0;i<5;i++){
			cell[y+ty[i]][x+tx[i]]++;
			*maxC = max(cell[y+ty[i]][x+tx[i]],*maxC);
		}
	}
}

int main()
{
	int cell[10][10];
	fill((int*)cell,(int*)cell+10*10,0);
	string str;
	int maxC=0;
	int count=0;
	while(getline(cin,str,',')){
		string str2;

		getline(cin,str2,',');
		string str3;

		getline(cin,str3);		
		paint(cell,str[0]-'0',str2[0]-'0',str3[0]-'0',&maxC);
		
	}
	for(int i=0;i<10;i++) for(int j=0;j<10;j++) count += cell[i][j] == 0 ? 1 : 0;

	cout << count << endl;
	cout << maxC << endl;
}

