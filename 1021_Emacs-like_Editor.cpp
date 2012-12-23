
#define _USE_MATH_DEFINES
#define INF 100000000
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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
#include <list>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

int posX=0;
int posY=0;
string buf="";

void ctrl_a(deque<string>& lines){
	posX=0;
}

void ctrl_e(deque<string>& lines){
	posX=lines[posY].size();
}

void ctrl_p(deque<string>& lines){
	if(posY>0) {
		posY--;
	}
	posX = 0;
}

void ctrl_n(deque<string>& lines){
	if(posY+1 < lines.size()) {
		posY++;
	}
	posX = 0;
}

void ctrl_f(deque<string>& lines){
	if(posX < lines[posY].size()) {
		posX++;
	}
	else if(posX == lines[posY].size()
		&& posY+1 < lines.size()){
			posY++;
			posX=0;
	}
}

void ctrl_b(deque<string>& lines){
	if(posX>0) {
		posX--;
	}
	else if(posX==0
		&& posY-1 >= 0){
			posY--;
			posX = lines[posY].size();
	}
}


void ctrl_d(deque<string>& lines){
	if(posX<lines[posY].size()) {
		string tmp = "";
		for(int i=0;i<lines[posY].size();i++){
			if(posX == i){
				continue;
			}
			tmp.push_back(lines[posY][i]);
		}
		lines[posY] = tmp;
	}
	else if(posX==lines[posY].size()
		&& posY+1 < lines.size()){
			string lower = lines[posY+1];
			lines[posY].append(lower);
			deque<string>::iterator it = lines.begin();
			advance(it,posY+1);
			lines.erase(it);
	}
	else return;
}


void ctrl_k(deque<string>& lines){
	if(posX==lines[posY].size()) {
		ctrl_d(lines);
		buf = "\n";
	}
	else if(posX<lines[posY].size()){
		string front="";
		string rear="";
		front = lines[posY].substr(0,posX);
		rear = lines[posY].substr(posX,lines[posY].size()-posX);	
		buf = rear;
		lines[posY] = front;
		posX = lines[posY].size();
	}
}


void ctrl_y(deque<string>& lines){
	if(buf.size()==0) return;

	else if(buf=="\n"){
		string rear = lines[posY].substr(posX,lines[posY].size()-posX);
		string front = lines[posY].substr(0,posX);

		lines[posY] = front;
		//deque<string>::iterator it = lines.begin();
		//advance(it,posY);
		deque<string> res;

		for(int i=0;i<posY;i++){
			res.push_back(lines[i]);
		}

		res.push_back(lines[posY]);
		res.push_back(rear);
		

		for(int i=posY+1;i<lines.size();i++){
			res.push_back(lines[i]);
		}
		
		lines = res;
		posY++;
		posX=0;
		//lines.insert(lines.begin()+posY,rear);
		//lines.insert(it,rear);
	}

	else{
		lines[posY].insert(posX,buf);
		posX += buf.size();
	}
}
int main(){
	deque<string> lines;
	string str;
	posX = 0;
	posY = 0;
	while(getline(cin,str)){		
		if(str == "END_OF_TEXT") break;
		lines.push_back(str);
	}

	while(cin >> str){
		if(str == "-") break;
		if(str == "a") ctrl_a(lines);
		if(str == "e") ctrl_e(lines);
		if(str == "p") ctrl_p(lines);
		if(str == "n") ctrl_n(lines);
		if(str == "f") ctrl_f(lines);
		if(str == "b") ctrl_b(lines);
		if(str == "d") ctrl_d(lines);
		if(str == "k") ctrl_k(lines);
		if(str == "y") ctrl_y(lines);
		//printf("after:%s posX:%d posY:%d \n",str.c_str(),posX,posY);
	}

	for(int i=0;i<lines.size();i++){
		cout << lines[i] << "\n";
	}

	return 0;
}


