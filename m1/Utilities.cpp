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
    return str.substr(beg, end-beg+1);
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
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
    if(str[next_pos] == m_delimiter){
        throw("This position contains a Delimiter!");
    }
    if (next_pos >= str.length())
    {
        // Set 'more' to false if 'next_pos' is beyond the input string length
        more = false;
        return "";
    }
    cout << "Next-pos: " << next_pos ;
    int remaining = str.length() - next_pos;
    std::string token2 = str.substr(next_pos, remaining);
    stringstream s(token2);   //convert a string to a stream
    std::string token;          
    std::getline(s, token, m_delimiter);
    cout << "Token at next position is: " << token[next_pos] << endl;
    if(token==""){
        more = false;
    }
    else{
        more = true;
    }
    if(token[next_pos] > token.length()){
        throw("token has ended");
    }
    cout << "Token at next position is: " << token[next_pos] << endl;
    if(token[next_pos] == m_delimiter){
        throw("This position contains a Delimiter!");
    }
    next_pos += token.length()+1;
    cout << "Token at next position is: " << token[next_pos] << endl;

    return trim(token);
}

