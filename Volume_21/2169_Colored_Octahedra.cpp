#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
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
#include <cctype>
#include <utility>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int color2num(map<string,int>& dictionary,const string& color){
  if(dictionary.find(color) == dictionary.end()){
    int idx = dictionary.size();
    dictionary[color] = idx;
  }
  return dictionary[color];
}

class Octahedra{
public:
  int* upper_face;
  int* lower_face;

  Octahedra(){
    upper_face = new int[4]();
    lower_face = new int[4]();
  }

  void set_colors(const vector<int>& colors){
    for(int i=0;i<4;i++){
      upper_face[i] = colors[i];
      lower_face[i] = colors[4+i];
    }
  }

  int rotateZ(int turn){
    for(int t = 0; t < turn; t++){
      int tmp_upper[4];
      int tmp_lower[4];
      for(int i=0;i<4;i++){
	tmp_upper[(i+1)%4] = upper_face[i];
	tmp_lower[(i+1)%4] = lower_face[i];
      }
      for(int i=0;i<4;i++){
	upper_face[i] = tmp_upper[i];
	lower_face[i] = tmp_lower[i];
      }
    }
  }

  int rotateX(int turn){
    for(int t = 0; t < turn; t++){
      swap(upper_face[0],lower_face[2]);
      swap(upper_face[1],lower_face[1]);
      swap(upper_face[2],lower_face[0]);
      swap(upper_face[3],lower_face[3]);
    }
  }
  
  int rotateY(int turn){
    for(int t = 0; t < turn; t++){
      swap(upper_face[0],lower_face[0]);
      swap(upper_face[1],lower_face[3]);
      swap(upper_face[2],lower_face[2]);
      swap(upper_face[3],lower_face[1]);
    }
  }

  int write(){
    int res = 0;
    int digit = 1;
    for(int i=0;i<4;i++){
      res += upper_face[i] * digit;
      digit *= 8;
    }
    for(int i=0;i<4;i++){
      res += upper_face[i] * digit;
      digit *= 8;
    }
    return res;
  }
};

int main(){
  string color;

  while(cin >> color){
    vector<int> colors;
    map<string,int> dictionary;
    int color_num;
    color_num = color2num(dictionary,color);
    colors.push_back(color_num);
    for(int i=1;i<8;i++){
      cin >> color;

      color_num = color2num(dictionary,color);
      colors.push_back(color_num);
    }

    sort(colors.begin(),colors.end());

    int res = 0;
    set<int> visited;
    do {
      Octahedra oct;
      int state;
      bool isok = false;
      for(int i=0;i<8;i++){
	oct.set_colors(colors);
	oct.rotateX(i);
	state = oct.write();
	if(visited.count(state) == 0){
	  visited.insert(state);
	  isok = true;
	}

	oct.set_colors(colors);
	oct.rotateY(i);
	state = oct.write();
	if(visited.count(state) == 0){
	  visited.insert(state);
	  isok = true;
	}

	oct.set_colors(colors);
	oct.rotateZ(i);
	state = oct.write();
	if(visited.count(state) == 0){
	  visited.insert(state);
	  isok = true;
	}

      }

      if(isok) res++;
    }while(next_permutation(colors.begin(),colors.end()));

    printf("%d\n",res);
  }
}
