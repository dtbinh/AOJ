
#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
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
#include <cctype>
#include <utility>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
 
int main(){
    double a,l,x;
     
    while(~scanf("%lf %lf %lf",&a,&l,&x)){
        double s = (a+l+l)/2.0;
        double ca = sqrt(s*(s-a)*(s-l)*(s-l));
 
        double res = 0.0;
         
        for(double scale = 0.00001; scale < 1.0; scale += 0.00001){
            double e1 = scale * (l+x);
            double e2 = (1.0-scale) * (l+x);
 
            double s2 = (e1+e2+l)/2.0;
            if(s2*(s2-e1)*(s2-e2)*(s2-l) < 0) continue;
 
            double ca2 = sqrt(s2*(s2-e1)*(s2-e2)*(s2-l));
 
            res=max(ca+ca2+ca2,res);
        }
 
        printf("%lf\n",res);
    }
}

