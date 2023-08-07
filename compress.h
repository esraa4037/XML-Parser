//made by alaa
#ifndef COMPRESS_H
#define COMPRESS_H

#include<string>
#include<queue>

using namespace std;

struct charnode ;
struct charmap ;
struct charVector ;
struct  charValue;
struct freqComp ;

void storevalues(charnode* chartree, charValue* a, string s);
void huffmanTree(priority_queue<charnode*, vector<charnode*>, freqComp>* chartree, charValue* cValue);
string decoding(charnode* chartree, string s, queue<string> newlines);
int BinaryToDecimal(string s, int i);
string outcomp(string s);
string outDecomp(string s);
charmap setCodes(string file_name);
queue<string> setNewLines(string file_name);
string remove_space(string s);
void Compressing(string file_name, string new_file_name);

void Decompress(string path, string newde_file_name);

int count_Space(string s);
string print_Space(int n);

#endif // COMPRESS_H
