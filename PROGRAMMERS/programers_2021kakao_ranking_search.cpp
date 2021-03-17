#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>

using namespace std;

unordered_map<string, int> MAP;
vector<int> List[4][3][3][3];

vector<int> solution(vector<string> info, vector<string> query) {

    MAP["-"] = 0;
    MAP["cpp"] = 1;
    MAP["java"] = 2;
    MAP["python"] = 3;
    MAP["backend"] = 1;
    MAP["frontend"] = 2;
    MAP["junior"] = 1;
    MAP["senior"] = 2;
    MAP["chicken"] = 1;
    MAP["pizza"] = 2;

    for (auto str : info) {
        stringstream ss(str);
        string language, work, career, food;
        int score;
        ss >> language >> work >> career >> food >> score;

        int indexes[4] = { MAP[language], MAP[work], MAP[career], MAP[food] };
        for (int i = 0; i < (1 << 4); i++) {
            int idx[4] = { 0 };
            for (int j = 0; j < 4; j++) {
                if (i & (1 << j)) {
                    idx[j] = indexes[j];
                }
            }
            List[idx[0]][idx[1]][idx[2]][idx[3]].push_back(score);
        }
    }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                for (int z = 0; z < 3; z++)
                    sort(List[i][j][k][z].begin(), List[i][j][k][z].end());

    vector<int> answer;
    for (auto str : query) {
        stringstream ss(str);
        string language, work, career, food, _and;
        int score;
        ss >> language >> _and >> work >> _and >> career >> _and >> food >> score;

        vector<int>::iterator it = lower_bound(
            List[MAP[language]][MAP[work]][MAP[career]][MAP[food]].begin(),
            List[MAP[language]][MAP[work]][MAP[career]][MAP[food]].end(),
            score
        );
        answer.push_back(List[MAP[language]][MAP[work]][MAP[career]][MAP[food]].end() - it);
    }

    return answer;
}

int main() {

    return 0;
}