#ifndef Wallet_h
#define Wallet_h

#pragma once
#include <string>
#include <map>
#include "OrderBookEntry.h"
class Wallet
{
    public:
        Wallet();
        /** inset currency to the wallet*/
        void insertCurrency(std::string type, double amount);
  /** remove currency to the wallet*/
        bool removeCurrency(std::string type, double amount);
        /** Check if the wallet contains this much currency or more*/
        bool containsCurrency(std::string type, double amount);
    /** checks if the wallet can cope with this ask or bid*/
        bool canFulfillOrder(OrderBookEntry order);
        /** update the contents of the wallet 
         *assumes the order was made by the owner of the wallet*/
        void processSale(OrderBookEntry& sale);

        /** generate the string representation of the wallet*/
        std::string toString();


    private:
        std::map<std::string, double> currencies;


};
#endif