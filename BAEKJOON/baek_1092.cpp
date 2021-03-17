#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> crains;
vector<int> weights;
vector<bool> boxes;

int main() {

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        crains.push_back(temp);
    }

    int M;
    cin >> M;
    for (int i = 0; i < M; i++) {
        int temp;
        cin >> temp;
        weights.push_back(temp);
        boxes.push_back(false);
    }

    sort(crains.begin(), crains.end(), greater<int>());
    sort(weights.begin(), weights.end(), greater<int>());

    int count = 0;
    int checked = 0;
    while (true) {
        if (checked == M) break;
        for (int i = 0; i < crains.size(); i++) {
            for (int j = 0; j < weights.size(); j++) {
                if (boxes[j] || boxes[j] > crains[i]) continue;
                else {
                    boxes[j] = true;
                    checked++;
                    break;
                }
            }
        }
        count++;    
    }
    cout << count << endl;
    return 0;
}