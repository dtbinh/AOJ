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
    dictionary[color] = dictionary.size();
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
      int tmp_upper[4];
      int tmp_lower[4];
      tmp_upper[1] = upper_face[0];
      tmp_lower[1] = upper_face[1];
      tmp_lower[2] = upper_face[2];
      tmp_upper[2] = upper_face[3];

      tmp_upper[0] = lower_face[0];
      tmp_lower[0] = lower_face[1];
      tmp_lower[3] = lower_face[2];
      tmp_upper[3] = lower_face[3];
      for(int i=0;i<4;i++){
	upper_face[i] = tmp_upper[i];
	lower_face[i] = tmp_lower[i];
      }
    }
  }
  
  int rotateY(int turn){
    for(int t = 0; t < turn; t++){
      int tmp_upper[4];
      int tmp_lower[4];
      tmp_lower[0] = upper_face[0];
      tmp_lower[1] = upper_face[1];
      tmp_upper[1] = upper_face[2];
      tmp_upper[0] = upper_face[3];

      tmp_lower[3] = lower_face[0];
      tmp_lower[2] = lower_face[1];
      tmp_upper[2] = lower_face[2];
      tmp_upper[3] = lower_face[3];
      for(int i=0;i<4;i++){
	upper_face[i] = tmp_upper[i];
	lower_face[i] = tmp_lower[i];
      }
    }
  }

  int write(){
    int res = 0;
    int digit = 1;
    for(int i=0;i<4;i++){
      res += upper_face[i] * digit;
      digit *= 9;
    }
    for(int i=0;i<4;i++){
      res += lower_face[i] * digit;
      digit *= 9;
    }
    return res;
  }

  int print_face(){
    for(int i=0;i<4;i++){
      printf("%d ",upper_face[i]);
    }
    printf("\n");
    for(int i=0;i<4;i++){
      printf("%d ",lower_face[i]);
    }
    printf("\n");
    printf("\n");
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

      for(int i=0;i<4;i++){
	for(int j=0;j<4;j++){
	  for(int k=0;k<4;k++){
	    oct.set_colors(colors);
	    oct.rotateX(i);
	    oct.rotateY(j);
	    oct.rotateZ(k);
	    state = oct.write();
	    if(visited.count(state) == 0){
	      visited.insert(state);
	      isok = true;
	    }
	  }
	}
      }
      if(isok) res++;
    }while(next_permutation(colors.begin(),colors.end()));

    printf("%d\n",res);
  }
}
