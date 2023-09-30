#pragma once
#include "Station.h"
#include "Utilities.h"
#include <iostream>

namespace sdds{
    struct Item{
	        std::string m_itemName;
	        size_t m_serialNumber{0};
	        bool m_isFilled{false};
            Item(){}
	        Item(const std::string& src) : m_itemName(src) {};
            };
    class CustomerOrder{
        std::string m_name;
        std::string m_product; 
        size_t m_cntItem;
        Item** m_lstItem;
        Item item1;
        //static
        static size_t m_widthField;
    public:
        CustomerOrder();
        CustomerOrder(const std::string& reference);
        //copy semantics
        CustomerOrder(const CustomerOrder& order);
        void operator=(const CustomerOrder& org) = delete;

        //move semantics
        CustomerOrder(CustomerOrder&& order) noexcept;
        void operator=(CustomerOrder&& org) noexcept;
        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
    
    /*std::ostream& operator<<(std::ostream& os, const CustomerOrder& rhs){
        rhs.display(os);
    }
    CustomerOrder cust1;
    cust1.display(std::cout);
    cout << cust1;
    */
}