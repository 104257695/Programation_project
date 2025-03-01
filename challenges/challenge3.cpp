#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>

void displayInventory(const std::map<std::string, int>& inventory) {
    std::cout << "Current Inventory:\n";
    for (const auto& item : inventory) {
        std::cout << item.first << ": " << item.second << " in stock\n";
    }
    std::cout << std::endl;
    
}
//Managing Products with std::map----------------
void add_new_pro(std::map<std::string, int> & inventory){
    std::string product;
    int quantity;
   
    std::cout << "New product to add: ";
    std::cin>> product;
    std::cout << "Quantity: ";
    std::cin>>quantity;

    inventory.insert({product, quantity});
    inventory[product]= quantity;
  
}
//------Tracking Unique Products with std::set---------
void categories(std::set<std::string>&  productCategories){
    std::string catg;
    std::cout << "New category to add: ";
    std::cin>> catg;
    productCategories.insert(catg);
}


//------------Processing Orders with std::queue--------------------
void CATGqueue(std::queue<std::string>& orders) {
    std::string order;

   
    std::cin.ignore();
    std::cout << "New order: ";
    std::getline(std::cin, order);

    if (!order.empty()) {
        orders.push(order);
    }
}
//Handling Restocks with std::stack
void procesing(std::stack<std::pair<std::string, int>> & restocks){
    std::string batch;
    int quant;

    std::cout << "Restocking to add: ";
    std::cin>> batch;
    std::cout << "Quantity: ";
    std::cin>>quant;

    restocks.push({batch,quant});
}
//----Storing Customer Purchases with std::vector-----------------------
void customer (std::vector<std::string> & customerCart) {
    std::string cart;

    std::cout << "Add customers cart: ";
    std::cin>> cart;

    customerCart.push_back(cart);

}

//---------------------------------------------------------
int main() {
    std::map<std::string, int> inventory;
    
    // Adding products
    inventory["Laptop"] = 5;
    inventory["Mouse"] = 20;
    inventory["Keyboard"] = 10;

    displayInventory(inventory);
    add_new_pro(inventory);
    displayInventory(inventory);

    //------Tracking Unique Products with std::set---------
      // Adding categories
    std::set<std::string> productCategories;

    productCategories.insert("Electronics");
    productCategories.insert("Accessories");
    productCategories.insert("Peripherals");

    std::cout << "Product Categories:\n";
    for (const auto& category : productCategories) {
        std::cout << "- " << category << "\n";
    }
    categories(productCategories);
    std::cout << "Updated Product Categories:\n";
    for (const auto& category : productCategories) {
        std::cout << "- " << category << "\n";
    }

//------------Processing Orders with std::queue--------------------
    std::queue<std::string> orders;

    // Adding orders
    orders.push("Order#1: Laptop");
    orders.push("Order#2: Mouse");
    orders.push("Order#3: Keyboard");

    // Processing orders
    CATGqueue(orders);
    while (!orders.empty()) {
        std::cout << "Processing " << orders.front() << std::endl;
        orders.pop();
    }
    
   
//----Handling Restocks with std::stack-----------
    std::stack<std::pair<std::string, int>> restocks;

    // Adding restock batches
    restocks.push({"Mouse", 10});
    restocks.push({"Laptop", 2});
    restocks.push({"Keyboard", 5});

    // Processing restocks
    procesing(restocks);

    while (!restocks.empty()) {
        auto item = restocks.top();
        std::cout << "Restocking " << item.second << " units of " << item.first << std::endl;
        restocks.pop();
    }    
    

//----Storing Customer Purchases with std::vector---------------------------------------------------------
    std::vector<std::string> customerCart;

    // Adding items to cart
    customerCart.push_back("Laptop");
    customerCart.push_back("Mouse");
    customerCart.push_back("Keyboard");

    std::cout << "Items in customer cart:\n";
    for (const auto& item : customerCart) {
        std::cout << "- " << item << "\n";
    }

    customer(customerCart);
    std::cout << "Items in new customer cart:\n";
    for (const auto& item : customerCart) {
        std::cout << "- " << item << "\n";
    }


    return 0;
}
//----------------------------------------
