#ifndef CSV_H
#define CSV_H

#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>

namespace CSV 
{
        //Struct to store each field of a line
        struct Line
        {
                std::vector<std::string> fields;
        };
        
        //Struct to hold all lines of a csv file
        struct CSV
        {
                std::list<Line> lines;
        };
        
        //Utility class. All functions are static
        class Parser
        {
                public:
                        //Static function which decides which way to parse a file.
                        //usesQuotes is default to false. If true it processes the 
                        //entire file in a way that assumes usage of quotes.
                        //Quotes cause a slowdown.
                        static CSV parseFile(const std::string &path, const bool usesQuotes=false)
                        {
                                CSV csv;
                                std::string line;
                                std::ifstream f(path);
                                if(usesQuotes) { 
                                        //Only check the bool once, rather than each while loop
                                        while(std::getline(f, line)) {
                                              csv.lines.push_back(parseLineWithQuotes(line));  
                                        }
                                } else {
                                        while(std::getline(f, line)) {
                                                csv.lines.push_back(parseLineWithoutQuotes(line));
                                        }
                                }
                                f.close();
                                return csv;
                        }

                private:
                        //Uses the lambda getField to handle quotes
                        //Not perfect. 
                        static Line parseLineWithQuotes(const std::string &line)
                        {       
                                Line outLine;
                                std::stringstream ss(line);
                                std::string field;
                                outLine.fields.reserve(10);
                                auto getField = [&](std::string &field){ 
                                        std::getline(ss, field, ',');
                                        if(field.front() == '"') {
                                                std::string tmp;
                                                field.erase(field.begin()); 
                                                tmp += field;
                                                while(tmp.back() != '"') {
                                                        //keep going through the field until " is reached
                                                        std::getline(ss, field, ','); 
                                                        tmp +=",";
                                                        tmp += field;
                                                }
                                                field = tmp;
                                                //remvoe any extra quotes
                                                std::for_each(field.begin(), field.end(), [](char &c){c = (c =='"') ? '\0' : c;});
                                        }
                                };
                                while(!ss.eof()) {
                                        getField(field);
                                        outLine.fields.push_back(std::move(field));
                                }
                                outLine.fields.shrink_to_fit();
                                return outLine;
                        }
                        //Deals with fields without quotes. Just simple csv. Much more
                        //effecient than the WithQuotes function.
                        static Line parseLineWithoutQuotes(const std::string &line)
                        {
                                Line outLine;
                                std::stringstream ss(line);
                                std::string field;
                                outLine.fields.reserve(10);
                                //lambda that gets the next field
                                auto getField = [&](std::string &field){ std::getline(ss, field, ',');  }; 
                                while(!ss.eof()) {
                                        getField(field);
                                        outLine.fields.push_back(std::move(field));
                                }
                                outLine.fields.shrink_to_fit();
                                return outLine;
                        }
        };
}

#endif //CSV_H
