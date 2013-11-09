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
static const int MAX_SIZE = 500;

int check_paper(bitset<MAX_SIZE>* usagi_horizontal_flags,
		bitset<MAX_SIZE>* usagi_virtical_flags,
		bitset<MAX_SIZE>* usagi_diagonal_flags,
		bitset<MAX_SIZE>* neko_horizontal_flags,
		bitset<MAX_SIZE>* neko_virtical_flags,
		bitset<MAX_SIZE>* neko_diagonal_flags,
		int square_size,
		int usagi_num,
		int neko_num){
  int usagi_sum = 0;
  int neko_sum = 0;
  for(int i=0;i<square_size;i++){
    if(usagi_horizontal_flags[i].none()) usagi_sum++;
    if(usagi_virtical_flags[i].none()) usagi_sum++;

    if(neko_horizontal_flags[i].none()) neko_sum++;
    if(neko_virtical_flags[i].none()) neko_sum++;
  }

  if(usagi_diagonal_flags[0].none()) usagi_sum++;
  if(usagi_diagonal_flags[1].none()) usagi_sum++;

  if(neko_diagonal_flags[0].none()) neko_sum++;
  if(neko_diagonal_flags[1].none()) neko_sum++;

  if(square_size == 1){
    usagi_sum /= 3;
    neko_sum /= 3;
  }
  bool is_usagi_clear = false;
  bool is_neko_clear = false;
  if(usagi_sum >= usagi_num) is_usagi_clear = true;
  if(neko_sum >= neko_num) is_neko_clear = true;

  if(is_usagi_clear && is_neko_clear){
    //draw
    return 0;
  }

  else if(is_usagi_clear && !is_neko_clear){
    return 1;
  }

  else if(!is_usagi_clear && is_neko_clear){
    return 2;
  }

  else {
    return -1;
  }
}

int usagi_paper[1000001];
int neko_paper[1000001];

int main(){
  int square_size,usagi_num,neko_num,total_cards;
  while(~scanf("%d %d %d %d",&square_size,&usagi_num,&neko_num,&total_cards)){

    memset(usagi_paper,-1,sizeof(usagi_paper));
    memset(neko_paper,-1,sizeof(neko_paper));

    for(int y=0;y<square_size;y++){
      for(int x=0;x<square_size;x++){
	int num;
	scanf("%d",&num);
	usagi_paper[num] = y * square_size + x;
      }
    }
    for(int y=0;y<square_size;y++){
      for(int x=0;x<square_size;x++){
	int num;
	scanf("%d",&num);
	neko_paper[num] = y * square_size + x;
      }
    }


    bitset<MAX_SIZE> usagi_horizontal_flags[square_size];
    bitset<MAX_SIZE> usagi_virtical_flags[square_size];
    bitset<MAX_SIZE> usagi_diagonal_flags[2];

    bitset<MAX_SIZE> neko_horizontal_flags[square_size];
    bitset<MAX_SIZE> neko_virtical_flags[square_size];
    bitset<MAX_SIZE> neko_diagonal_flags[2];

    for(int pos=0;pos<square_size;pos++){
      for(int bit_idx=0;bit_idx<square_size;bit_idx++){
	usagi_horizontal_flags[pos][bit_idx] = true;
	usagi_virtical_flags[pos][bit_idx] = true;
	usagi_diagonal_flags[0][bit_idx] = true;
	usagi_diagonal_flags[1][bit_idx] = true;

	neko_horizontal_flags[pos][bit_idx] = true;
	neko_virtical_flags[pos][bit_idx] = true;
	neko_diagonal_flags[0][bit_idx] = true;
	neko_diagonal_flags[1][bit_idx] = true;
      }      
    }

    const string status[] = {"DRAW","USAGI","NEKO"};
    int res = 0;
    for(int card_idx=0;card_idx<total_cards;card_idx++){
      int num;
      scanf("%d",&num);

      if(usagi_paper[num] == -1 && neko_paper[num] == -1) continue;

      if(usagi_paper[num] != -1){
	int usagi_x = usagi_paper[num] % square_size;
	int usagi_y = usagi_paper[num] / square_size;
	// y:
	//x:0 1 2 ... 3 4 ...
	//  1
	//  2
	usagi_horizontal_flags[usagi_y][usagi_x] = false;
	usagi_virtical_flags[usagi_x][usagi_y] = false;
	if(usagi_x==usagi_y){
	  usagi_diagonal_flags[0][usagi_x] = false;
	}
	if(((square_size - 1) - usagi_x) == usagi_y){
	  usagi_diagonal_flags[1][usagi_x] = false;
	}
      }

      if(neko_paper[num] != -1){
	int neko_x = neko_paper[num] % square_size;
	int neko_y = neko_paper[num] / square_size;
	// y:
	//x:0 1 2 ... 3 4 ...
	//  1
	//  2
	neko_horizontal_flags[neko_y][neko_x] = false;
	neko_virtical_flags[neko_x][neko_y] = false;
	if(neko_x==neko_y){
	  neko_diagonal_flags[0][neko_x] = false;
	}
	if(((square_size - 1) - neko_x) == neko_y){
	  neko_diagonal_flags[1][neko_x] = false;
	}
      }

      int winner = check_paper(usagi_horizontal_flags,
			       usagi_virtical_flags,
			       usagi_diagonal_flags,
			       neko_horizontal_flags,
			       neko_virtical_flags,
			       neko_diagonal_flags,
			       square_size,
			       usagi_num,
			       neko_num);

      if(res == 0 && winner != -1 ) res = winner;
    }
    printf("%s\n",status[res].c_str());
  }
}
