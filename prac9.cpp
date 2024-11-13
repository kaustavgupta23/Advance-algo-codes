#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    Node* links[26]={nullptr};
    bool flag = false;

    bool containsKey(char c) {
        return (links[c - 'a'] != nullptr);
    }

    void put(char c, Node* node) {
        links[c - 'a'] = node;
    }

    Node* get(char c) {
        return links[c - 'a'];
    }

    void setEnd() {
        flag = true;
    }

    bool isEnd() {
        return flag;
    }
};

class Trie {
public:
    Node* root = new Node;

    void insert(string word) {
        //cout<<"Inserted"<<endl;
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node);
            }
           node= node->get(word[i]);
        }
        node->setEnd();
    }

    bool search(string word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                return false;
            }
           node= node->get(word[i]);
        }
        return node->isEnd();
    }
};

int main() {
    string w = "minimize";
    reverse(w.begin(), w.end());

    vector<string> strings;
    cout << "Prefixes of reversed string:\n";
    for (int i = 0; i < w.length(); i++) {
        string temp = "";
        for (int j = 0; j <= i; j++) {
            temp += w[j];
        }
        reverse(temp.begin(),temp.end());
        strings.push_back(temp);
        cout << temp << " "; // Display each prefix
    }
    cout << endl;

    Trie t;
    for (int i = 0; i < strings.size(); i++) {
        t.insert(strings[i]);
    }

    if (t.search("mimize")) {
        cout << "present" << endl;
    } else {
        cout << "not present" << endl;
    }

    return 0;
}
