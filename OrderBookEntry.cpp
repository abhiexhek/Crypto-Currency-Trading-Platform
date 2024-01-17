//
//  OrderBookEntry.cpp
//  CryptoPlatform
//
//  Created by Ankit Subedi on 04/01/2024.
//

#include "OrderBookEntry.h"
#include <string>

OrderBookEntry::OrderBookEntry( std::string _timestamp,
                                std::string _product,
                                OrderBookType _orderType,
                                double _price,
                                double _amount,
                                std::string _username)
                                :
                                timestamp(_timestamp),
                                product(_product),
                                orderType(_orderType),
                                price(_price),
                                amount(_amount),
                                username(_username)

{

}
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s) {
  if (s == "ask")
    return OrderBookType::ask;
  if (s == "bid")
    return OrderBookType::bid;
  return OrderBookType::unknown;
}
