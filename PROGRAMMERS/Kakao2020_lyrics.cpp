#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

struct node {
    node* c[26];
    int cnt;
    bool term;
    node() : term(false), cnt(1) {
        memset(c, 0, sizeof(c));
    }
    ~node() {
        for (int i = 0; i < 10; i++) {
            if (c[i]) delete c[i];
        }
    }

    void insert(const char* key) {
        if (*key == '\0') term = true;
        else {
            int cur = *key - 'a';
            if (c[cur] == NULL) {
                c[cur] = new node();
            }
            else {
                c[cur]->cnt++;
            }
            c[cur]->insert(key + 1);
        }
    }

    int find(const char* key) {
        int cur = *key - 'a';
        if (*key == '?') {
            int temp = 0;
            for (int k = 0; k < 26; k++) {
                if (c[k] != NULL) {
                    temp += c[k]->cnt;
                }
            }
            return temp;
        }
        if (c[cur] == NULL) return 0;
        if (*(key + 1) == '?') return c[cur]->cnt;
        return c[cur]->find(key + 1);
    }
};

node* root[10001];
node* reverse_root[10001];

vector<int> solution(vector<string> words, vector<string> queries) {
    
    int word_size = words.size();
    int query_size = queries.size();
    vector<int> answer(query_size, 0);

    for (auto& a : words) {
        int size = a.size();

        const char* c = a.c_str();
        if (root[size] == NULL) root[size] = new node();
        root[size]->insert(c);

        string reversed = a;
        reverse(reversed.begin(), reversed.end());

        const char* rc = reversed.c_str();
        if (reverse_root[size] == NULL) reverse_root[size] = new node();
        reverse_root[size]->insert(rc);
    }

    int idx = 0;

    for (auto& a : queries) {
        int size = a.size();

        if (a[size - 1] == '?') {
            const char* c = a.c_str();

            if (root[size] == NULL) { idx++; continue; }
            else answer[idx] = root[size]->find(c);
        }
        else {
            string re = a;
            reverse(re.begin(), re.end());
            const char* rs = re.c_str();

            if (reverse_root[size] == NULL) { idx++; continue; }
            else answer[idx] = reverse_root[size]->find(rs);
        }
        idx++;
    }

    return answer;
}
