
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
typedef pair <int,P> PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
int main(){
    int n,y;
    while(~scanf("%d",&n)){
        if(n==0) break;
        scanf("%d",&y);
 
        double maxv = -1;
        int res = 0;
        for(int i=0;i<n;i++){
            int b,r,t;
             
            scanf("%d %d %d",&b,&r,&t);
 
            double basic_int = 0;
            if(t==1){
                basic_int = 10000*(1.0+y*((double)r/100.0));
            }
            else{
                basic_int = 10000*pow(1.0+(double)r/100.0,y);
            }
 
            if(maxv < basic_int){
                maxv = basic_int;
                res = b;
            }
        }
 
        printf("%d\n",res);
    }
}

