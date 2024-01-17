#ifndef CSVreader_h
#define CSVreader_h

#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVreader
{
    public:
    CSVreader();

    static std::vector<OrderBookEntry> readCSV(std::string csvFile);
    static std::vector<std::string> tokenise(std::string csvLine, char separator);
    static OrderBookEntry stringsToOBE(std::string timestamp,
                                        std::string product,
                                        OrderBookType OrderBookType,
                                        std::string price,
                                        std::string amount);
    private:
    static OrderBookEntry stringsToObe(std::vector<std::string> strings);

};
#endif /* CSVreader_hpp */