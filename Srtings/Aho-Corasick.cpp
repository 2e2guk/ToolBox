// 일대다 문자열 패턴 매칭 알고리즘
// main 함수 사용 예시는 boj 9250
// Aho-Corasick
// 문자열의 길이 N, k개의 패턴, 각각의 길이 m[i] (1 <= i <= k)
// O(N + sigma(m[i], i : 1 ~ k))
#include <bits/stdc++.h>
using namespace std;

struct Trie {
    Trie *go[26];
    Trie *fail;
    bool output;

    Trie() {
        fill(go, go + 26, nullptr);
        output = false;
    }
    ~Trie() {
        for(int i = 0; i < 26; i++)
            if(go[i]) delete go[i];
    }
    void insert(const char* key) {
        if(*key == '\0'){
            output = true;
            return;
        }
        int next = *key - 'a';
        if(!go[next]) {
            go[next] = new Trie;
        }
        go[next]->insert(key + 1);
    }
};

void buildTrieAndFailureLinks(Trie *root, int N) {
    for(int i = 0; i < N; i++) {
        char str[10001];
        cin >> str;
        root->insert(str);
    }

    queue<Trie*> Q;
    root->fail = root;
    Q.push(root);
    while(!Q.empty()) {
        Trie *current = Q.front();
        Q.pop();

        for(int i = 0; i < 26; i++) {
            Trie *next = current->go[i];
            if(!next) continue;

            if(current == root) next->fail = root;
            else {
                Trie *dest = current->fail;
                while(dest != root && !dest->go[i])
                    dest = dest->fail;
                if(dest->go[i]) dest = dest->go[i];
                next->fail = dest;
            }
            if(next->fail->output) next->output = true;
            Q.push(next);
        }
    }
}

bool searchInTrie(Trie *root, const char *str) {
    Trie* current = root;
    for(int c = 0; str[c]; c++){
        int next = str[c] - 'a';
        while(current != root && !current->go[next])
            current = current->fail;
        if(current->go[next])
            current = current->go[next];
        if(current->output) 
            return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M;
    Trie* root = new Trie;

    cin >> N;
    buildTrieAndFailureLinks(root, N);

    cin >> M;
    for(int i = 0; i < M; i++) {
        char str[10001];
        cin >> str;
        cout << (searchInTrie(root, str) ? "YES" : "NO") << "\n";
    }

    delete root;
}
