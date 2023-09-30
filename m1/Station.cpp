#include "Station.h"
#include "Utilities.h"
#include "Station.h"
#include <iomanip>
#include <iostream>
using namespace std;
namespace sdds{
    size_t Station::m_widthfield = 0;
    int Station::id_generator = 0;

    Station::Station(const std::string record){
        Utilities util1;
        size_t pos = 0;
        bool more = true;
        itemName = util1.extractToken(record, pos, more);
        //Question is: how do we extract a size_t from a string?
        //Answer is: via stoul()
        serial = stoul(util1.extractToken(record, pos, more));
        numInStock = stoul(util1.extractToken(record, pos, more));
        m_widthfield = max(m_widthfield, util1.getFieldWidth());
        desc = util1.extractToken(record, pos, more);
        stationID = ++id_generator;
  
    }
    const std::string& Station::getItemName() const{
        return itemName;
    }
    size_t Station::getNextSerialNumber(){
        return serial++;
    }
    size_t Station::getQuantity(){
        return numInStock;
    }
    void Station::updateQuantity(){
        if(numInStock != 0){
            numInStock-=1;
        }
    }
    void Station::display(std::ostream& os, bool full) const{
        os << right << setfill('0') <<setw(3) << stationID << " | " 
            << left  << setfill(' ') <<setw(m_widthfield) << itemName << " | " 
            << right << setfill('0') <<setw(6) << serial << " | ";
        if(full){

            os <<std::fixed << std::setw(4) << std::setfill(' ') << right 
               << numInStock<< " | " << desc;
        }  
        os << endl;
    }
}