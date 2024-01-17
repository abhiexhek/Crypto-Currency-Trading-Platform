//
//  MerkelMain.hpp
//  CryptoPlatform
//
//  Created by Ankit Subedi on 04/01/2024.
//

#ifndef MerkelMain_h
#define MerkelMain_h


#pragma once
#include <stdio.h>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include <vector>
class MerkelMain
{
public:
    MerkelMain() = default;
    /** Call this to start the sim */
    void init();
    private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);
    
    std::string currentTime;
    
    OrderBook orderBook{"/Users/ankitsubedi/Desktop/Building Crypotcurrency Platform/CryptoPlatform/CryptoPlatform/crypto.csv"};

    Wallet wallet;
};
#endif /* MerkelMain_hpp */
