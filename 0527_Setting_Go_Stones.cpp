
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
 
struct Jinfo{
    int start;
    int len;
};
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        //0:white
        //1:black
 
        bool field[100000];
        memset(field,0,sizeof(field));
        for(int i=0;i<n;i++){
            bool color;
            cin >> color;
 
            field[i] = color;
 
            if((i+1) % 2==0){
                if(i-1 >= 0 && field[i-1] != color){
                    for(int j=i-1;j>=0;j--){
                        if(field[j] == color) break;
                        field[j] = color;
                    }
                }
            }
        }
 
        printf("%d\n",count(field,field+n,false));
    }
}

