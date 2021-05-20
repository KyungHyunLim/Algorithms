/*
 체육복
 - Greedy 알고리즘
 
 1. 현재 시점에서 체육복을 입을 수 있는 학생이 가장 많도록 선택
 
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
	int answer = 0;
	int losts = lost.size();
	vector<bool> check;
	
	for (int i = 0; i < n+1; i++) {
		check.push_back(false);
	}

	for (int i = 0; i < reserve.size(); i++) {
		if (find(lost.begin(), lost.end(), (reserve[i])) != lost.end()) { //빌려줄 사람이 도둑 맞았으면 넘어가기
			losts--;										//2벌중 남은 1벌은 자신이 입어야 되니까.
			check[reserve[i]] = true;						//빌릴 필요 없다는 의미로 check를 true로.
			continue;
		}

	}


	for (int i = 0; i < reserve.size(); i++) {
		if (check[reserve[i]]) continue;
		bool pre = find(lost.begin(), lost.end(), (reserve[i] - 1)) != lost.end();	//이전 번호 잃어 버렸나 검사
		bool post = find(lost.begin(), lost.end(), (reserve[i] + 1)) != lost.end(); //다음 번호 잃어 버렸나 검사

		//0. 둘다 도둑 않맞았므면 넘어가기
		if (!pre && !post) continue;

		//1. 이전 번호만 도둑 맞음 && 빌리지 않았으면
		if (pre && !post && !check[reserve[i] - 1]) {
			losts--;						//잃어 버린 학생 수 감소
			check[reserve[i] - 1] = true;	//받았으니 true
		}
		//2. 다음 번호만 도둑 맞음 && 빌리지 않았으면
		else if (!pre && post && !check[reserve[i] + 1]) {
			losts--;						//잃어 버린 학생 수 감소
			check[reserve[i] + 1] = true;	//받았으니 true
		}
		//3. 둘다 도둑 맞음.
		else if(pre && post){
			if (!check[reserve[i] - 1]) { //이전 번호가 빌리지 못했으면 빌려주고
				losts--;
				check[reserve[i] - 1] = true;
			}
			else if(!check[reserve[i] + 1]){	//이전 번호가 빌렸으면 다음 번호 빌려주기
				losts--;
				check[reserve[i] + 1] = true;
			}
		}
	}

	answer = n - losts;
	
	return answer;
}
