
#define _USE_MATH_DEFINES
#define INF 100000000
  
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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
  
int main(){
    string stage;
  
    while(cin >> stage){
  
        int m = 0;
        char prev = 'z';
        for(int i=0;i<stage.size();i++){
            if(stage[i] != prev && stage[i] == 'o'){
                m++;
            }
            prev = stage[i];
        }
  
        int b = 0;
        prev = 'z';
        for(int i=0;i<stage.size();i++){
            if(stage[i] != prev && stage[i] == 'x'){
                b++;
            }
            prev = stage[i];
        }
  
        if(m >= b) printf("%c\n",'o');
        else printf("%c\n",'x');
    }
}

