//
//  OrderBook.cpp
//  CryptoPlatform
//
//  Created by Ankit Subedi on 1/7/24.
//

#include "OrderBook.h"
#include "CSVreader.h"
#include <map>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVreader::readCSV(filename);
}
std::vector<std::string>OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;
    for(OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }
    
    for (auto const& e: prodMap)
    {
        products.push_back(e.first);
    }
    
    return products;
}
std::vector<OrderBookEntry>OrderBook::getOrders(OrderBookType type,
                                    std::string product,
                                     std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e: orders)
    {
        if(e.orderType == type&&
           e.product == product&&
           e.timestamp == timestamp)
        {
            orders_sub.push_back(e);
        }
    }
    
    return  orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for(OrderBookEntry& e: orders)
    {
        if(e.price>max)
            max = e.price;
    }
    return  max;
}
double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double low = orders[0].price;
    for(OrderBookEntry& e: orders)
    {
        if(e.price<low)
            low = e.price;
    }
    return  low;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}
std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string nextTimestamp = "";
    for (OrderBookEntry&e: orders )
    {
        if(e.timestamp>timestamp)
        {
            nextTimestamp = e.timestamp;
            break;
        }
    }
    if(nextTimestamp == "")
    {
        nextTimestamp = orders[0].timestamp;
    }
    return  nextTimestamp;
}
void OrderBook::insertOrder(OrderBookEntry& order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(),OrderBookEntry::compareByTimeStamp);
}

 std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
 {
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
                                                    product,
                                                    timestamp);

    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::ask,
                                                        product,
                                                        timestamp);
    
    std::vector<OrderBookEntry> sales;
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for(OrderBookEntry& ask : asks)
    {
        for(OrderBookEntry& bid: bids)
        {
            if(bid.price>= ask.price)
            
            {
                OrderBookEntry sale{timestamp, product,OrderBookType::asksale,
                                    ask.price, 0};
                if(bid.username == "simuser")
                {
                    sale.username = "simuser"; 
                    sale.orderType = OrderBookType::bidsale;
                }
                if(ask.username == "simuser")
                {
                    sale.username = "simuser"; 
                    sale.orderType = OrderBookType::asksale; 
                }

                if(bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                }
                if(bid.amount>ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount-ask.amount;
                    break;
                }
                if(bid.amount<ask.amount && bid.amount > 0)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }

return sales;
 }