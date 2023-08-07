//made by alaa

#include<iostream>
#include<string>
#include<queue>
#include<fstream>
#include<cmath>
#include <iomanip>

using namespace std;

string remove_Space(string s) {
    if (s == "") { return ""; }
    int pos_begin = -1, pos_end;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
            pos_begin = i;
            break;
        }
    }
    if (pos_begin == -1) {
        return "";
    }
    for (int i = s.length() - 1; i > 0; i--) {
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
            pos_end = i;
            break;
        }
    }
    s = s.substr(pos_begin, pos_end - pos_begin + 1);
    return s;
}
int count_Space(string s) {
    int space = 0;
    while (s[space] == ' ')space++;
    return space;
}
string print_Space(int n) {
    string s = "";
    for (int i = 1; i <= n; i++)s += " ";
    return s;
}
struct charnode {
    char ch;
    int freq;
    charnode* left, * right;
    charnode(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        left = right = NULL;
    }

};
struct charmap {
    vector<charnode> charnodes;
    void operator[](char key) {
        int count = 0;
        for (int i = 0; i < charnodes.size(); i++) {
            if (charnodes.at(i).ch == key) {
                charnodes.at(i).freq++;
                count++;
            }
        }
        if (count == 0) charnodes.push_back(charnode(key, 1));
    }
};

struct charVector {
    char ch;
    string s;
    charVector(char ch, string s) {
        this->ch = ch;
        this->s = s;
    }
};
struct  charValue {
    vector<charVector> cValue;
    string operator[](char ch) {
        for (int i = 0; i < cValue.size(); i++) {
            if (cValue.at(i).ch == ch) return cValue.at(i).s;
        }
    }
};
struct freqComp {
    bool operator()(charnode* l, charnode* r) {
        return (l->freq > r->freq);
    }

};
void storevalues(charnode* chartree, charValue* a, string s) {
    if (chartree == NULL) return;
    if (chartree->ch != '$') a->cValue.push_back(charVector(chartree->ch, s));
    storevalues(chartree->left, a, s + "0");
    storevalues(chartree->right, a, s + "1");
}

void huffmanTree(priority_queue<charnode*, vector<charnode*>, freqComp>* chartree, charValue* cValue) {

    charnode* left, * right, * a, * newnode;
    while (chartree->size() != 1) {
        left = chartree->top();
        chartree->pop();
        right = chartree->top();
        chartree->pop();
        newnode = new charnode('$', left->freq + right->freq);
        newnode->left = left;
        newnode->right = right;
        chartree->push(newnode);
    }
    a = chartree->top();
    storevalues(a, cValue, "");
}

string decoding(charnode* chartree, string s, queue<string> newlines, queue<string> spaces) {

    string decomp = "", nl = "";
    charnode* current = chartree;
    for (int i = 0; i < s.size(); i++)
    {
        if (i == 0) {
            decomp = spaces.front();
            spaces.pop();
        }
        if (!newlines.empty() && nl == newlines.front()) {
            decomp += '\n';
            decomp += spaces.front();
            spaces.pop();
            newlines.pop();
            nl = "";
        }
        if (s[i] == '0') current = current->left;
        else current = current->right;

        if (current->left == NULL && current->right == NULL) {
            decomp += current->ch;
            nl += current->ch;
            current = chartree;
        }
    }

    return decomp;
}
int BinaryToDecimal(string s, int i) {
    if (i != -1) {
        int a = s[i] - '0';
        return (pow(2, 7 - i) * a) + BinaryToDecimal(s, i - 1);
    }
    else return 0;

}

string outcomp(string s) {

    string out = "", in;
    unsigned char codedChar;
    while (s.size() >= 8) {
        in = BinaryToDecimal(s.substr(0, 8), 7);
        out += in;
        s = s.substr(8, s.size() - 8);
        if (s.size() != 0 && s.size() < 8)s = "0" + s;
    }
    return out;
}
string outDecomp(string s) {

    char a;
    unsigned char b;
    int n, count = -1;
    string s1 = "", s2 = "", s3 = "", sz;
    for (int k = 0; k < s.size(); k++) {
        b = (s[k]);
        n = b;
        for (int i = 0; i < 8; i++) {
            a = (n % 2) + '0';
            s1 = a + s1;
            n /= 2;
        }
        if (count != -1) {
            sz = s1.substr(0, s1.size() - (s1.size() - count));
            s1 = s1.substr(0, s1.size() - (s1.size() - count)) + '\n' + s1.substr(count, s1.size() - sz.size());
        }
        s2 += s1;
        s1 = "";
    }
    return s2;
}

charmap setCodes(string file_name, queue<int>& spacesNum) {
    charmap  chars;
    string s, s1;
    ifstream fin;
    fin.open(file_name.c_str(), ios::in);
    if (fin.is_open()) {
        while (getline(fin, s1)) {
            spacesNum.push(count_Space(s1));
            s = remove_Space(s1);
            for (int i = 0; i < s.size(); i++) {
                chars[s[i]];
            }
        }
    }
    fin.close();
    return chars;
}

queue<string> setNewLines(string file_name) {

    queue<string>newlines;
    string s, s1;
    ifstream fin;
    fin.open(file_name.c_str(), ios::in);
    if (fin.is_open()) {
        while (getline(fin, s1)) {
            s = remove_Space(s1);
            if (fin.peek() != EOF)newlines.push(s);
        }
    }
    fin.close();
    return newlines;
}

void Compressing(string file_name, string new_file_name) {
    string s, s1 = "", s2, s3 = "";
    unsigned char codedChar;
    charmap  chars;
    charValue* cValue = new charValue;
    queue<string>newlines;
    queue<char> a = {};
    queue<int>spacesNum;
    priority_queue<charnode*, vector<charnode*>, freqComp> chartree;



    chars = setCodes(file_name, spacesNum);

    for (int i = 0; i < chars.charnodes.size(); i++) {
        charnode* a = &(chars.charnodes.at(i));
        chartree.push(a);
    }

    huffmanTree(&chartree, cValue);

    ifstream fin;
    fstream fout;

    fin.open(file_name.c_str(), ios::in);
    fout.open(new_file_name.c_str(), ios::out);
    if (fout.is_open() && fin.is_open()) {
        while (getline(fin, s2)) {
            s = remove_Space(s2);
            for (int i = 0; i < s.size(); i++)s1 += cValue->operator[](s[i]);
        }
        if (s1.size() % 8 != 0) {
            s3 = s1.substr(0, (s1.size() / 8) * 8);
            s1 = s1.erase(0, (s1.size() / 8) * 8);
            while (s1.size() != 8) s1 = "0" + s1;
            s1 = "0" + s1;
            s1 = s3 + s1;
        }
        fout << outcomp(s1);
        cout << outcomp(s1);
    }

    fin.close();
    fout.close();



}

void Decompress(string file_name  ,string newde_file_name) {
    string  us = "", s, s1,s2,s3;
    charmap  chars;
    charValue* cValue = new charValue;
    queue<int>spacesNum;
    queue<string>spaces;
    priority_queue<charnode*, vector<charnode*>, freqComp> chartree;


    chars = setCodes(file_name, spacesNum);
    while (!spacesNum.empty()) {
        spaces.push(print_Space(spacesNum.front()));
        spacesNum.pop();
    }
    for (int i = 0; i < chars.charnodes.size(); i++) {
        charnode* a = &(chars.charnodes.at(i));
        chartree.push(a);
    }

    huffmanTree(&chartree, cValue);


    char ch;

    ifstream fin;
    ofstream fout1;
    fout1.open(newde_file_name, ios::out);
    fin.open(file_name.c_str(), ios::in);

    if ( fin.is_open()&& fout1.is_open()) {
        while (getline(fin, s2)) {
            s = remove_Space(s2);
            for (int i = 0; i < s.size(); i++)s1 += cValue->operator[](s[i]);
        }
        if (s1.size() % 8 != 0) {
            s3 = s1.substr(0, (s1.size() / 8) * 8);
            s1 = s1.erase(0, (s1.size() / 8) * 8);
            while (s1.size() != 8) s1 = "0" + s1;
            s1 = "0" + s1;
            s1 = s3 + s1;
        }
        fout1 << decoding(chartree.top(), outDecomp(outcomp(s1)), setNewLines(file_name), spaces);
    }

    fin.close();
    fout1.close();


}
