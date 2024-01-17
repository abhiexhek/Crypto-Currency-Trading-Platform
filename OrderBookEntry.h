//
//  OrderBookEntry.hpp
//  CryptoPlatform
//
//  Created by Ankit Subedi on 04/01/2024.
//

// #ifndef OrderBookEntry_hpp
// #define OrderBookEntry_hpp

#pragma once
#include <string>
#include <stdio.h>

enum class OrderBookType{bid, ask, unknown,asksale, bidsale};
class OrderBookEntry
{
    public:
    OrderBookEntry(std::string _timestamp,
                    std::string _product,
                    OrderBookType _orderType,
                    double _price,
                    double _amount,
                    std::string _username = "dataset");

   static OrderBookType stringToOrderBookType(std::string s);
   static bool compareByTimeStamp(OrderBookEntry& e1, OrderBookEntry& e2)
   {
    return e1.timestamp<e2.timestamp;
   }

   static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
   {
    return e1.price<e2.price;
   }

   static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
   {
    return e1.price>e2.price;
   }

        std::string timestamp;
        std::string product;
        OrderBookType orderType = OrderBookType::bid;
        double price;
        double amount;
        std::string username;
};


// #endif /* OrderBookEntry_hpp */
