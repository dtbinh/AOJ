
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
typedef pair<double,double> P;



int main(){
	int n;
	string str;
	while(getline(cin,str)){
		sscanf(str.c_str(),"%d",&n);
		if(n==0) break;

		int** stage = new int*[n];
		for(int i=0;i<n;i++) stage[i] = new int[n];


		for(int i=0;i<n;i++){
			getline(cin,str);
			for(int j=0;j<n;j++){
				if(str[j]=='*')	stage[i][j] = 1;
				else stage[i][j] = 0;
			}
		}

		int ub = 1000;
		int lb = 0;
		int md;

		for(int i=0;i<20;i++){
			md = (ub+lb) / 2;
			
			bool ok=false;
			for(int sy=0;sy+md-1<n;sy++){
				for(int sx=0;sx+md-1<n;sx++){
					ok = true;

					for(int y=0;y<md;y++){
						for(int x=0;x<md;x++){
							if(stage[y+sy][x+sx] == 1){
								ok=false;
								goto cant;
							}
						}
					}
cant:;
					if(ok) goto found;
				}
			}
found:;
			if(ok) lb = md;
			else ub = md;
		}

		cout << md << endl;

		for(int i=0;i<n;i++) delete[] stage[i];
		delete[] stage;
	}
}

