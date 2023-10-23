#include "Utilities.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
using namespace sdds;

static std::string trim(const std::string& str){
    if(str.length() == 0){
        return "";
    }
    size_t beg, end;
    for(beg=0; str[beg]== ' ' && beg < str.length(); beg++);
    for(end=str.length()-1; str[end]==' ' && end > 0; end--);
    string finalstring = str.substr(beg, end-beg+1);
    return finalstring;
}

char Utilities::m_delimiter;
void Utilities::setDelimiter(char newDelimiter){
            m_delimiter = newDelimiter;
        }
void Utilities::setFieldWidth(size_t newWidth){
    m_widthField = newWidth;
}
size_t Utilities::getFieldWidth() const{
    return m_widthField;
}
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
    // cout << "String is: " << str << endl;
    // cout << "Next pos is: " << next_pos << endl;
    if (next_pos >= str.length()) {
        more = false;
        throw std::runtime_error("Position out of bounds");
    }

    size_t delimiterPos = str.find(m_delimiter, next_pos);
    //cout << "-------TEST 1----------" << endl;
    if (delimiterPos == std::string::npos) {
        delimiterPos = str.length();
        more = false;
    } else {
        more = true;
    }
    //cout << "-------TEST 2----------" << endl;
    if (delimiterPos == next_pos) {
        // Skip tokens consisting solely of the delimiter
        next_pos++;
        return extractToken(str, next_pos, more); // Recursively move to the next token
    }
    //cout << "-------TEST 3----------" << endl;
    std::string token = str.substr(next_pos, delimiterPos - next_pos);
    if(m_delimiter == token[0]){
        throw std::runtime_error("Delimiter is the only left character");
    }
    next_pos = delimiterPos + 1;
    m_widthField = std::max(m_widthField, token.length());
    //cout << "-------TEST 4----------" << endl;
    //cout << "Token is: " << token << endl;
    //cout << "Next pos is: " << next_pos << endl;

    return trim(token);
}

