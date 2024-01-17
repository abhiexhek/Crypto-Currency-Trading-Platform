#include "CSVreader.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <fstream>

CSVreader::CSVreader()
{

}
std::vector<OrderBookEntry> CSVreader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFilename};
    std::string line;
    if(csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try {
                
                OrderBookEntry obe = stringsToObe(tokenise(line, ','));
                entries.push_back(obe);

            } 
            catch (const std::exception& e)
            {
                std::cout<<"CSVreader::readCSV bad data "<<std::endl;
            }        }//end of while
    }
    std::cout<<"CSVreader::readCSV read "<<"entries "<<entries.size()<<std::endl;
    return entries;
}
std::vector<std::string> CSVreader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do {
        end = csvLine.find_first_of(separator, start);
        if(start == csvLine.length() || start == end)
            break;
        if(end >= 0)
            token = csvLine.substr(start, end-start);
        else token = csvLine.substr(start, csvLine.length()-start);
        tokens.push_back(token);
        start = end + 1;
        
    } while (end != std::string::npos);
    return  tokens;}
OrderBookEntry CSVreader::stringsToObe(std::vector<std::string> tokens)
{
    double price, amount;
            if (tokens.size()!= 5)
            {
                std::cout<<"Bad token"<<std::endl;
                throw std::exception{};
            }
            try
            {
                
                price = std::stod(tokens[3]);
                amount = std::stod(tokens[4]);
            } catch (std::exception& e)
            {
                std::cout<<"CSVReader::stringTOOBE Bad float! "<<tokens[3]<<std::endl;
                std::cout<<"CSVReader::stringTOOBE Bad float! "<<tokens[4]<<std::endl;
                throw;
    
            }
    OrderBookEntry obe{tokens[0],
                        tokens[1],
                        OrderBookEntry::stringToOrderBookType(tokens[2]),
                        price,
                        amount
                    };
return obe;
}
 OrderBookEntry CSVreader::stringsToOBE(std::string timestamp,
                                        std::string product,
                                        OrderBookType OrderType,
                                        std::string priceString,
                                        std::string amountString)
{
    double price, amount;
      try
            {
                
                price = std::stod(priceString);
                amount = std::stod(amountString);
            } catch (std::exception& e)
            {
                std::cout<<"CSVReader::stringToOBE Bad float! "<<priceString<<std::endl;
                std::cout<<"CSVReader::stringToOBE Bad float! "<<amountString<<std::endl;
                throw;
    
            }
  OrderBookEntry obe{timestamp,
                        product,
                        OrderType,
                        price,
                        amount
                    };
return obe;
}
