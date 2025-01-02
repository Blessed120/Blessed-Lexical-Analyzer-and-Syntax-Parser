
/*

lEXICAL ANALYZER IN C++
The purpose of this program is to identify lexemes and tokens from an input file  and match them with token groups
then print each lexeme and/or token pair to the screen
*/

// From code line 12 - 16, i imported neccesary libraries

#include <iostream>
#include <fstream> 
#include <string>
#include <map>
#include <vector>

//  From line 19 to 48, enum is use to define tokens for the Cooke language
enum Token {
    ASSIGN_OP,
    LESSER_OP,
    GREATER_OP,
    EQUAL_OP,
    NEQUAL_OP,
    LEQUAL_OP,
    GEQUAL_OP,
    OPEN_PAREN,
    CLOSE_PAREN,
    ADD_OP,
    SUB_OP, 
    MULT_OP, 
    DIV_OP, 
    MOD_OP,
    BOOL_AND,
    BOOL_OR,
    BOOL_NOT,
    SEMICOLON, 
    KEY_IN,
    KEY_OUT,
    KEY_IF,
    KEY_ELSE,
    OPEN_CURL,
    CLOSE_CURL,
    IDENT,
    INT_LIT,
    UNKNOWN,
};

// From line 51 to 80, we are mapping each each token declared above to its correspoding string value

std::map<Token, std::string> tokenNames = {
    
    {ASSIGN_OP, "ASSIGN_OP"},
    {LESSER_OP, "LESSER_OP"},
    {GREATER_OP, "GREATER_OP"},
    {EQUAL_OP, "EQUAL_OP"},
    {NEQUAL_OP, "NEQUAL_OP"},
    {LEQUAL_OP, "LEQUAL_OP"},
    {GEQUAL_OP, "GEQUAL_OP"},
    {OPEN_PAREN, "OPEN_PAREN"},
    {CLOSE_PAREN, "CLOSE_PAREN"},
    {ADD_OP, "ADD_OP"},
    {SUB_OP, "SUB_OP"},
    {MULT_OP, "MULT_OP"},
    {DIV_OP, "DIV_OP"},
    {MOD_OP, "MOD_OP"},
    {BOOL_AND, "BOOL_AND"},
    {BOOL_OR, "BOOL_OR"},
    {BOOL_NOT, "BOOL_NOT"},
    {SEMICOLON, "SEMICOLON"},
    {KEY_IN, "KEY_IN"},
    {KEY_OUT, "KEY_OUT"},
    {KEY_IF, "KEY_IF"},
    {KEY_ELSE, "KEY_ELSE"},
    {OPEN_CURL, "OPEN_CURL"},
    {CLOSE_CURL, "CLOSE_CURL"},
    {IDENT, "IDENT"},
    {INT_LIT, "INT_LIT"},
    {UNKNOWN, "UNKNOWN"} 
};

// From line 83 to 86, we are holding each token to string lexeme value
struct TokenInfo {
    Token token;
    std::string lexeme;
};

// From line 90 to 117, we are mapping each token/lexeme to a string word 

std::map<std::string, Token> keywords = {
    {"=", ASSIGN_OP},
    {"<", LESSER_OP},
    {">", GREATER_OP},
    {"==", EQUAL_OP},
    {"!=", NEQUAL_OP},
    {"<=", LEQUAL_OP},
    {">=", GEQUAL_OP},
    {"(", OPEN_PAREN},
    {")", CLOSE_PAREN},
    {"+", ADD_OP},
    {"-", SUB_OP},
    {"*", MULT_OP},
    {"/", DIV_OP},
    {"%", MOD_OP},
    {"&&", BOOL_AND},
    {"||", BOOL_OR},
    {"!", BOOL_NOT},
    {";", SEMICOLON},
    {"input",KEY_IN},
    {"output", KEY_OUT},
    {"if", KEY_IF},
    {"else", KEY_ELSE},
    {"{", OPEN_CURL},
    {"}", CLOSE_CURL},
    {"V",IDENT},
    {"N", INT_LIT},   
};

/*
From line  124 to 178, the getNextToken function reads chacters from the input file
inorder to generate tokens.
*/

TokenInfo getNextToken(std::ifstream& file) {
    char c;
    std::string lexeme;
    file >> std::noskipws; // White spaces processing

    while (file.get(c) && (std::isspace(c))) {}

    if (file.eof()) return {UNKNOWN, ""}; // End of file
    // Line 133 - 139 check for alphabet
    if (std::isalpha(c)) {
        lexeme += c;
        while (file.get(c) && (std::isalnum(c) || c == '_')) {
            lexeme += c;
        }
        file.putback(c);
        return {keywords.count(lexeme) ? keywords[lexeme] : IDENT, lexeme};
      //  line 141 - 149 handles integers  
    } else if (std::isdigit(c)) {
        lexeme += c;
        while (file.get(c) && std::isdigit(c)) {
            lexeme += c;
        }
        file.putback(c);
        return {INT_LIT, lexeme};
    } else {
        lexeme += c;
        
        // Line 154 to 162 handles <= lexeme, and returns LEQUAL if <= operetor is found in order
        
        
        if (lexeme == "<") {
            if (file.get(c) && c == '=') {
                lexeme += c;
                return {LEQUAL_OP, lexeme};
            } 
            else {
                file.putback(c);
            }
        }
        
        // Line 165 to 173 handles <= lexeme, and returns GEQUAL_OP if >= operetor is found in order
           else if (lexeme == ">") {
            if (file.get(c) && c == '=') {
                lexeme += c;
                return {GEQUAL_OP, lexeme};
            } else {
                file.putback(c);
            }  
            
        }
        
        // Line 177 to 184 handles && lexeme, and returns BOOL_AND if && operetor is found in order
        
        else if (lexeme == "&") {
            if (file.get(c) && c == '&') {
                lexeme += c;
                return {BOOL_AND, lexeme};
            } else {
                file.putback(c);
            }
        } 
        
        // Line 187 to 194 handles || lexeme, and returns BOOL_OR if || operetor is found in order
        else if (lexeme == "|") {
            if (file.get(c) && c == '|') {
                lexeme += c;
                return {BOOL_OR, lexeme};
            } else {
                file.putback(c);
            }
        }
        
        
        if (lexeme == "+" || lexeme == "-" || lexeme == "*" || lexeme == "/") {
            if (file.get(c) && c == lexeme[0]) {
                lexeme += c;
            } else {
                file.putback(c);
            }
        }
        
        // // Line 206 to 216 handles <= lexeme, and returns NEQUAL_OP if <= operetor is found in order
        else if(lexeme == "!"){
          if(file.get(c) && c == '='){
            lexeme += c;
            return {NEQUAL_OP, lexeme};
            
          }
          else{
            file.putback(c);
          
          }
        }
        
        // Line 219 to 228 handles == lexeme, and returns EQUAL_OP if == operetor is found in order
      else if (lexeme == "="){
         if(file.get(c) && c == '='){
            lexeme +=c;
            
            return {EQUAL_OP, lexeme};
          }
          else{
           file.putback(c);
          }
        }

        // Handle other single character operators
        if (keywords.count(lexeme)) {
            return {keywords[lexeme], lexeme};
        }

        // If it reaches here and it's not recognized, return UNKNOWN
        return {UNKNOWN, lexeme};
        
    }
}

// From line 243 to 253, Simply getting input file from user and complete other steps

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cout << "File not found: " << argv[1] << std::endl;
        return 1;
    }

    std::cout << "Cooke Analyzer :: R<11920009>" << std::endl; // Printing out Cooke Analyzer and my R - Number

// This while condition is to process tokens until we reach End Of File
    while (true) {
        TokenInfo tokenInfo = getNextToken(inputFile);
        if (tokenInfo.token == UNKNOWN && tokenInfo.lexeme.empty()) {
            break; // End of file
        }

        if (tokenInfo.token == UNKNOWN) {
            std::cout << tokenInfo.lexeme <<"\tUNKNOWN" << std::endl;
        } else {
            std::cout << tokenInfo.lexeme << "\t" << tokenNames[tokenInfo.token] << std::endl;
        }
    }

// The file closes and ends at this point and returns 0, meaning it was succesful
    inputFile.close();
    return 0;
}
