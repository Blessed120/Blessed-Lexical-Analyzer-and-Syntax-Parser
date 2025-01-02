

/*

RECURSIVE DESCENT PARSING IN C++
The purpose of this program is to write a recursive descent syntax parser in C++ that can validate the syntax of a source code file provided by the user. 
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>
#include <vector>
#include <stdexcept>

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

std::map<Token, std::string> tokenNames = {
    {ASSIGN_OP, "ASSIGN_OP"}, {LESSER_OP, "LESSER_OP"}, {GREATER_OP, "GREATER_OP"}, {EQUAL_OP, "EQUAL_OP"},
    {NEQUAL_OP, "NEQUAL_OP"}, {LEQUAL_OP, "LEQUAL_OP"}, {GEQUAL_OP, "GEQUAL_OP"}, {OPEN_PAREN, "OPEN_PAREN"},
    {CLOSE_PAREN, "CLOSE_PAREN"}, {ADD_OP, "ADD_OP"}, {SUB_OP, "SUB_OP"},  {MULT_OP, "MULT_OP"},  {DIV_OP, "DIV_OP"}, {MOD_OP, "MOD_OP"}, {BOOL_AND, "BOOL_AND"},
    {BOOL_OR, "BOOL_OR"}, {BOOL_NOT, "BOOL_NOT"}, {SEMICOLON, "SEMICOLON"},
    {KEY_IN, "KEY_IN"},  {KEY_OUT, "KEY_OUT"},{KEY_IF, "KEY_IF"},  {KEY_ELSE, "KEY_ELSE"},
    {OPEN_CURL, "OPEN_CURL"},  {CLOSE_CURL, "CLOSE_CURL"}, {IDENT, "IDENT"}, {INT_LIT, "INT_LIT"}, {UNKNOWN, "UNKNOWN"}
};

std::map<std::string, Token> keywords = {
    {"=", ASSIGN_OP},{"<", LESSER_OP}, {">", GREATER_OP}, {"==", EQUAL_OP}, {"!=", NEQUAL_OP}, {"<=", LEQUAL_OP},
    {">=", GEQUAL_OP}, {"(", OPEN_PAREN}, {")", CLOSE_PAREN}, {"+", ADD_OP},{"-", SUB_OP},{"*", MULT_OP},{"/", DIV_OP},
    {"%", MOD_OP}, {"&&", BOOL_AND}, {"||", BOOL_OR}, {"!", BOOL_NOT}, {";", SEMICOLON}, {"input", KEY_IN}, {"output", KEY_OUT}, {"if", KEY_IF}, {"else", KEY_ELSE},
    {"{", OPEN_CURL},{"}", CLOSE_CURL},
};

struct TokenInfo {
    Token token;
    std::string lexeme;
    int line; // Adding line number to token info
};

TokenInfo getNextToken(std::ifstream& file) {
    char c;
    std::string lexeme;
    static int lineNumber = 1;
    file >> std::noskipws; // White spaces processing
    

    while (file.get(c) && std::isspace(c)) {
      if(c== '\n'){
          lineNumber++;
      }
    
    }

   if (file.eof()) return {UNKNOWN, "", lineNumber}; // End of file
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
        return {INT_LIT, lexeme, lineNumber};
    } else {
        lexeme += c;
        
    if (lexeme == "(") {
        return {OPEN_PAREN, lexeme, lineNumber};
    }
     
    if (lexeme == ")") {
        return {CLOSE_PAREN, lexeme, lineNumber};
    }
        // Line 154 to 162 handles <= lexeme, and returns LEQUAL if <= operator is found in order
        if (lexeme == "<") {
            if (file.get(c) && c == '=') {
                lexeme += c;
                return {LEQUAL_OP, lexeme, lineNumber};
            } 
            else {
                file.putback(c);
            }
        }
        
        // Line 165 to 173 handles >= lexeme, and returns GEQUAL_OP if >= operator is found in order
        else if (lexeme == ">") {
            if (file.get(c) && c == '=') {
                lexeme += c;
                return {GEQUAL_OP, lexeme, lineNumber};
            } else {
                file.putback(c);
            }  
        }
         
        
        // Line 177 to 184 handles && lexeme, and returns BOOL_AND if && operator is found in order
        else if (lexeme == "&") {
            if (file.get(c) && c == '&') {
                lexeme += c;
                return {BOOL_AND, lexeme, lineNumber};
            } else {
                file.putback(c);
            }
        } 
        
        // Line 187 to 194 handles || lexeme, and returns BOOL_OR if || operator is found in order
        else if (lexeme == "|") {
            if (file.get(c) && c == '|') {
                lexeme += c;
                return {BOOL_OR, lexeme, lineNumber};
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
        
        // Line 206 to 216 handles != lexeme, and returns NEQUAL_OP if != operator is found in order
        else if(lexeme == "!"){
            if(file.get(c) && c == '='){
                lexeme += c;
                return {NEQUAL_OP, lexeme, lineNumber};
            }
            else{
                file.putback(c);
            }
        }
        
        // Line 219 to 228 handles == lexeme, and returns EQUAL_OP if == operator is found in order
        else if (lexeme == "="){
            if(file.get(c) && c == '='){
                lexeme += c;
                return {EQUAL_OP, lexeme, lineNumber};
            }
            else{
                file.putback(c);
            }
        }

        // Handle other single character operators
        if (keywords.count(lexeme)) {
            return {keywords[lexeme], lexeme, lineNumber};
        }
        
        
        

        // If it reaches here and it's not recognized, return UNKNOWN
        return {UNKNOWN, lexeme, lineNumber};
    }
}

class Parser {
public:
    explicit Parser(std::ifstream& file) : file(file), currentToken(getNextToken(file)) {}

    void parse() {
        stmts();
    }

    bool isValid() const {
        return currentToken.token == UNKNOWN; // End of file or valid termination
    }

private:
    std::ifstream& file;
    int lineNumber;
    TokenInfo currentToken;

    void lex() {
        currentToken = getNextToken(file);
         std::cout << "Current token: " << tokenNames[currentToken.token] << " Lexeme: " << currentToken.lexeme << std::endl;
    }

    void error(const std::string& message) {
        std::cerr << "Error encountered on line " << currentToken.line
                  << ": The next lexeme was '" << currentToken.lexeme
                  << "' and the next token was " << tokenNames[currentToken.token] << std::endl;
        exit(1); // Exit immediately if there is an error
    }

void stmts() {
    if (currentToken.token == IDENT) {
        lex();  // Consume IDENT
        if (currentToken.token == ASSIGN_OP) {
            lex();  // Consume ASSIGN_OP
            expr();  // Parse the expression
            if (currentToken.token == SEMICOLON) {
                lex();  // Consume SEMICOLON
                if (currentToken.token != CLOSE_CURL && currentToken.token != EOF) {
                    stmts();  // Recursive call to parse the next statement
                }
            } else {
                error("Missing semicolon after assignment");
            }
        } else {
            error("Missing assignment operator after identifier");
        }
    } else if (currentToken.token == KEY_IN) {
        lex();  // Consume 'input'
        if (currentToken.token == OPEN_PAREN) {
            lex();  // Consume '('
            if (currentToken.token == IDENT) {
                lex();  // Consume IDENT (n)
                if (currentToken.token == CLOSE_PAREN) {
                    lex();  // Consume ')'
                    if (currentToken.token == SEMICOLON) {
                        lex();  // Consume SEMICOLON
                        if (currentToken.token != CLOSE_CURL && currentToken.token != EOF) {
                            stmts();  // Recursive call to parse further statements
                        }
                    } else {
                        error("Missing semicolon after input statement");
                    }
                } else {
                    error("Missing closing parenthesis after input argument");
                }
            } else {
                error("Expected identifier after 'input' in parentheses");
            }
        } else {
            error("Missing opening parenthesis after 'input'");
        }
    } else if (currentToken.token == KEY_IF) {
        lex();  // Consume 'if'
        if (currentToken.token == OPEN_PAREN) {
            lex();  // Consume '('
            condition();  // Parse the condition
            if (currentToken.token == CLOSE_PAREN) {
                lex();  // Consume ')'
                if (currentToken.token == OPEN_CURL) {
                    lex();  // Consume '{'
                    stmts();  // Parse statements inside the 'if' block
                    if (currentToken.token == CLOSE_CURL) {
                        lex();  // Consume '}'
                        if (currentToken.token == KEY_ELSE) {
                            lex();  // Consume 'else'
                            if (currentToken.token == OPEN_CURL) {
                                lex();  // Consume '{'
                                stmts();  // Parse statements inside the 'else' block
                                if (currentToken.token == CLOSE_CURL) {
                                    lex();  // Consume '}'
                                } else {
                                    error("Missing closing curly brace after 'else' block");
                                }
                            } else {
                                error("Missing opening curly brace after 'else'");
                            }
                        }
                    } else {
                        error("Missing closing curly brace after 'if' block");
                    }
                } else {
                    error("Missing opening curly brace after 'if'");
                }
            } else {
                error("Missing closing parenthesis after 'if' condition");
            }
        } else {
            error("Missing opening parenthesis after 'if'");
        }
    } else if (currentToken.token == OPEN_CURL) {
        lex();  // Consume '{'
        stmts();  // Parse the block inside the curly braces
        if (currentToken.token == CLOSE_CURL) {
            lex();  // Consume '}'
        } else {
            error("Missing closing curly brace");
        }
    } else {
        error("Invalid statement");
    }
}




    void expr() {
        term();
        while (currentToken.token == ADD_OP || currentToken.token == SUB_OP) {
            lex();
            term();
        }
    }

    void term() {
        factor();
        while (currentToken.token == MULT_OP || currentToken.token == DIV_OP || currentToken.token == MOD_OP) {
            lex();
            factor();
        }
    }

    void factor() {
        if (currentToken.token == IDENT || currentToken.token == INT_LIT) {
            lex();
        } else if (currentToken.token == OPEN_PAREN) {
            lex();
            expr();
            if (currentToken.token == CLOSE_PAREN) {
                lex();
            } else {
                error("Missing closing parenthesis");
            }
        } else {
            error("Invalid factor");
        }
    }

  void condition() {
    if (currentToken.token == BOOL_NOT) {
        lex();  // Consume '!'
        condition();
    } else {
        expr();  // Parse the first expression
        if (currentToken.token == LESSER_OP || currentToken.token == GREATER_OP ||
            currentToken.token == EQUAL_OP || currentToken.token == NEQUAL_OP ||
            currentToken.token == LEQUAL_OP || currentToken.token == GEQUAL_OP) {
            lex();  // Consume relational operator
            expr();  // Parse the second expression
        }
    }

    // Handle logical operators && and ||
    while (currentToken.token == BOOL_AND || currentToken.token == BOOL_OR) {
        lex();  // Consume '&&' or '||'
        condition();  // Parse the next condition
      }
  }

};


int main(int argc, char** argv) {

    std::cout << "Cooke Parser :: R11920009" << std::endl;
    
    // Check if a file is provided as input
    if (argc < 2) {
        std::cerr << "Error: Please provide an input file." << std::endl;
        return 2;  // Return exit code 2 if no file is provided
    }

    // Try to open the file
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return 3;  // Return exit code 3 if the file cannot be opened
    }

    // Proceed with parsing if the file is successfully opened
    Parser parser(file);
    parser.parse();

    if (!parser.isValid()) {
        std::cerr << "Syntax Validated" << std::endl;
        return 0;  // Exit with code 0 if parsing is successful
    }

    return 1;  // Exit with code 1 if there's an error in parsing
}
