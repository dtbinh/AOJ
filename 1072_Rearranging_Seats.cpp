
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
 
static const double EPS = 1e-8;
 
int main(){
    int r,c;
    while(~scanf("%d %d",&r,&c)){
        if(r==c && c==0) break;
        if(!(r % 2 == 1 && c % 2 ==1)) printf("yesn");
        else printf("non");
    }
}

