//Collision
//Elevate
//Ryan Fang
//Micro and micro economics Udemy
//International Economics
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
    m_widthField = 0;
    item1.m_itemName = "";
}
CustomerOrder::CustomerOrder(const std::string& reference){
    cout << reference << endl;
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
    // cout << endl;
    // for(size_t i=0;i<temp.size();i++){
    //     cout <<"|TEST-----------" << temp[i] << "|" << endl;
    // }
    // cout << endl;
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
        //cout << item->m_serialNumber << endl;
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
    m_name    = std::move(order.m_name);
    cout << order.m_name;
    m_product = std::move(order.m_product);
    m_cntItem = order.m_cntItem;
    //shouldnt this loop through the list items and assign them individually
    m_lstItem = order.m_lstItem;
    
    order.m_lstItem = nullptr;
    order.m_cntItem = 0;
}
void CustomerOrder::operator=(CustomerOrder&& order) noexcept{
    if(this != &order){
        //cout << order.m_cntItem << "<- reference|this-> " << this->m_cntItem << endl;
        //cout << this->m_name << endl;
        //cout << order.m_lstItem[0] << "<- reference|this-> " << this->m_lstItem[0] << endl;

        m_name = std::move(order.m_name);
        //cout << "Finished move name" << endl;
        m_product = std::move(order.m_product);
        //cout << "Finished move product" << endl;
        m_cntItem = order.m_cntItem;
        //cout << "Finished move itm count" << endl;
        cout << "Item count is: " << this->m_cntItem << endl;
        for(size_t i=0;i<this->m_cntItem;i++){
            m_lstItem[i] = std::move(order.m_lstItem[i]);
        }
        cout << "Finished move operation" << endl;
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
    cout << "Inside the item filler" << endl;
    for(size_t i=0;i<m_cntItem;i++){
        if(station.getItemName() == m_lstItem[i]->m_itemName && station.getQuantity() > 0){
            //fills the item
            //descreases the quantity available in the station by 1
            station.updateQuantity();
            cout << "Filled NAME, PRODUCT " << 
            m_lstItem[i]->m_itemName << endl; 
            m_lstItem[i]->m_isFilled = true;
            //m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
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
    cout << m_cntItem << endl;
    cout << m_lstItem[1]->m_serialNumber << endl;
    // for (size_t i = 0; i < m_cntItem; i++) {
    //     os << "[" << std::setw(6) << std::setfill('0') 
    //        << m_lstItem[i]->m_serialNumber << "] - "
    //        << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
    // }
}
