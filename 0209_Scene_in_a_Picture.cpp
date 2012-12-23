
#define _USE_MATH_DEFINES
#define INF 10000000
#include <iostream>
#include <sstream>
#include <cmath>
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
typedef pair<int,int> P;

static const double eps = 1e-8;

int stage[100][100];
int piece[50][50];

void rotate90(int size,int** input, int** output)
{
	for(int y=0;y<size;y++){
		for(int x=0;x<size;x++){
			double dx = x*cos(M_PI/2.0) - y*sin(M_PI/2.0) + (size-1);
			double dy = x*sin(M_PI/2.0) + y*cos(M_PI/2.0);

			output[(int)(dy+eps)][(int)(dx+eps)]=input[y][x];
		}
	}
}

void rotate180(int size,int** input, int** output)
{
	for(int y=0;y<size;y++){
		for(int x=0;x<size;x++){
			double dx = x*cos(M_PI) - y*sin(M_PI) + (size-1);
			double dy = x*sin(M_PI) + y*cos(M_PI) + (size-1);
			output[(int)(dy+eps)][(int)(dx+eps)]=input[y][x];
		}
	}
}

void rotate270(int size,int** input, int** output)
{

	for(int y=0;y<size;y++){
		for(int x=0;x<size;x++){
			double dx = x*cos(3.0*M_PI/2.0) - y*sin(3.0*M_PI/2.0);
			double dy = x*sin(3.0*M_PI/2.0) + y*cos(3.0*M_PI/2.0) + (size-1);

			output[(int)(dy+eps)][(int)(dx+eps)]=input[y][x];
		}
	}
}

void printStage(int size,int** stage){
	for(int y=0;y<size;y++){
		for(int x=0;x<size;x++){
			printf("%3d%s",stage[y][x], x==size-1 ? "\n" : " ");
		}
	}
	printf("\n");
}

int main(){
	int m,n;
	while(~scanf("%d %d",&n,&m)){
		if(m==n && n==0) break;
		for(int y=0;y<n;y++){
			for(int x=0;x<n;x++){
				scanf("%d",&stage[y][x]);
			}
		}

		int** piece = new int*[m];
		for(int i=0;i<m;i++) piece[i] = new int[m];

		int** tmp_piece = new int*[m];
		for(int i=0;i<m;i++) tmp_piece[i] = new int[m];

		for(int y=0;y<m;y++){
			for(int x=0;x<m;x++){
				scanf("%d",&piece[y][x]);
			}
		}

		int resx=INF,resy=INF;

		for(int sty = 0;sty<n-m+1;sty++){
			for(int stx=0; stx<n-m+1;stx++){
				bool isok = true;
				for(int piy=0,tmpy=sty;piy<m && tmpy<n;piy++,tmpy++){
					for(int pix=0,tmpx=stx;pix<m && tmpx<n;pix++,tmpx++){
						if(piece[piy][pix] == -1) continue;
						if(piece[piy][pix] != stage[tmpy][tmpx]) isok = false;
					}
				}

				if(isok){
					for(int y=0;y<m;y++){
						for(int x=0;x<m;x++){
							if(piece[y][x] == -1) continue;

							if(resy > sty+y){
								resy = sty+y;
								resx = stx+x;
							}
							else if(resy == sty+y){
								resx = min(resx,stx+x);
							}
						}
					}
				}

			}
		}

		//printStage(m,piece);
		rotate90(m,piece,tmp_piece);
		//printStage(m,tmp_piece);

		for(int sty = 0;sty<n-m+1;sty++){
			for(int stx=0; stx<n-m+1;stx++){
				bool isok = true;
				for(int piy=0,tmpy=sty;piy<m && tmpy<n;piy++,tmpy++){
					for(int pix=0,tmpx=stx;pix<m && tmpx<n;pix++,tmpx++){
						if(tmp_piece[piy][pix] == -1) continue;
						if(tmp_piece[piy][pix] != stage[tmpy][tmpx]) isok = false;
					}
				}

				if(isok){
					for(int y=0;y<m;y++){
						for(int x=0;x<m;x++){
							if(tmp_piece[y][x] == -1) continue;

							if(resy > sty+y){
								resy = sty+y;
								resx = stx+x;
							}
							else if(resy == sty+y){
								resx = min(resx,stx+x);
							}
						}
					}
				}

			}
		}

		rotate180(m,piece,tmp_piece);
		//printStage(m,tmp_piece);

		for(int sty = 0;sty<n-m+1;sty++){
			for(int stx=0; stx<n-m+1;stx++){
				bool isok = true;
				for(int piy=0,tmpy=sty;piy<m && tmpy<n;piy++,tmpy++){
					for(int pix=0,tmpx=stx;pix<m && tmpx<n;pix++,tmpx++){
						if(tmp_piece[piy][pix] == -1) continue;
						if(tmp_piece[piy][pix] != stage[tmpy][tmpx]) isok = false;
					}
				}

				if(isok){
					for(int y=0;y<m;y++){
						for(int x=0;x<m;x++){
							if(tmp_piece[y][x] == -1) continue;

							if(resy > sty+y){
								resy = sty+y;
								resx = stx+x;
							}
							else if(resy == sty+y){
								resx = min(resx,stx+x);
							}
						}
					}
				}

			}
		}

		rotate270(m,piece,tmp_piece);
		//printStage(m,tmp_piece);

		for(int sty = 0;sty<n-m+1;sty++){
			for(int stx=0; stx<n-m+1;stx++){
				bool isok = true;
				for(int piy=0,tmpy=sty;piy<m && tmpy<n;piy++,tmpy++){
					for(int pix=0,tmpx=stx;pix<m && tmpx<n;pix++,tmpx++){
						if(tmp_piece[piy][pix] == -1) continue;
						if(tmp_piece[piy][pix] != stage[tmpy][tmpx]) isok = false;
					}
				}

				if(isok){
					for(int y=0;y<m;y++){
						for(int x=0;x<m;x++){
							if(tmp_piece[y][x] == -1) continue;

							if(resy > sty+y){
								resy = sty+y;
								resx = stx+x;
							}
							else if(resy == sty+y){
								resx = min(resx,stx+x);
							}
						}
					}
				}

			}
		}

		if(resx == resy && resy == INF) printf("NA\n");
		else printf("%d %d\n",resx+1,resy+1);

		for(int i=0;i<m;i++) delete[] piece[i];
		delete[] piece;
		for(int i=0;i<m;i++) delete[] tmp_piece[i];
		delete[] tmp_piece;
	}
}

