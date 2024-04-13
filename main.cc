#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <cstring>
using namespace std;

namespace fs = filesystem;

string to_lower_case(const string& str) {
    string result;
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}

void splitWords(const string &line, vector<string> &words) {
    string word;
    for (char c : line) {
        if (isspace(c) || c == '-' || c == ',' || c == '.' || c == '/' || c == '!' || c == '?') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
}

int main(int argc, char *argv[]) {

    if(argc != 2) {
        cerr << "Please provide file name as argument" << endl;
        return 1;
    }

    string file_name = argv[1];
    fs::path curr_dir = fs::current_path();
    switch ( fs::path p{file_name}; fs::status(p).type() ) {
        case fs::file_type::not_found:
            cout << "dir: " << curr_dir << endl;
            for (const auto& it : fs::directory_iterator{curr_dir}) {
                cout << " - " << it.path() << endl;
            }
            break;
        case fs::file_type::regular:
            ifstream file (file_name);
            unsigned int line_count = 0;
            unsigned int char_count = 0;
            unsigned int word_count = 0;
            vector<string> words;
            for(string line; getline(file, line);) {
                line_count++;

                for(char c: line) {
                    if (!isspace(static_cast<unsigned char>(c))) {
                        char_count++;
                    }
                }
                splitWords(line, words);
                word_count += words.size();
            }
            file.close();

            cout << "liczba linijek: " << line_count << endl;
            cout << "liczba znaków: " << char_count << endl;
            cout << "liczba słów: " << word_count << endl;
            cout << endl;


            map <string, int > hashmap;
            for (string word: words) {
                string word_edited = to_lower_case(word);
                if (hashmap.find(word_edited) != hashmap.end()) {
                    hashmap[word_edited] += 1;
                } else {
                    hashmap.insert({ word_edited, 1});
                }
            }

            cout << "Słowa w kolejności alfabetycznej:" << endl;
            for(const auto& pair : hashmap) {
                cout << pair.first << " - " << pair.second << endl;
            }

            cout << endl;

            cout << "Słowa w kolejności według długości:" << endl;
            map<int, vector<string>> wordsByLength;
            for (const auto& pair : hashmap) {
                wordsByLength[pair.first.size()].push_back(pair.first);
            }
            for (const auto& entry : wordsByLength) {
                for (const auto& word : entry.second) {
                    cout << word << " - " << hashmap[word] << endl;
                }
            }
            break;
    }
    return 0;
}
