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

class Color{
public:
  double L,a,b;
  Color(double _L,double _a,double _b) : L(_L),a(_a),b(_b){}
};

int main(){
  int color_num,student_num;
  while(~scanf("%d %d",&color_num,&student_num)){
    vector<Color> colors;
    for(int i=0;i<color_num;i++){
      double L,a,b;
      scanf("%lf %lf %lf",&L,&a,&b);
      colors.push_back(Color(L,a,b));
    }

    bool* flag = new bool[color_num];
    for(int i=0,j=0;i<color_num;i++,j++){
      flag[i] = false;
      if(j<student_num) flag[i] = true;
    }
    
    sort(flag,flag+color_num);
    
    double res = 0;
    do{
      vector<int> nodes;
      for(int i=0;i<color_num;i++){
	if(flag[i]) nodes.push_back(i);
      }
      double sum = 0;
      for(int i=0;i<nodes.size();i++){
	for(int j=i+1;j<nodes.size();j++){
	  int idx1 = nodes[i];
	  int idx2 = nodes[j];
	  sum += (colors[idx1].L - colors[idx2].L) * (colors[idx1].L - colors[idx2].L)
	    + (colors[idx1].a - colors[idx2].a) * (colors[idx1].a - colors[idx2].a)
	    + (colors[idx1].b - colors[idx2].b) * (colors[idx1].b - colors[idx2].b);
	}
      }
      res = max(sum,res);
    }while(next_permutation(flag,flag+color_num));

    printf("%.6lf\n",res);
  }
}
