
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
 
 
static const double EPS = 1e-8;

 
int tx[] = {-1,0,1,0};
int ty[] = {0,1,0,-1};
 
bool isPrime[300001];
 
 
 
int main()
{
    int N;
    while(~scanf("%d",&N)){
        if(N==1) break;
 
        bool isPrime[300001];
        memset(isPrime,-1,sizeof(isPrime));
 
        printf ("%d:",N);
        for(int i=2;i<=N;i++){
            if(!isPrime[i]) continue;
            if((N % 7 == 1 || N % 7 == 6)
                && (i % 7 == 1 || i % 7 == 6)
                && N % i == 0 && ((N / i) % 7 == 1 || (N / i) % 7 == 6) ){
                    for(int j=i+i;j<=300000;j+=i){
                        isPrime[j] = false;
                    }
                    printf(" %d",i);
            }
        }
        printf("\n");
    }
 
}

