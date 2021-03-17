#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>

using namespace std;
class Info {
public:
	string state;
	string nickname;
	string userId;
};
vector<string> solution(vector<string> record) {
	vector<string> answer;
	vector<Info> log;
	
	map<string, string> nick;
	pair<map<string, string>::iterator, bool> check;

	for (int i = 0; i < record.size(); i++) {
		istringstream iss(record[i]);
		vector<string> words{ istream_iterator<string>{iss},istream_iterator<string>{} };

		Info* newOne = new Info();
		newOne->state = words[0];
		newOne->userId = words[1];

		if (newOne->state == "Leave") {
			newOne->nickname = nick[newOne->userId];
		}
		else {
			newOne->nickname = words[2];
		}	

		log.push_back(*newOne);
		check = nick.insert(pair<string, string>(log[i].userId, log[i].nickname));
		if (check.second != true) {
			nick[log[i].userId] = log[i].nickname;
		}
	}


	for (int i = 0; i < log.size(); i++) {
		if (log[i].state == "Enter") {
			string temp = nick[log[i].userId] + "님이 들어왔습니다.";
			answer.push_back(temp);
		}
		else if (log[i].state == "Leave") {
			string temp = nick[log[i].userId] + "님이 나갔습니다.";
			answer.push_back(temp);
		}
	}


	return answer;
}
