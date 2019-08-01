#include <iostream>
#include <fstream>
#include <sstream>
#include <map>


class Inventory{
    std::string item;
    int qty;
    float funds;
    double change;


    public:
        bool enough_money;
        bool enough_qty;
        std::map<std::string, double> price;
        std::map<std::string, int> quantity;
        double budget;
        
        int num_sold;
        double total_value;

        
        
        Inventory(std::string inventory_fname);
        void Print();
        int AttemptExport(std::string item_, int qty_, float funds_);
        int SummarizeTransaction();
        int TotalStock();
        double Value();

};