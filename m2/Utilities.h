#pragma once
#include <iostream>

namespace sdds{
    class Utilities{
        size_t m_widthField = 1;
        static char m_delimiter; //if the function is static, the member has to be static too?
    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

        static void setDelimiter(char newDelimiter);
        static char getDelimiter(){
            return m_delimiter;
        }
    };
}
