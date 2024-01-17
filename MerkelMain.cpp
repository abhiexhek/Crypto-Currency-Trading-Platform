//
//  MerkelMain.cpp
//  CryptoPlatform
//
//  Created by Ankit Subedi on 04/01/2024.
//

#include "MerkelMain.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVreader.h"
#include "Wallet.h"
/** your main function should call this */
void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}
/** load up some dummy data for now */
//void MerkelMain::loadOrderBook()
//{
//    orders = CSVreader::readCSV("/Users/ankitsubedi/Desktop/Building Crypotcurrency Platform/CryptoPlatform/CryptoPlatform/crypto.csv");
//
//}
void MerkelMain::printHelp()
{
    std::cout<<"Help -choose options from the menu"<<std::endl;
    std::cout<<"and follow the on screen instructions."<<std::endl;
}
void MerkelMain::printMarketStats()
{
    for (std::string const& p: orderBook.getKnownProducts())
    {
        std::cout<<"Product: "<<p<<std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                p, currentTime);
        std::vector<OrderBookEntry> bidSeen = orderBook.getOrders(OrderBookType::bid,
                                                                  p, currentTime);
        std::cout<<"Asks seen : "<<entries.size()<<std::endl;
        std::cout<<"Max ask: "<<OrderBook::getHighPrice(entries)<<std::endl;
        std::cout<<"Min ask : "<<OrderBook::getLowPrice(entries)<<std::endl;

    }
//    std::cout<<"OrderBook Contain  "<<orders.size() <<" entries"<<std::endl;
//    unsigned int bids = 0;
//    unsigned int asks = 0;
//    for (OrderBookEntry& e : orders)
//    {
//        if(e.orderType == OrderBookType::ask)
//            asks++;
//        if(e.orderType == OrderBookType::bid)
//            bids++;
//    }
//    std::cout<<"OrderBook Contain  "<<asks<<" ask and "<<bids<<" bids"<<std::endl;
}
void MerkelMain::enterAsk()
{
    std::cout<<"Make and ask - enter the amount: product, price, amount, eg ETH/BTC, 200, 0.5"<<std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVreader::tokenise(input, ',');
    if(tokens.size() != 3)
    {
        std::cout<<"MerkelMain::enterAsk Bad input!"<<input<<std::endl;
    }
    else
    {
        try
        {
        OrderBookEntry obe = CSVreader::stringsToOBE(currentTime,
                                    tokens[1],
                                    OrderBookType::ask,
                                    tokens[3],
                                    tokens[4]);
        obe.username = "simuser";
        
        if(wallet.canFulfillOrder(obe))
        {
            std::cout<<"Wallet looks good. "<<std::endl;
            orderBook.insertOrder(obe);
        }
        else
        {
            std::cout<<"Wallet has insuffient funds. "<<std::endl;
        }
        }
        catch(const std::exception& e)
        {
            std::cout<<"MerkelMain::enterAsk Bad input"<<std::endl;
        }
    }
}
void MerkelMain::enterBid()
{
    std::cout<<"Make and bid - enter the amount: product, price, amount, eg ETH/BTC, 200, 0.5"<<std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVreader::tokenise(input, ',');
    if(tokens.size() != 3)
    {
        std::cout<<"MerkelMain::enterBid Bad input! "<<input<<std::endl;
    }
    else
    {
        try
        {
        OrderBookEntry obe = CSVreader::stringsToOBE(currentTime,
                                    tokens[1],
                                    OrderBookType::bid,
                                    tokens[3],
                                    tokens[4]);
        obe.username = "simuser";
        
        if(wallet.canFulfillOrder(obe))
        {
            std::cout<<"Wallet looks good. "<<std::endl;
            orderBook.insertOrder(obe);
        }
        else
        {
            std::cout<<"Wallet has insuffient funds. "<<std::endl;
        }
        }
        catch(const std::exception& e)
        {
            std::cout<<"MerkelMain::enterBid Bad input"<<std::endl;
        }
    }
}
void MerkelMain::printWallet()
{
    std::cout<<wallet.toString()<<std::endl;
}
void MerkelMain::gotoNextTimeframe()
{
    std::cout<<"Going to next time frame. "<<std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    std::cout<<"Sales: "<<sales.size()<<std::endl;
    for(OrderBookEntry& sale : sales)
    {
        std::cout<<"Sale price: "<<sale.price<<" amount"<<sale.amount<<std::endl;
        if(sale.username == "simuser")
        {
            //update the 
            wallet.processSale(sale);

        }
    }
    currentTime = orderBook.getNextTime(currentTime);

}
void MerkelMain::printMenu()
{
    std::cout<<"1: Print help"<<std::endl;
    std::cout<<"2: Print exchange stats"<<std::endl;
    std::cout<<"3: Make an offer"<<std::endl;
    std::cout<<"4: Make a bid"<<std::endl;
    std::cout<<"5: Print wallet"<<std::endl;
    std::cout<<"6: Continue"<<std::endl;
    std::cout<<"================"<<std::endl;
    std::cout<<"Current time is: "<<currentTime<<std::endl;
}
int MerkelMain::getUserOption()
{
    std::string line;
    int userInput = 0;
    std::cout<<"Choose number between 1-6 "<<std::endl;
    std::getline(std::cin, line);
    try
    {
        userInput = std::stoi(line);
    }
    catch(const std::exception& e)
    {
        //
    }
    return userInput;
}
void MerkelMain::processUserOption(int userOption)
{
    switch (userOption)
        {
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        
        case 3:
            enterAsk();
            break;
        
        case 4:
            enterBid();
            break;

        case 5:
            printWallet();
            break;

        case 6:
            gotoNextTimeframe();
            break;

        default:
            std::cout<<"Invalid choice. Choose 1-6"<<std::endl;
            break;
        }
}
