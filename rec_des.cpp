#include <iostream>
using namespace std;

class Rec_Parser{
    int pos=0;
    // look_ahead
    string input;
    char look_ahead= input[0];

    void SetPos(int p){
        pos = p;
        look_ahead = input[pos];
    }

    // Lexical

    void SkipWhiteSpaces(){
        while(pos<input.size()&&(input[pos]==' '||input[pos]=='\n'))
            SetPos(pos+1);
    }

    bool ParseStringLit(){
        if(pos>=input.size()||input[pos]!='"')
            return false;
        string sub = input.substr(pos+1);
        int ind = sub.find('"');
        if(ind!=-1) {
            SetPos(pos+ind+2);
            SkipWhiteSpaces();
            return true;
        }
        return false;
    }

    bool ParseNumber(){
        if(pos>=input.size())
            return false;
        int curr=pos;
        while(input[pos]>='0' && input[pos] <= '9' )
            SetPos(pos+1);
        SkipWhiteSpaces();
        return pos>curr;
    }

    bool ParseChar(char c){
        if(pos>=input.size() || input[pos]!=c)
            return false;
        SetPos(pos+1);
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


    // written using recursive descent style
    bool ParseValue(){
        bool res1 = ParseStringLit();
        if(res1) return true;
        bool res2 = ParseNumber();
        if(res2) return true;
        bool res3 = ParseObject();
        if(res3) return true;
        bool res4 = ParseArray();
        if(res4) return true;
        return false;
    }

    bool ParseObject(){
        int curr_pos = pos;
        if(look_ahead=='{'){
            bool res1 = ParseChar('{');
            bool res2 = ParsePairs();
            bool res3 = ParseChar('}');
            if(res1&&res2&&res3){
                return true;
            }
        }
        SetPos(curr_pos);
        return false;
    }

    bool ParsePairs(){
        if(ParsePair())
            ParsePairTail();
        return true;
    }

    bool ParsePair(){
        int curr_pos = pos;
        if(ParseStringLit()){
            bool res1 = ParseChar(':');
            bool res2 = ParseValue();
            if(res1&&res2){
                return true;
            }
        }
        SetPos(curr_pos);
        return false;
    }

    bool ParsePairTail(){
        int curr_pos = pos;
        if(look_ahead==','){
            bool res1 = ParseChar(',');
            bool res2 = ParsePair();
            if(res1&&res2){
                ParsePairTail();
                return true;
            }
        }
        SetPos(curr_pos);
        return true;
    }

    bool ParseArray(){
        int curr_pos = pos;
        if(look_ahead=='['){
            bool res1 = ParseChar('[');
            bool res2 = ParseValues();
            bool res3 = ParseChar(']');
            if(res1&&res2&&res3){
                return true;
            }
        }
        SetPos(curr_pos);
        return false;
    }

    bool ParseValues(){
        if(ParseValue())
            ParseValueTail();
        return true;
    }

    bool ParseValueTail(){
        int curr_pos = pos;
        if(look_ahead==','){
            bool res1 = ParseChar(',');
            bool res2 = ParseValue();
            if(res1&&res2){
                ParseValueTail();
                return true;
            }
        }
        SetPos(curr_pos);
        return true;
    }

public:
    Rec_Parser(string in):input(in){}

    void ChangeIn(string in){
        input=in;
        pos=0;
    }

    bool ParseJSON(){
        return ParseValue();
    }
};
