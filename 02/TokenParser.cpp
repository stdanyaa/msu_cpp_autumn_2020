#include "TokenParser.h"

std::string TokenParser::GetToken(std::string::const_iterator& it, 
                                    std::string::const_iterator& end_it)
{ 
    while( isspace(*it) && (it!=end_it) ) ++it;
    std::string token = "";
    while(!isspace(*it) && (it!=end_it)){
        token += *it;
        it++;
    }
    return token;
}

bool TokenParser::IsDigit(const std::string& token)
{
    for (char c : token) if (!isdigit(c)) return false;
    return true;
}

uint64_t TokenParser::ToDigit(std::string token)
{
    uint64_t digit = 0;
    for(std::string::iterator it = token.begin(); it!=token.end(); it++)
    {
        digit *= 10;
        digit+=*it-'0';
    }
    return digit;
}
    
TokenParser::TokenParser()
{
    EndCallback =  []() {};
    StartCallback = []() {};
    DigitTokenCallback = [](uint64_t digittoken){};
    StringTokenCallback = [](std::string& token){};
}

void TokenParser::SetStartCallback(callback_t func)                 { StartCallback = func;}
void TokenParser::SetEndCallback(callback_t func)                   { EndCallback = func;}
void TokenParser::SetStringTokenCallback(stringtokencallback_t func){ StringTokenCallback = func;}
void TokenParser::SetDigitTokenCallback(digittokencallback_t func)  { DigitTokenCallback = func;}

void TokenParser::Parse(const std::string &text)
{
    std::string token;
    std::string::const_iterator it = text.begin();
    std::string::const_iterator it_end = text.end();
    StartCallback();
    if (!text.empty())
        while((token = GetToken(it, it_end)) != ""){
            if (IsDigit(token)){
                DigitTokenCallback(ToDigit(token));
            }
            else StringTokenCallback(token);
        }
    EndCallback();
}