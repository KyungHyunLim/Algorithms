/*
자기 방으로 돌아가기

핵심: 가장 많이 겹치는 수가 정답. 
(A번 경로가 겹치는 경우들이 5가지라면, 이 경우들은 절때 5번의 단위시간이 필요)

1. 케이스 별 시작과 도착점 설정
2. 구간을 사용한다는 의미로 roomlist[i]++ (i=지나가는 방들의 번호)
3. 시작이 짝수번이면 홀수번방 도 지나감, 도착이 홀수번이면 짝수번방도 지나감
4. 각 방을 지나가는 모든 경우 중 최대값 출력
*/

#include<iostream>
#include<cstring>
using namespace std;

#define MAX(A,B) A>B?A:B

int map[401][2];

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
	  int n;
    cin >> n;

    for(int i=0; i<n; i++){
         cin >> map[i][0] >> map[i][1];
    }

    int roomlist[401] = {0};
    memset(roomlist, 0, sizeof(roomlist));
    int start=0;
    int end = 0;
    int answer = 1;
    for(int i=0; i<n; i++){
    if(map[i][0] < map[i][1]) {
        start = map[i][0];
          end = map[i][1] ;
    }else{
        start = map[i][1];
        end = map[i][0];
    }	

    if(start % 2 == 0) start--;
    if(end % 2 == 1) end++;

    for(int j=start; j<end+1; j++){
        roomlist[j] += 1;
          answer = MAX(answer, roomlist[j]);
      }
    }
  	cout << "#" << test_case << " " << answer << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
