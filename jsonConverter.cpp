#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;


void xml2json (vector<string> s, string new_file_name){
    ofstream ofs;
    ofs.open(new_file_name, ofstream::out);
    if(ofs.is_open()){
    for(size_t i=0;i<s.size();i++){

    if(s[i]=="users" && s[i+1] =="user"){
        // cout<<'{'<<endl<<"  "<<"\""<<"users"<<"\""<<":"<<'['<<endl;
        ofs << "{" << endl << "  " <<"\""<<"users"<<"\""<<":"<<'['<<endl;
    }

    if(s[i]=="user"&&s[i+1] =="users"){
        // cout<<"      "<<'}'<<endl<<"    "<<']'<<endl<<'}'<<endl;;
        ofs<<"      "<<'}'<<endl<<"    "<<']'<<endl<<'}'<<endl;;
    }
    if(s[i]=="user"&&s[i+1] =="user"){
        // cout<<"      "<<'}'<<','<<endl;
        ofs<<"      "<<'}'<<','<<endl;
    }
    if(s[i]=="user"&&s[i+1]=="id"){
        //   cout<<"     "<<'{'<<endl;
          ofs<<"     "<<'{'<<endl;

    }

      if((s[i]=="id")  &&(s[i-1]== "user")){
            // cout<<"        "<<"\""<<"id"<<"\""<<":"<<"\""<<s[i+1]<<"\"";
            ofs<<"        "<<"\""<<"id"<<"\""<<":"<<"\""<<s[i+1]<<"\"";
        }
      if((s[i]=="id") &&(s[i-1]== "follower")){
            // cout<<"            "<<"\""<<"id"<<"\""<<":"<<"\""<<s[i+1]<<"\"";
            ofs<<"            "<<"\""<<"id"<<"\""<<":"<<"\""<<s[i+1]<<"\"";
        }
       if((s[i]=="id") &&(s[i+1]== "name")){
            // cout<<','<<endl;
            ofs<<','<<endl;
        }
       if((s[i]=="id") &&(s[i+1]== "follower")){
            // cout<<endl;
            ofs<<endl;
        }





    if(s[i]=="name" ){
         if(s[i+1] !="posts"){
            // cout<<"        "<<"\""<<"name"<<"\""<<':'<<"\""<<s[i+1]<<" ";
            ofs<<"        "<<"\""<<"name"<<"\""<<':'<<"\""<<s[i+1]<<" ";
            if(s[i+2]!="name"){
                // cout<<s[i+2]<<"\""<<','<<endl;
                ofs<<s[i+2]<<"\""<<','<<endl;
            }
         }


    }
    if(s[i]=="posts" ){
         if(s[i+1] !="followers"){
            // cout<<"        "<<"\""<<"posts"<<"\""<<':'<<'['<<endl;
            ofs<<"        "<<"\""<<"posts"<<"\""<<':'<<'['<<endl;
    }
         if(s[i+1]=="followers"){
            //  cout<<"          "<<']'<<','<<endl;
             ofs<<"          "<<']'<<','<<endl;
         }

    }

    if(s[i]=="followers"){
        if(s[i+1]=="follower"){
        //    cout<<"        "<<"\""<<"followers"<<"\""<<':'<<'['<<endl;
           ofs<<"        "<<"\""<<"followers"<<"\""<<':'<<'['<<endl;
         }
        if(s[i+1]!="follower"){

                // cout<<"        "<<']'<<endl;
                ofs<<"        "<<']'<<endl;
        }
    }
    if(s[i]=="topics"){
        if(s[i+1]=="topic"){
            // cout<<"            "<<"\""<<"topics"<<"\""<<':'<<'['<<endl;
            ofs<<"            "<<"\""<<"topics"<<"\""<<':'<<'['<<endl;
         }
        if(s[i+1]!="topic"){
        //    cout<<"            "<<']'<<endl;
           ofs<<"            "<<']'<<endl;
         }
    }

    if(s[i]=="follower"){
        if(s[i+1]=="id"){
            // cout<<"          "<<'{'<<endl;
            ofs<<"          "<<'{'<<endl;
             }
        if(s[i+1]=="followers"){
            // cout<<"          "<<'}'<<endl;
            ofs<<"          "<<'}'<<endl;
        }
        if(s[i+1]=="follower"){
            // cout<<"          "<<'}'<<','<<endl;
            ofs<<"          "<<'}'<<','<<endl;
        }
    }
    if((s[i]=="body")&&(s[i+1] == "topics")){
            //  cout<<"\""<<','<<endl;
             ofs<<"\""<<','<<endl;
          }
    if((s[i]=="body")&&(s[i+1]!="topics")){
        //   cout<<"            "<<"\""<<"body"<<"\""<<':'<<"\"";
          ofs<<"            "<<"\""<<"body"<<"\""<<':'<<"\"";
          for(;s[i+1]!="body";i++){

             if(s[i+2] != "topics"){
            //   cout<<s[i+1]<<' ';
              ofs<<s[i+1]<<' ';
              }


          }}

    if((s[i]=="topic")&&(s[i+1] == "topics")){
        //   cout<<endl;
          ofs<<endl;
          }
    if((s[i]=="topic")&& (s[i+1] != "topic")&& (s[i+1] != "topics")){
        //   cout<<"              "<<"\""<<s[i+1]<<"\"";
          ofs<<"              "<<"\""<<s[i+1]<<"\"";
          }
    if((s[i]=="topic")&&(s[i+1] == "topic")){
        //   cout<<','<<endl;
          ofs<<','<<endl;
          }

    if((s[i]=="post")&&(s[i+1]=="body")){
        // cout<<"          "<<'{'<<endl;
        ofs<<"          "<<'{'<<endl;
    }
    if((s[i]=="post")&&(s[i+1]=="post")){
        // cout<<"            "<<'}'<<','<<endl;
        ofs<<"            "<<'}'<<','<<endl;
    }
    if((s[i]=="post")&&(s[i+1]=="posts")){
        // cout<<"            "<<'}'<<endl;
        ofs<<"            "<<'}'<<endl;
     }


    }

    } else {
        // cout << "can't open the file." << endl;
        ofs << "can't open the file." << endl;
    }
    ofs.close();
}

vector<string> removeDupWord(string str)
{   vector<string> s;
    string word = "";
    for (auto x : str)
    {
        if ( x ==' ' || x=='<' || x=='>' || x=='/')
        {
           if(word !=""){s.push_back(word);}
           word = "";
        }
        else {
            word = word + x;
        }
    }
    return s;
}

void convert_to_json(string path, string new_path){
    ifstream ifs;
    ifs.open(path);

    vector<string> v;
    string line="", str="";

   if(ifs.is_open()){
//for(int i = 0; i < 1000; i++){
//    getline(ifs, line);
//    str += line;
//}
    while(getline(ifs, line)){
        str += line;
    }
    v = removeDupWord(str);
    xml2json(v, new_path);
    } else {
        //cout << "Can't open the file." << endl;
    }
    ifs.close();
}
