#include <iostream>
#include <vector>
#include <string>
#include <fstream>
std::vector<std::string>tokenise(std::string csvLine, char separator)

{
    std::vector<std::string> tokens;
    int start, end;
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
    return  tokens;
}
int main()
{
    std::string csvFilename{"crypto.csv"};
    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
    std::cout << "Opened file " << csvFilename << std::endl;
    }
    else
    {
    std::cout << "Problem opening file " << csvFilename << std::endl;
    }
    // don't forget to close it!
    csvFile.close();
    return 0;
}