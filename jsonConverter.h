#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H
#include <string>
#include <vector>

void xml2json (std::vector<std::string> s, std::string new_file_name);
std::vector<std::string> removeDupWord(std::string str);
void convert_to_json(std::string path, std::string new_path);

#endif // JSONCONVERTER_H
