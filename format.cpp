#include<iostream>
#include<string>
#include<stack>
#include<string>
#include<fstream>
#include <bits/stdc++.h>
using namespace std;

struct sp {
    string s1;
    int sep;
};


string aremove_Space(string s){
    if (s==""){return "";}
    int pos_begin = -1, pos_end;
    for(int i = 0; i < s.length(); i++){
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'){
            pos_begin = i;
            break;
        }
    }
    if(pos_begin == -1){
        return "";
    }
    for(int i = s.length() - 1; i > 0; i--){
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'){
            pos_end = i;
            break;
        }
    }
    s = s.substr(pos_begin, pos_end - pos_begin + 1);
    return s;
}

int findsm(string s) {
    size_t a = s.find('>');
    if (a + 1 != s.length())return 1;
    else return 0;
}
string printsp(int n, string st) {
    while (n != 0) {
        st += " ";
        n--;
    }
    return st;
}

void Formating(string file_name, string new_file_name) {
    bool text = false;
    string s,s1, st = "";
    sp a;
    int t = 0;
    stack<sp> spaces;
    ifstream fin;
    ofstream fout;
    fin.open(file_name, ios::in);
    fout.open(new_file_name, ios::out);
    if (fin.is_open() && fout.is_open()) {
        while (getline(fin, s1)) {
s=aremove_Space(s1);
            if (s[0] == '<') {
                if (s[1] == '/') {
                    fout << printsp(spaces.top().sep, st) << s << endl;
                    spaces.pop();

                }
                else {

                    if (!spaces.empty())t = spaces.top().sep + 4;
                    fout << printsp(t, st) << s << endl;
                    if (!findsm(s)) {
                        a.s1 = s;
                        a.sep = t;
                        spaces.push(a);
                    }

                }
            }
            else fout << printsp(spaces.top().sep+4, st) << s << endl;



        }
        fin.close();
        fout.close();

    }

}
