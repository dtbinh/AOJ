
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
#include <cctype>
#include <utility>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
int main(){
    int m;
    while(~scanf("%d",&m)){
        for(int i=0;i<m;i++){
            int init;
            int n;
            int year;
            scanf("%d",&init);
            scanf("%d",&year);
            scanf("%d",&n);
            int res = 0;
            for(int j=0;j<n;j++){
                double a,b,c;
                 
                //0 0.03125 3000
                scanf("%lf %lf %lf",&a,&b,&c);
 
                if(a==1){
                    double A = init;
                    int rem=0;
                    for(int k=0;k<year;k++){
                        double B = floor(A * b);
                        A = A+B-c;
                    }
                    res = max(res,(int)A);
                }
                else{
                    double A = init;
                    int rem = 0;
                    int sum = 0;
                    for(int k=0;k<year;k++){
                        double B = floor(A * b);
                        A -= c;
                        sum += B;
                    }
                    res = max(res,(int)A+sum);
                }               
            }
 
            printf("%d\n",res);
        }
    }
}

