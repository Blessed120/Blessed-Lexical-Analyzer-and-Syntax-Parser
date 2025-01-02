Constructing a Compiler design Lexical Analyzer and Syntax Parser

**part 1: In this projects, I wrote Lexical and Syntax Analyzer capable of parsing a source code
file provided by the user. This syntax for this language will be based upon the following grammar (in BNF):**
P ::= S
S ::= V = E; | input(V); | output(E); | if ( C ) { S } | if ( C ) { S } else { S } | S S
C ::= E < E | E > E | E == E | E != E | E <= E | E >= E | C && C | C || C | !C
E ::= T | E + T | E - T
T ::= F | T * F | T / F | T % F
F ::= (E) | N | V
V ::= a | b | … | y | z | aV | bV | … | yV | zV
N ::= 0 | 1 | … | 8 | 9 | 0N | 1N | … | 8N | 9N
Keep in mind that the V and N grammar rules establish the formal rules for identifiers (V) and Integer literals (N)
respectively.

Lexemes
Lexeme formation is guided using the BNF rules / grammar above. Your application should match each lexeme
with its associated token. Invalid lexemes should be assigned to a token group called UNKNOWN. The following
token names should be used to identify each valid lexeme:
Lexeme Token Lexeme Token Lexeme Token
= ASSIGN_OP           + ADD_OP               input KEY_IN
< LESSER_OP           - SUB_OP               output KEY_OUT
> GREATER_OP          * MULT_OP              if KEY_IF
== EQUAL_OP           / DIV_OP               else KEY_ELSE
!= NEQUAL_OP          % MOD_OP               { OPEN_CURL
<= LEQUAL_OP          && BOOL_AND            } CLOSE_CURL
>= GEQUAL_OP          || BOOL_OR             V IDENT
( OPEN_PAREN          ! BOOL_NOT             N INT_LIT
) CLOSE_PAREN         ; SEMICOLON

Lexemes that do not match to a known token should be reported as an “UNKNOWN” token. This 



**PART 2: Using your lexical analyzer developed in Project #1 and the parser code provided in class as a guide, develop arecursive descent syntax parser in C or C++ that can validate the syntax of a source code file provided by the user**

Your parser should read a source code file then, using your lexical analyzer, identify
lexemes/tokens one at a time to ensure they can be aligned with known BNF rules for the language. For this
language, P::=S would be the root of the parse tree. Your parser may print out the steps it takes during
execution if you wish (similar to the provided parser) but that is not required. The following is the only required
output and exit codes from your parser:

1)  If the provided user file is free of syntax errors:
a. Your solution must print out “Syntax Validated” as the last line of output.
b. Your solution must return with an exit code of 0.

2) If the provided user file contains syntax errors:
a. Your solution must print out “Error encounter on line <num>: The next lexeme was <lexeme>
and the next token was <token>”
i. Where <num> is the line number where the error occurred (where the first line of a
program is line 1)
ii. Where <lexeme> is the lexeme that caused the problem (examples: “x”, “<>”)
iii. Where <token> is the uppercase name of the token (examples: “IDENT”, “UNKNOWN”)
b. Your solution must return with an exit code of 1.


3) If the user did not provide a file as input:
a. Your solution must display an appropriate error message.
b. Your solution must return with an exit code of 2.

4) If the user did provide a file as input but the file does not exist:
a. Your solution must display an appropriate error message.
b. Your solution must return with an exit code of 3.

5) If a user input file contains multiple syntax errors, your solution is only required to find and report the
first syntax error.

