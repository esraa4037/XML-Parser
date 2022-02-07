#ifndef VALIDATE_H
#define VALIDATE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

vector<string> lines(string path);
string vec_to_str(vector<char> v);
vector<string> parse_line(string s);

string remove_Space_from_begin_and_end(string s);

string ignore_all_spaces(string s);

bool is_data(string s) ;

bool is_version(string s);

bool correct_version(string s);

bool is_opening(string s);
bool is_closing(string s);

bool is_comment(string s) ;

bool must_be_closed_imidiately(string s);

int get_type(string s);

bool is_more_than_one_tag(string s);

bool balanced(string open, string close) ;
void fill_stack_and_vec(int current_line ,string line,
                        vector<int> &errored_lines,
                        stack<string> &tags,
                        int first_non_empty_line);


vector<int> get_errored_lines(string user_file_path);

bool is_valid(string file_name);

string get_closing(string tag_name);

 void fill_correction_vec(int current_line ,string line,
                        stack<string> &tags, vector<vector<string>> &vec_of_replacements,
                        int first_non_empty_line);

vector<vector<string>> get_correction(string file_path);


void create_correct_xml(string file_name,string new_file_name);

vector<vector<string>> get_correction(string file_path);


#endif // VALIDATE_H
