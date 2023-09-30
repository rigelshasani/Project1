#pragma once
#include <iostream>

namespace sdds{
    class Station{
    private:
        int id;
        std::string name;
        std::string description;
        size_t serial;
        size_t items;
        static size_t m_widthField;
        static int id_generator;

    public:
        Station(const std::string& record);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}