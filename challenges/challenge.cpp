#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <stack>


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
int main(){
    //----Handling Restocks with std::stack-----------
    std::stack<std::pair<std::string, int>> restocks;

    // Adding restock batches
    restocks.push({"Mouse", 10});
    restocks.push({"Laptop", 2});
    restocks.push({"Keyboard", 5});

    // Processing restocks
 
    while (!restocks.empty()) {
        auto item = restocks.top();
        std::cout << "Restocking " << item.second << " units of " << item.first << std::endl;
        restocks.pop();
    }    
    procesing(restocks);

    while (!restocks.empty()) {
        auto item = restocks.top();
        std::cout << "Restocking " << item.second << " units of " << item.first << std::endl;
        restocks.pop();
    }
}
