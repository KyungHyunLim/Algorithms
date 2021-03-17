#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<math.h>
using namespace std;

int tr;
int tc;
int c;

void solve(int N, int r, int c) {
	if (N == 2) {
		if (r == tr && c == tc) {
			printf("%d", c);
			return;
		}
		c++;
		if (r == tr && c + 1 == tc) {
			printf("%d", c);
			return;
		}
		c++;
		if (r == tr + 1 && c == tc) {
			printf("%d", c);
			return;
		}
		c++;
		if (r + 1 == tr && c + 1 == tc) {
			printf("%d", c);
			return;
		}
		c++;
		return;
	}

	if (!(r <= tr && tr < r + N && c <= tc && tc < c + N)) {
		c += (N * N);
		return;
	}

	solve(N / 2, r, c);
	solve(N / 2, r, c + (N / 2));
	solve(N / 2, r + (N / 2), c);
	solve(N / 2, r + (N / 2), c + (N / 2));
}


int main() {

	int N;
	scanf("%d %d %d", &N, &tr, &tc);

	c = 0;
	solve(pow(2,N),0,0);

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

/*
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;

int N,R,C,answer,cnt;

bool getAnswer(int r, int c, int size){
	if(size == 1){
		if(R == r && C == c){
			answer = cnt;
			return true;
		}
		cnt += 1;
		return false;
	}

	if(!(r<=R && R<r+size && c<=C && C<c+size)){
		cnt += size*size;
		return false;
	}

	int m = size/2;
	for(int i=0; i<2 ;i++){
		for(int j=0; j<2 ;j++){
			if(getAnswer(r+i*m, c+j*m, m))
				return true;
		}
	}
	return false;
}

int main(){
	scanf("%d %d %d",&N,&R,&C);
	getAnswer(0,0,(1<<N));
	printf("%d",answer);
}

*/