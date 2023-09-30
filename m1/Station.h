#pragma once
#include <iostream>

namespace sdds{
    class Station{
        //remember that class variables are static while instance variables are 
        //available for every single instance of the objects to be used and changed accordingly
        int stationID;
        std::string itemName;
        std::string desc;
        size_t serial;
        size_t numInStock;
        
        //class variables
        static size_t m_widthfield;
        static int id_generator;
    public:
        Station(const std::string record);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity();
        void updateQuantity();
        void display(std::ostream& os, bool full) const;

    };
}