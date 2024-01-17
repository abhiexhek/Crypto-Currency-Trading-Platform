//
//  OrderBook.hpp
//  CryptoPlatform
//
//  Created by Ankit Subedi on 1/7/24.
//
#pragma once
#ifndef OrderBook_h
#define OrderBook_h
#include "OrderBookEntry.h"
#include "CSVreader.h"
#include <stdio.h>

class OrderBook
{
public:
    /** construct, reading a csv data file*/
    OrderBook(std::string filename);
    /** return vector of all known products in the datasets*/
    std::vector<std::string>getKnownProducts();
    /** return vector  of Orders according to the sent filters*/
    std::vector<OrderBookEntry>getOrders(OrderBookType type,
                                        std::string product,
                                         std::string timestamp);
    
    /** return the earliest time in the orderbook*/
    std::string getEarliestTime();
    /** return the next time after earliest time sent in the orderbook
     * If there is no next time stam code wrap around and start form first*/
    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry& order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
    
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getLowPrice(std::vector<OrderBookEntry>& orders);
    
private:
    std::vector<OrderBookEntry> orders;
};

#endif /* OrderBook_hpp */
