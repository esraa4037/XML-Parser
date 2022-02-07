#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H
#include <string>
#include <list>
#include <vector>
using namespace std;
void convert_to_json(std::string path, std::string new_path);

string removeSpacesN(string line);
vector<string> xmlToVecN(string str);
class attribute{
    public:
        string key="";
        string value="";
};

class node{
public:
        string tag;
        string code;
        node* last = nullptr;
        std::list<attribute> attribut;
        std::list<node*>nodePtrList;
        bool isDuplicated=0;
        bool noAttributes();
        int parents_number();
};

bool noAttributes();
int parents_number();
string tag_print(string str);
int attribute_check(string s);
vector<string> attribute_print(string str, int index);
int duplication_check(node *child);
node* tree_creator(vector<string> strVec, int size);
string json_print(node* root);
string iteration(node* root, string& result);
void convert_to_json(string path, string new_path);

#endif // JSONCONVERTER_H
