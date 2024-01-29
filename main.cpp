#include <iostream>
using namespace std;

class Parser{
    int pos=0;
    string input;

    // Lexical

    void SkipWhiteSpaces(){
        while(pos<input.size()&&(input[pos]==' '||input[pos]=='\n'))
            pos++;
    }

    bool ParseStringLit(){
        if(pos>input.size()||input[pos]!='"')
            return false;
        string sub = input.substr(pos+1);
        int ind = sub.find('"');
        if(ind!=-1) {
            pos+=ind+2;
            SkipWhiteSpaces();
            return true;
        }
        return false;
    }

    bool ParseNumber(){
        if(pos>input.size())
            return false;
        int curr=pos;
        while(input[pos]>='0' && input[pos] <= '9' )
            pos++;
        SkipWhiteSpaces();
        return pos>curr;
    }

    bool ParseChar(char c){
        if(pos>input.size() || input[pos]!=c)
            return false;
        pos++;
        SkipWhiteSpaces();
        return true;
    }

    // Parser

    // JSON Grammar
    /*
        VALUE   ::= STRINGLIT / NUMBER / OBJECT / ARRAY
        OBJECT  ::= "{" (PAIR ("," PAIR)* )? "}"
        PAIR    ::= STRINGLIT ":" VALUE
        ARRAY   ::= "[" (VALUE ("," VALUE)* )? "]"
    */

    bool ParseValue(){
        return ParseStringLit() || ParseNumber() || ParseObject() || ParseArray();
    }

    bool ParseObject(){
        int curr_pos = pos;
        if(ParseChar('{')&&ParsePairs()&&ParseChar('}')){
            return true;
        }
        pos = curr_pos;
        return false;
    }

    bool ParsePairs(){
        if(ParsePair())
            ParsePairTail();
        return true;
    }

    bool ParsePair(){
        int curr_pos = pos;
        if(ParseStringLit()&&ParseChar(':')&&ParseValue())
            return true;
        pos=curr_pos;
        return false;
    }

    bool ParsePairTail(){
        while(true) {
            int curr_pos = pos;
            if(!(ParseChar(',')&&ParsePair())) {
                pos = curr_pos;
                return true;
            }
        }
    }

    bool ParseArray(){
        int curr_pos = pos;
        if(ParseChar('[')&&ParseValues()&&ParseChar(']'))
            return true;
        pos = curr_pos;
        return false;
    }

    bool ParseValues(){
        if(ParseValue())
            ParseValueTail();
        return true;
    }

    bool ParseValueTail(){
        while(true){
            int curr_pos = pos;
            if(!(ParseChar(',')&&ParseValue())) {
                pos = curr_pos;
                return true;
            }
        }
    }

public:
    Parser(string in):input(in){}

    bool ParseJSON(){
        return ParseValue();
    }
};

int main() {
    string json=  "{\"fares\":[1,2,3,4],\n"
                   " \"atef\":\"fares\"}";
    string json2 = "{\"variant\":{\"type\":\"real\",\"value\":12},\"array1d\":[{\"0\":{\"type\":"
                   "\"real\",\"value\":12}},{\"1\":{\"type\":\"real\",\"value\":12}}],\"array2d\":[{\"1\":[{\"0\":{\"type\":"
                   "\"real\","
                   "\"value\":12}},{\"1\":{\"type\":\"real\",\"value\":12222}}]}]}";
    string json3 = "{\"variant\":{\"type\":\"real\",\"value\":1234},\"array1d\":[{\"0\":{\"type\":"
                   "\"real\",\"value\":123334}},{\"1\":{\"type\":\"real\",\"value\":12323234}},{\"2\":{\"type\":"
                   "\"real\",\"value\":1234}}],\"array2d\":[{\"1\":[{\"0\":{\"type\":\"real\",\"value\":1231114}},{\"1\":{\"type\":"
                   "\"real\",\"value\":9934}},{\"2\":{\"type\":\"real\",\"value\":123767224}}]},{\"2\":[{\"0\":{\"type\":"
                   "\"real\",\"value\":12899834}},{\"1\":{\"type\":\"real\",\"value\":12389324}},{\"2\":{\"type\":"
                   "\"real\",\"value\":12349954}}]}]}";
    Parser parser(json3);
    if(parser.ParseJSON())
        cout << "Valid JSON";
    else
        cout << "Invalid JSON";
    return 0;
}
