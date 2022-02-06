#ifndef TEXTPAGE_H
#define TEXTPAGE_H
#include <fstream>
#include <iostream>
using namespace std;

class TextPage {
    public:
        string text;
        TextPage(string path) {

            ifstream input_file(path);
            if (!input_file.is_open()) {
                cerr << "Could not open the file - '"
                    << path << "'" << endl;
                exit(EXIT_FAILURE);
            }
            this->text = string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
            input_file.close();
        }
};

#endif
