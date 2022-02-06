#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
using namespace std;


string vec_to_str(vector<char> v){
    string s = "";
    for(char c: v){
        s += c;
    }
    return s;
}

vector<string> parse_line(string s){
    vector<string> data;
    int i = 0;
    vector<char> lex;

    while(s[i] != '\0'){
        if(s[i] == '<'){
            // inner text
            if(!lex.empty()){
                data.push_back(vec_to_str(lex));
                lex.clear();
            }

            // closing tag
            if(s[i+1] == '/'){
                while(1){
                    lex.push_back(s[i++]);
                    if(s[i] == '>'){
                        lex.push_back(s[i++]);
                        break;
                    }
                }
                data.push_back(vec_to_str(lex));
                lex.clear();
                continue;
            } else {
                // else means openning tag
                while(1){
                    lex.push_back(s[i++]);
                    if(s[i] == '>'){
                        lex.push_back(s[i++]);
                        break;
                    }
                }
                data.push_back(vec_to_str(lex));
                lex.clear();
                continue;
            }


        }else {
            lex.push_back(s[i++]);
        }
    }

return data;
}

string remove_Space_from_begin_and_end(string s){
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

string ignore_all_spaces(string s){
    string c = "";
    for(int i = 0; i < s.length(); i++){
        if(s[i] != ' ' && s[i] != '\t'){
            c = c + s[i];
        }
    }
    return c;
}

bool is_data(string s) {
    return (s[0] != '<');
}

bool is_version(string s){
    string version = ignore_all_spaces(s);
    string version1 = ignore_all_spaces("<?xml version=\"1.0\"?>");
    string version11 = ignore_all_spaces("<?xml version=\"1.1\"?>");
    if(version == version1 || version == version11){
        return true;
    }
    return false;
}

bool correct_version(string s){
    int pos = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '\"'){
            pos = i;
            break;
        }
    }
    if(s[pos+1] == '1' && s[pos+2] == '.' && s[pos+3] == '0' && s[pos+4] == '\"'){
        return true;
    }
    if(s[pos+1] == '1' && s[pos+2] == '.' && s[pos+3] == '1' && s[pos+4] == '"'){
        return true;
    }
    return false;
}

bool is_opening(string s){
    string m = remove_Space_from_begin_and_end(s);
    if(s == "<users>" || s == "<user>") return true;
    if(s == "<id>" || s == "<name>") return true;
    if(s == "<posts>" || s == "<post>") return true;
    if(s == "<body>") return true;
    if(s == "<topics>" || s == "<topic>") return true;
    if(s == "<followers>" || s == "<follower>") return true;

    return false;
}

bool is_closing(string s){
    string m = remove_Space_from_begin_and_end(s);
    if(s == "</users>" || s == "</user>") return true;
    if(s == "</id>" || s == "</name>") return true;
    if(s == "</posts>" || s == "</post>") return true;
    if(s == "</body>") return true;
    if(s == "</topics>" || s == "</topic>") return true;
    if(s == "</followers>" || s == "</follower>") return true;

    return false;
}

bool is_comment(string s) {
    if (s.length() < 7) return false;
    if(s[0] == '<' && s[1] == '!' && s[2] == '-'
    && s[3] == '-' && s[s.length()-1] == '>'
    && s[s.length()-2] == '-' && s[s.length()-3] == '-'){
    return true; }
    return false;
}

bool must_be_closed_imidiately(string s){
    if(s == "<id>" || s == "<name>") return true;
    if(s == "<body>" || s == "<topic>") return true;
    return false;
}

int get_type(string s){
    if(is_version(s)){
        if(correct_version(s)) return 1; //"correct version";
        else return 2; //"incorrect version";
    }else if(is_data(s)) return 3; // inner data
    else if(is_opening(s)) return 4; // openning tag
    else if(is_closing(s)) return 5; // closing tag
    else if(is_comment(s)) return 6; // comment

    return -1; //"incorrect tag";
}

bool is_more_than_one_tag(string s){
    s = remove_Space_from_begin_and_end(s);
    int tags = 0;
    for(int i = 0; i < s.length(); i++){
        if (s[i] == '<'){
            tags++;
            if(tags > 1){
                return true;
            }
            if(s[0] != '<' && tags >= 1){
                return true;
            }
        }
        if(s[i] == '>' && s[i+1] != '\0'){
            return true;
        }
    }

    return false;
}

bool balanced(string open, string close) {
    open = open.substr(1,open.length()-2);
    close = close.substr(2,close.length()-3);
    return (open == close);
}


void fill_stack_and_vec(int current_line ,string line,
                        vector<int> &errored_lines,
                        stack<string> &tags,
                        int first_non_empty_line){

    int type = get_type(line);
        switch(type){
            case 1: if(first_non_empty_line == current_line){
                        break;
                    } else {
                    errored_lines.push_back(current_line);
                    }
                    break;
            case 2: errored_lines.push_back(current_line);
                    break;
            case 3: break;
            case 4: if(!tags.empty()){
                        if(must_be_closed_imidiately(tags.top())){
                            errored_lines.push_back(current_line-1);
                            tags.pop();
                        }
                    }
                    tags.push(line);
                    break;
            case 5: if(!tags.empty()){
                        if(balanced(tags.top(), line)){
                            tags.pop();
                        } else {
                            if(must_be_closed_imidiately(tags.top())){
                                errored_lines.push_back(current_line-1);
                                tags.pop();
                                if(balanced(tags.top(), line)){
                                    tags.pop();
                                } else {
                                    tags.push(line);
                                    errored_lines.push_back(current_line);
                                    }
                            } else{
                                errored_lines.push_back(current_line);
                            }

                        }
                    } else {
                        tags.push(line);
                        errored_lines.push_back(current_line);
                    }
                    break;
            case 6: break;
            default: errored_lines.push_back(current_line);
                     break;
        }

}


vector<int> get_errored_lines(string user_file_path){
    ifstream file;
    file.open(user_file_path);

    stack<string> tags;
    string line;
    int type, current_line = 0;
    vector<int> errored_lines;

    if(file.is_open()){
        ///////// get the first non-empty line ///////////////
        getline(file, line);
        current_line++;
        while(line == ""){
            getline(file, line);
            current_line++;
        }
        int first_non_empty_line = current_line;
        //////////////////////////////////////////////////////
        do{
            line = remove_Space_from_begin_and_end(line);
            if(line != ""){
                //check if line contains more than one tag.
                if(is_more_than_one_tag(line)){
                    //cout << "more than one tag" << endl;
                    vector<string> data = parse_line(line);
                    for(string d : data){
                        fill_stack_and_vec(current_line ,d, errored_lines,
                                            tags, first_non_empty_line);
                    }

                } else {
                    //cout << "just one tag" << endl;
                    fill_stack_and_vec(current_line ,line, errored_lines,
                                        tags, first_non_empty_line);
                }
            }
            current_line++;
        } while(getline(file, line));
    }
    file.close();
    return errored_lines;
}


bool is_valid(string file_name){
    vector<int> errored_lines = get_errored_lines(file_name);
    if(errored_lines.empty()){
        return true;
    }
    return false;
}

string get_closing(string tag_name){
    return "</" + tag_name.substr(1,tag_name.length());
}


 void fill_correction_vec(int current_line ,string line,
                        stack<string> &tags, vector<vector<string>> &vec_of_replacements,
                        int first_non_empty_line){

    // first contains the tag shod be replaced
    // second element contains the correction
    // third element contains the line index
    vector<string> v;

    string correct;
    int type = get_type(line);
        switch(type){
            case 1: if(first_non_empty_line == current_line){
                        break;
                    } else {
                    // errored_lines.push_back(current_line);
                    v.clear();
                    v.push_back(line);
                    v.push_back("");
                    v.push_back(to_string(current_line));
                    v.push_back("override");
                    vec_of_replacements.push_back(v);
                    }
                    break;
            case 2:
            //      errored_lines.push_back(current_line);
                    v.clear();
                    v.push_back(line);
                    v.push_back("<?xml version=\"1.0\"?>");
                    v.push_back(to_string(current_line));
                    v.push_back("override");
                    vec_of_replacements.push_back(v);
                    break;
            case 3: if(tags.empty()){
                        v.clear();
                        v.push_back(line);
                        v.push_back("");
                        v.push_back(to_string(current_line));
                        v.push_back("override");
                        vec_of_replacements.push_back(v);
                     }
                    break;
            case 4: if(!tags.empty()){
                        if(must_be_closed_imidiately(tags.top())){
                            v.clear();
                            v.push_back(line);
                            v.push_back(get_closing(tags.top()));
                            v.push_back(to_string(current_line-1));
                            v.push_back("append");
                            vec_of_replacements.push_back(v);
                            tags.pop();

                        } else if (line == tags.top()){
                            v.clear();
                            v.push_back(line);
                            v.push_back(get_closing(tags.top()));
                            v.push_back(to_string(current_line-1));
                            v.push_back("append");
                            vec_of_replacements.push_back(v);
                            tags.pop();
                        }
                    }
                    tags.push(line);

                    break;
            case 5: if(!tags.empty()){
                        if(balanced(tags.top(), line)){
                            tags.pop();
                        } else {
                            if(must_be_closed_imidiately(tags.top())){
                                // errored_lines.push_back(current_line-1);
                                v.clear();
                                v.push_back(line);
                                v.push_back(get_closing(tags.top()));
                                v.push_back(to_string(current_line-1));
                                v.push_back("append");
                                vec_of_replacements.push_back(v);
                                tags.pop();
                                if(balanced(tags.top(), line)){
                                    tags.pop();
                                } else {
                                    tags.push(line);
                                    // errored_lines.push_back(current_line);
                                    v.clear();
                                    v.push_back(line);
                                    v.push_back("");
                                    v.push_back(to_string(current_line));
                                    v.push_back("override");
                                    vec_of_replacements.push_back(v);
                                    }
                            } else{

                                    string temp = tags.top();
                                    tags.pop();
                                    if(balanced(tags.top(), line)){
                                        tags.pop();
                                        v.clear();
                                        v.push_back(line);
                                        v.push_back(get_closing(temp));
                                        v.push_back(to_string(current_line-1));
                                        v.push_back("append");
                                        vec_of_replacements.push_back(v);

                                    } else {
                                        tags.push(temp);
                                        v.clear();
                                        v.push_back(line);
                                        v.push_back("");
                                        v.push_back(to_string(current_line));
                                        v.push_back("override");
                                        vec_of_replacements.push_back(v);
                                    }
                            }

                        }
                    } else {
                        v.clear();
                        v.push_back(line);
                        v.push_back("");
                        v.push_back(to_string(current_line));
                        v.push_back("override");
                        vec_of_replacements.push_back(v);
                    }
                    break;
            case 6: break;
            default:

                        v.clear();
                        v.push_back(line);
                        v.push_back(get_closing(tags.top()));
                        v.push_back(to_string(current_line));
                        v.push_back("replace");
                        vec_of_replacements.push_back(v);

                     tags.pop();

                     break;
        }

}


vector<vector<string>> get_correction(string file_path){
    ifstream file;
    file.open(file_path);


    stack<string> tags;
    string line;
    int type, current_line = 0;
    vector<vector<string>> vec_of_replacements;
    // vector<int> errored_lines;

    ///////// get the first non-empty line ///////////////
    getline(file, line);
    current_line++;
    while(line == ""){
        getline(file, line);
        current_line++;
    }
    int first_non_empty_line = current_line;
    //////////////////////////////////////////////////////
    do{
        line = remove_Space_from_begin_and_end(line);
        if(line != ""){
            //check if line contains more than one tag.
            if(is_more_than_one_tag(line)){
                //cout << "more than one tag" << endl;
                vector<string> data = parse_line(line);
                for(string d : data){
                    fill_correction_vec(current_line ,d, tags,
                                        vec_of_replacements, first_non_empty_line);
                }

            } else {
                //cout << "just one tag" << endl;
                fill_correction_vec(current_line ,line, tags,
                                    vec_of_replacements, first_non_empty_line);
            }
        }
        current_line++;
    } while(getline(file, line));

    file.close();
    return vec_of_replacements;
}


void create_correct_xml(string file_name,string new_file_name) {
    vector<vector<string> > v = get_correction(file_name);
    ifstream is;
    is.open(file_name);

    ofstream ofs;
    ofs.open(new_file_name, ofstream::out);

    string line;
    int line_index = 1;
    getline(is, line);
    if(is.is_open() and ofs.is_open()) {
        for(size_t i = 0; i < v.size(); i++){
            while(stoi(v[i][2]) != line_index){
                ofs << line << endl;
                getline(is, line);
                line_index++;
            }
            if(v[i][3] == "replace"){

                ////////////////////////////////////
                string error = v[i][0];
                string correct = v[i][1];
                size_t pos = line.find(error); // pos of the error tag
                line.replace(pos, error.length(), "");
                line.replace(pos, correct.length(), correct);
                ///////////////////////////////////
                ofs << line << endl;
                getline(is, line);
                line_index++;
            } else if(v[i][3] == "append"){
                ofs << line + v[i][1] << endl;
                getline(is, line);
                line_index++;
            } else if(v[i][3] == "override"){
                ofs << "" << endl; // clear the line
                getline(is, line);
                line_index++;
            }
        }
        do {
            ofs << line << endl;
        } while(getline(is, line));
    }
    ofs.close();
    is.close();

}

