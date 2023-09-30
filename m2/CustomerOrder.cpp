#include <iostream>
#include <vector>
#include <iomanip>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

using namespace std;
using namespace sdds;

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder(){
    m_name = "";
    m_product = "";
    m_cntItem = 0;
    m_lstItem = nullptr;
    //item1//how do i initialize a object/class?
    m_widthField = 0;
    item1.m_itemName = "";
}
CustomerOrder::CustomerOrder(const std::string& reference){
    Utilities util1;
    size_t next = 0;
    bool r = true;
    m_name = util1.extractToken(reference, next, r);
    m_product = util1.extractToken(reference, next, r);

    vector<string> temp;
    while(r == true){
        temp.push_back(util1.extractToken(reference, next, r));
    }
    //testing the items
    cout << endl;
    for(size_t i=0;i<temp.size();i++){
        cout <<"|TEST-----------" << temp[i] << "|" << endl;
    }
    cout << endl;
    //end test
    m_widthField = std::max(m_widthField, util1.getFieldWidth());
    //get the item count
    m_cntItem = temp.size();
    //instantiate the array of pointers
    m_lstItem = new Item*[m_cntItem];
    //populate it
    for(size_t i = 0;i<m_cntItem;i++){
        //creates a item pointer called item
        //assigns to that, the address of a newly created..
        //Item object, which takes in a parameter...
        //temp[i], which is a string
        Item* item = new Item(temp[i]);
        m_lstItem[i] = item;
    }
    //alternatively
    //  m_lstItem = new Item*[temp.size()];
    //  std::copy(temp.begin(), temp.end(), m_lstItem);
    
}
//copy semantics
CustomerOrder::CustomerOrder(const CustomerOrder& order){
    cout << "TESTING exception" << endl;
    throw("exception"); 
}

//move semantics
CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept{
    cout << order.m_name;
    m_name    = std::move(order.m_name);
    cout << order.m_name;
    m_product = std::move(order.m_product);
    m_cntItem = order.m_cntItem;
    m_lstItem = order.m_lstItem;
    
    order.m_lstItem = nullptr;
    order.m_cntItem = 0;
}
void CustomerOrder::operator=(CustomerOrder&& order) noexcept{
    if(this != &order){
        cout << order.m_cntItem << "<- reference|this-> " << this->m_cntItem << endl;
        m_name = std::move(order.m_name);
        m_product = std::move(order.m_product);
        m_cntItem = order.m_cntItem;
        for(size_t i=0;i<m_cntItem;i++){
            m_lstItem[i] = std::move(order.m_lstItem[i]);
        }
    }
}
CustomerOrder::~CustomerOrder(){
    if(m_lstItem != nullptr){
        
        for(size_t i=0;i<m_cntItem;i++){
            delete m_lstItem[i];
        }
        
        
        delete[] m_lstItem;
    }
}

bool CustomerOrder::isOrderFilled() const{
    for(size_t i=0;i<m_cntItem;i++){
        if(m_lstItem[i]->m_isFilled == false){
            return false;
        }
    }
    return true;
}
bool CustomerOrder::isItemFilled(const std::string& itemName) const{
    for(size_t i=0;i<m_cntItem;i++){
    //for i in range of the item count
        if(itemName == m_lstItem[i]->m_itemName){
            //if itemName is the same as the itemname in the list
            if(m_lstItem[i]->m_isFilled == true){}
            //if that item is filled
            else{
                //if not return false;
                return false;
            }
        }
    }
    return true;
}
void CustomerOrder::fillItem(Station& station, std::ostream& os){
    for(size_t i=0;i<m_cntItem;i++){
        if(station.getItemName() == m_lstItem[i]->m_itemName && station.getQuantity() > 0){
            //fills the item
            m_lstItem[i]->m_isFilled = true;
            //descreases the quantity available in the station by 1
            station.updateQuantity();
            cout << "Filled NAME, PRODUCT " << 
            m_lstItem[i]->m_itemName << endl; 
        }
        else{
            cout << "Unable to fill NAME, PRODUCT " << m_lstItem[i]->m_itemName << endl;
            //where is this being printed out on the output?
            //i cant check how the spelling works out

        }//end else

    }//end for loop

}//end fillitem function
void CustomerOrder::display(std::ostream& os) const {
    os << m_name << " - " << m_product << std::endl;

    for (size_t i = 0; i < m_cntItem; i++) {
        os << "[" << std::setw(6) << std::setfill('0') 
           << m_lstItem[i]->m_serialNumber << "] - "
           << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
    }
}