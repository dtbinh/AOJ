
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
typedef pair <int,int > P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
int main(){
    int a,b,c;
    while(~scanf("%d %d %d",&a,&b,&c)){
        if(a==b && b==c && c==0) break;
 
        if (c == 0) {
            if (a != 1)
                printf("%d %d %d %d\n", a, b, 1, 0);
            else
                printf("%d %d %d %d\n", 1, max(0, b), 1, min(0, b));
            continue;
        }
 
        for(int r=1;r*r<=a;r++){
            if(a%r != 0) continue;
            int p = a/r;
            for(int s=-10000;s<=10000;s++){
                if(s==0) continue;
                if(s!=0 && c%s !=0) continue;
                int q=c/s;
 
                if(q*r != b - p*s) continue;
                if((p>0 && r>0) 
                    && (p>r || (p==r && q>=s))){
                    printf("%d %d %d %d\n",p,q,r,s);
                    goto next;
                }
            }
        }
        printf("Impossible\n");
next:;
 
    }
}

