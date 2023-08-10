#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

// TODO
// float numbers
// variables
// functions

int main(int argc, char* argv[])
{
    //Lexer tknr("(1432 + 50x (3.4^2) - 112) / sin90xy * pi/2");
    //Lexer tknr("((50) / 25)");
    //Lexer tknr("((3*5+8/2+1)/4)*250");
    //Lexer tknr("-5^2+(-25)/5");
    //Lexer tknr("-(5^2)*(-5)!"); // FIX: Factorial 
    //Lexer tknr("-(5^2)+-5");
    //Lexer tknr("5.2+5.5");
    Lexer tknr("5/5+5*5");
    //Lexer tknr("0  +   3");
    std::vector<Token*> tk = tknr.get_tokens();

    for (auto i : tk)
        std::cout << i->type << " " << i->value << std::endl;

    Parser parser;
    parser.parse(tk);
    //parser.show_expresion();

    std::cout << "INTERPRETER" << std::endl;
    Interpreter interpreter;
    interpreter.interpret(parser.get_parse_tree());

    return 0;
}
