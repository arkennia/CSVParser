# CSVParser
Simple C++ CSV Parser

## Usage: 
Single Header: #include "csv.hpp"

CSV is a struct containing a std::list of Line structs. Line contains a std::vector of strings.

CSV namespace contains the Parser class.   

Methods:

        parseFile(<file path>, bool usesQuotes)

If your CSV file uses quotation marks, you must set usesQuotes to true or it will not read properly.

### Example:
```c
#include "csv.hpp"
#include <iostream>

int main()
{
        CSV::CSV myCSV = CSV::Parser::parseFile("mycsv.csv", true); 
        for(const auto &l : myCSV.lines) { //prints all lines and all fields
                for(const auto &d : l.fields) {
                        printf(" %s", d.c_str());
                }
                printf("\n\r");
        }
        return 0;
}
```
