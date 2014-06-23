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
  
const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

class Book{
public:
  int read;
  int write;
  Book(int _r,int _w) : read(_r), write(_w) {}
  bool operator <(const Book& b) const {
    return (read != b.read ? (read < b.read) : (write < b.write));
  }
  bool operator >(const Book& b) const {
    return (read != b.read ? (read > b.read) : (write > b.write));
  }
};

bool dp[1000010];

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;

    vector<Book> books;

    int total_reading = 0;
    int total_writing = 0;
    for(int book_idx = 0; book_idx < N; book_idx++){
      int read,write;
      scanf("%d %d",&read,&write);
      books.push_back(Book(read,write));
      total_reading += read;
      total_writing += write;
    }

    sort(books.begin(),books.end());
    int longest_reading = (books.end()-1)->read;
    int remaining = total_reading - longest_reading;

    if(remaining < longest_reading){
      int fill_space = longest_reading - remaining;
      memset(dp,false,sizeof(dp));
      dp[0] = true;
      int max_fill = 0;
      for(int i=0; i < N - 1; i++){
	for(int j=fill_space; j>=0; j--){
	  if(j + books[i].write > fill_space) continue;

	  dp[j + books[i].write] = dp[j];
	  if(dp[j + books[i].write]){
	    max_fill = max(max_fill,j+books[i].write);
	  }
	}
      }

      printf("%d\n",total_reading + total_writing + (fill_space - max_fill));
    }
    else{
      printf("%d\n",total_reading + total_writing);
    }
  }
}
