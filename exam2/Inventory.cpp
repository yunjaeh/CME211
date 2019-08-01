#include <iostream>
#include <fstream>
#include <string>
#include "Inventory.hpp"
// #include "CashRegister.hpp"


Inventory::Inventory(std::string inventory_fname){

    std::string each_line;
    std::ifstream f;
    std::string token;

    std::string temp_item;
    double temp_price;
    int temp_qty;
    budget=0.0;

    f.open(inventory_fname);

    // // f >> each_line;

    while(getline(f,each_line))
    {
        // std::cout << each_line << std::endl;
        std::istringstream ss(each_line);
        std::getline(ss,token,',');
        temp_item = token;
        std::getline(ss,token,',');
        temp_price = std::stod(token);
        std::getline(ss,token,',');
        temp_qty = std::stoi(token);
        // std::cout << temp_item << "," <<temp_price << ","<< temp_qty << std::endl;

        price[temp_item] = temp_price;
        quantity[temp_item] = temp_qty;
    }
        
    f.close();
}

void Inventory::Print(){
    
    for(auto item : price)
    {
        std::cout << item.first << std::endl;
        // std::cout.setf(std::ios::showpoint);
        // std::cout.precision(3);
        // std::cout << "  Price: " << price[item.first];
        // std::cout << ", Qty: " <<  quantity[item.first] << std::endl;
        std::cout << "  "<< price[item.first] <<", " <<quantity[item.first] << std::endl;
    }
}

int Inventory::AttemptExport(std::string item_, int qty_, float funds_){

    item = item_;
    qty = qty_;
    funds = funds_;

    // check item presents in the inventory
    auto iter = price.find(item);
    if(iter==price.end()){
        throw std::invalid_argument("Item does not present in the inventory");
    }
    // check given qty is negative or not
    if(qty < 0){
        throw std::invalid_argument("Negative quantity input");
    } 
    // check given fund is negative or not 
    if(funds < 0){
        throw std::invalid_argument("Negative money input");
    } 

    // we do have the item in the inventory and qty, funds are valid
    double total_price = price[item] * (double) qty;

    // case : not enough item available in the inventory
    
    // case : we have enough quantities of the item
    

    
    
    enough_qty = qty <= quantity[item];
    // std::cout << "enough_qty:"  << enough_qty <<std::endl;
    if(enough_qty)
    {   
        enough_money = total_price <= funds;
        // std::cout << "enough_money: "  << enough_money <<std::endl;
        if(enough_money){
            //enough money, enough qty
            num_sold = qty;
            total_value = total_price;

            change = funds - total_value;
            quantity[item] = quantity[item] - num_sold;
        } else {
            // not enough money, enough qty
            num_sold = int(funds / price[item]);
            total_value = price[item] * (double)num_sold;
            change = funds - total_value;
            quantity[item] = quantity[item] - num_sold;
        }
    } else {
        total_price = price[item] * (double) quantity[item];
        enough_money = total_price <= funds;
        // std::cout << "enough_money: "  << enough_money <<std::endl;
        if(enough_money){
            //enough money, not enough qty
            num_sold = quantity[item];
            total_value = total_price;

            change = funds - total_value;
            quantity[item] = quantity[item] - num_sold;
        } else {
            // not enough money, not enough qty
            num_sold = int(funds / price[item]);
            total_value = price[item] * (double)num_sold;
            change = funds - total_value;
            quantity[item] = quantity[item] - num_sold;
        }
    }

    return 1;
}

int Inventory::SummarizeTransaction(){
    std::cout <<"-----Receipts-----" << std::endl;
    std::cout <<"Item: "<< item << std::endl;
    std::cout <<"Given money: " << funds << std::endl;
    std::cout <<"Total number sold: " << num_sold << std::endl;
    std::cout <<"Total value sold: " << total_value << std::endl;
    std::cout <<"Change: " << change << std::endl;

    return 0;
}
int Inventory::TotalStock(){
    
    int num_items=0;
    for(auto item:quantity)
    {
        num_items += item.second;
    }
    return num_items;
}

double Inventory::Value(){

    double total_value=0;
    for(auto item:price)
    {
        total_value += price[item.first] * (double) quantity[item.first];
    }
    return total_value;
}
