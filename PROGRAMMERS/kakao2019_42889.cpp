#include <string>
#include <vector>
#include <algorithm> 
using namespace std;
class Info {
public:
	int stage;
	float faliure;
};

vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	vector<Info> fail;

	std::sort(stages.begin(), stages.end());
	int i = 0;

	for (int i = 0; i < N; i++) {
		Info* newOne = new Info();
		newOne->faliure = 0;
		newOne->stage = i+1;
		fail.push_back(*newOne);
	}

	while(i < stages.size()){
		int num_stage = stages[i];
		int index = i;
		int count = 0;
		while (true) {
			if (i == stages.size() || (num_stage == N + 1)) {
				i++;
				break;
			}			
			if (num_stage == stages[i]) {
				count++;
				i++;
			}
			else {				
				break;
			}			
		}		
		fail[num_stage-1].faliure = (float)count / (float)(stages.size() - index);				
	}
		
	for (int i = 0; i < fail.size(); i++) {
		for (int j = 0; j < fail.size() - 1; j++) {
			float fltemp;
			int  intemp;
			if (fail[i].faliure > fail[j].faliure) {
				fltemp = fail[i].faliure;
				intemp = fail[i].stage;
				fail[i].faliure = fail[j].faliure;
				fail[i].stage = fail[j].stage;
				fail[j].faliure = fltemp;
				fail[j].stage = intemp;
			}
		}
	}

	for (int i = 0; i < fail.size(); i++) {
		for (int j = 0; j < fail.size() - 1; j++) {
			float fltemp;
			int  intemp;
			if (fail[i].faliure == fail[j].faliure) {
				if (fail[i].stage < fail[j].stage) {
					fltemp = fail[i].faliure;
					intemp = fail[i].stage;
					fail[i].faliure = fail[j].faliure;
					fail[i].stage = fail[j].stage;
					fail[j].faliure = fltemp;
					fail[j].stage = intemp;
				}
			}
		}
	}

	for (int i = 0; i < fail.size(); i++) {
		answer.push_back(fail[i].stage);
	}


	return answer;
}
