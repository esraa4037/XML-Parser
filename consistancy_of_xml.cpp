#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

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

// bool correct_data(string s){
//     for (int i = 0; i < s.length(); i++){
//         if(s[i] == '<') return false;
//     }
//     return true;
// }

// bool is_opening(string s){
//     string m = remove_Space_from_begin_and_end(s);
//     if(m[0] == '<' && m[1] != '/'){
//             return true;
//         }
//     return false;
// }

// bool correct_tag(string s){
//     string m = remove_Space_from_begin_and_end(s);
//     int no_of_spaces = 0;
//     for(int i = 0; i < m.length(); i++){
//         if(m[i] == ' '){no_of_spaces++;}
//     }
//     if(no_of_spaces == 0 && m[0] == '<' && m[m.length()-1] == '>') {
//         return true;
//     }
//     return false;
// }

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

bool must_be_closed_imidiately(string s){
    if(s == "<id>" || s == "<name>") return true;
    if(s == "<body>" || s == "<topic>") return true;
    return false;
}

int get_type(string s){
    if(is_version(s)){
        if(correct_version(s)) return 1; //"correct version";
        else return 2; //"incorrect version";
    }else if(is_data(s)) return 3;        
    else if(is_opening(s)) return 4;
    else if(is_closing(s)) return 5; 
   
    return -1; //"incorrect tag";
}

bool is_more_than_one_tag(string s){
    if(s[0] != '<') return false; // then it't a data
    
    int pos = -1;
    for(int i = 0; i < s.length(); i++){
        if (s[i] == '>'){
            pos = i;
            break;
        }
    }
    if(pos == -1) return false;
    if(s[pos+1] != '\0') return true;
    return false;
}

vector<string> parse_line(string line){
    string s = remove_Space_from_begin_and_end(line);
    vector<string> data;
    string open, info, close;

    for(int i = 0; i < s.length(); i++){
        open+= s[i];
        if(s[i] == '>'){
            break;
        }
    }
    data.push_back(open);
    for(int i = open.length(); i < s.length(); i++){
        if(s[i] == '<'){
            break;
        }
        info+= s[i];
        
    }
    data.push_back(info);
    for(int i = open.length() + info.length(); i < s.length(); i++){
        close+= s[i];
    }
    if(close.length()>0)
        data.push_back(close);
return data;
}

bool balanced(string open, string close) {
    open = open.substr(1,open.length()-2);
    close = close.substr(2,close.length()-3);
    return (open == close);
}

bool is_valid(vector<int> errored_lines){
    if(errored_lines.empty()){
        return true;
    }
    return false;
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

            default: errored_lines.push_back(current_line);
                     break;
        }
        
}

vector<int> get_errored_lines(ifstream &file, stack<string> &tags){
    string line;
    int type, current_line = 0;
    vector<int> errored_lines;

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
    
    return errored_lines;
}


int main()
{
	string line, user_file_path;
    stack<string> tags;
    ifstream file;
    cout << "please enter the file path." << endl;
    cout << "file path like E:\\cpp_projects\\files_in_cpp\\testError.txt" << endl;
    cin >> user_file_path;
    file.open(user_file_path);
    // file.open("E:\\cpp_projects\\files_in_cpp\\studentsINFO.txt");
	
    vector<int> data = get_errored_lines(file, tags);
    file.close();

    for(int s: data) {
        cout << s << endl;
    }

    if(is_valid(data)){
        cout << "xml file is valid." << endl;
        cout << "No errors were found." << endl;
    }

    return 0;
}
