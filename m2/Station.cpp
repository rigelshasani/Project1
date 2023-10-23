#include "Station.h"
#include "Utilities.h"
#include <iomanip>

namespace sdds{
    size_t Station::m_widthField = 0;
    int Station::id_generator = 0;
    Station::Station(const std::string& record){
        //std::cout << "Inside station constructor" << std::endl;
        //std::cout << record << std::endl;
        //brings in a record, then extracts
        Utilities util; 
        size_t pos = 0;
        std::string token;
        bool more;

        name = util.extractToken(record, pos, more);
        serial = std::stoul(util.extractToken(record, pos, more));
        //std::cout << "Record is: " << record << std::endl;
        items = std::stoul(util.extractToken(record, pos, more));
        m_widthField = std::max(m_widthField, util.getFieldWidth());
        description = util.extractToken(record, pos, more);
        id = ++id_generator;
        //std::cout << name<< " " << serial << " " << items << " "  << m_widthField << " " << description << std::endl;
    }

    const std::string& Station::getItemName() const{
        return name;
    }

    size_t Station::getNextSerialNumber(){
        return serial++;
    }

    size_t Station::getQuantity() const{
        return items;
    }
    
    void Station::updateQuantity(){
        items = (items==0) ? 0 : items-1;
    }

    void Station::display(std::ostream& os, bool full) const{
        os << std::fixed << std::setfill('0') << std::right << std::setw(3) << id << " | " 
           << std::setfill(' ') << std::left << std::setw(m_widthField) << name << "| " << 
            std::setw(6) << std::setfill('0') << std::right << serial << " | ";
        
        if(full){
            os << std::fixed << std::setw(4) << std::setfill(' ') << std::right 
               << items << " | " << description;
        }

        os << std::endl;
    }
}