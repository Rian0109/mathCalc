#include "parser.h"
#include <iostream>
#include <string>
#include <cmath>

Parser::Parser()
{
}

Parser::Parser(std::vector<Token*>& tks)
{
	parse(tks);
}

Parser::~Parser()
{
}

ParseTree& Parser::parse(std::vector<Token*>& tks)
{
	check_expresion(tks);
	eval(tks);
	generate_parse_tree_it(mathexp);
	//parse_tree.traverse("infix");
	return get_parse_tree();
}

int Parser::generate_parse_tree_it(std::vector<char*> mvtemp)
{
	for (int i = 0; i < mvtemp.size(); ++i) {
		if (mvtemp[i] == "(") continue;
		if (mvtemp[i] == ")") {
			mvtemp.erase(mvtemp.begin() + i);
			int it = i - 2;
			//std::cout << mvtemp[it] << std::endl;
			if (is_operator(mvtemp[it])) {
				// Don't want to remove lparen while successive operations (op_count > 0)
				int op_count = 0;
				Binop* op;
				do {
					//std::cout << "CALC: " << mvtemp[it - 1] << mvtemp[it] << mvtemp[it + 1] << std::endl;
					op = parse_tree.create_node(mvtemp[it]);
					// _NODE_ +- _NODE_
					if (strcmp(mvtemp[it - 1], "_NODE_") == 0 && strcmp(mvtemp[it + 1], "_NODE_") == 0) {
						op->left = node_stack.top(), node_stack.pop();
						op->right = node_stack.top(), node_stack.pop();
					}
					else if (strcmp(mvtemp[it - 1], "_NODE_") == 0) { // _NODE_ +- num
						op->left = node_stack.top(), node_stack.pop();
						op->right = parse_tree.create_node((char*)mvtemp[it + 1]);
					}
					else if (strcmp(mvtemp[it + 1], "_NODE_") == 0) { // num +- _NODE_
						op->left = parse_tree.create_node((char*)mvtemp[it - 1]);
						op->right = node_stack.top(), node_stack.pop();
					}
					else { // num +- num
						op->left = parse_tree.create_node((char*)mvtemp[it - 1]);
						op->right = parse_tree.create_node((char*)mvtemp[it + 1]);
					}
					/*char* buff;
					size_t len = strlen(buff_temp) + 1;
					buff = (char*)malloc(len * sizeof(char));
					memcpy(buff, buff_temp, len);*/
					mvtemp.insert(mvtemp.begin() + it - 1, (char*)"_NODE_"); //insert new value
					mvtemp.erase(mvtemp.begin() + it, mvtemp.begin() + it + 3); // erase pre-operator operator post-operator

					if (op_count == 0) mvtemp.erase(mvtemp.begin() + it - 2);					
					i = (it - 2) < 0 ? 0 : it - 2;
					it = (it - 3) < 0 ? 0 : it - 3;
					//std::cout << "OP: " << mvtemp[it] << std::endl;
					// store node in stack
					node_stack.push(op);
					++op_count;
				} while (is_operator(mvtemp[it]));
				// store node in stack
				// node_stack.push(op);
			}
			else {
				// erase (
				mvtemp.erase(mvtemp.begin() + it);
				i = it;
			}
			/*for (int i = 0; i < mvtemp.size(); ++i)
				std::cout << mvtemp[i];
			std::cout << std::endl;*/
		}
		//if (mvtemp.size() == 1) break;
	}
	parse_tree.insert_node(node_stack.top());
	node_stack.pop();
	return 0;
}

void Parser::show_expresion(void) const
{
	for (auto i : mathexp)
		std::cout << (char*)i;
	std::cout << std::endl;
}

ParseTree& Parser::get_parse_tree(void)
{
	return parse_tree;
}

int Parser::check_expresion(std::vector<Token*>& tks)
{
	return 0;
}

int Parser::eval(std::vector<Token*>& tks)
{
	//mathexp.push_back((char*)"((");
	mathexp.insert(mathexp.end(), { (char*)"(", (char*)"(", (char*)"(", (char*)"(" });
	int i_prev;
	for (int i = 0; i < tks.size(); ++i) {
		i_prev = i - 1;
		if (strcmp(tks[i]->type, "number") == 0)
			mathexp.push_back((char*)tks[i]->value);
		if (strcmp(tks[i]->type, "operator") == 0) {
			if (strcmp(tks[i]->value, "+") == 0)
				mathexp.insert(mathexp.end(), { (char*)")", (char*)")", (char*)")", tks[i]->value, (char*)"(", (char*)"(", (char*)"(" });
			else if (strcmp(tks[i]->value, "-") == 0) {
				if (strcmp(tks[i + 1]->type, "number") == 0) // Precedence: i.e. -5 ^ 2 -> (-1 * 5) ^ 2
					mathexp.insert(mathexp.end(), { (char*)"(", (char*)"-1", (char*)")", (char*)")", (char*)"*", (char*)"(", (char*)"(", (char*)tks[++i]->value, (char*)")" });
				else if (i == 0 || (strcmp(tks[i_prev]->type, "number") && (strcmp(tks[i_prev]->type, "parenr") != 0)))
					mathexp.insert(mathexp.end(), { (char*)"-1", (char*)")", (char*)")", (char*)"*", (char*)"(", (char*)"(" });
				else
					mathexp.insert(mathexp.end(), { (char*)")", (char*)")", (char*)")", tks[i]->value, (char*)"(", (char*)"(", (char*)"(" });
			}
			else if (strcmp(tks[i]->value, "*") == 0 || strcmp(tks[i]->value, "/") == 0)
				mathexp.insert(mathexp.end(), { (char*)")", (char*)")", tks[i]->value, (char*)"(", (char*)"(" });
			else if (strcmp(tks[i]->value, "^") == 0)
				mathexp.insert(mathexp.end(), { (char*)")", tks[i]->value, (char*)"(" });
			/*else if (strcmp(tks[i]->value, "!") == 0) {
				mathexp.pop_back();
				mathexp.insert(mathexp.end(), { (char*)"fact(", tks[i_prev]->value, (char*)")" });
			}*/
			else
				mathexp.push_back((char*)tks[i]->value);
		}
		if (strcmp(tks[i]->type, "parenl") == 0)
			//mathexp.push_back((char*)"((");
			mathexp.insert(mathexp.end(), { (char*)"(", (char*)"(", (char*)"(", (char*)"(" });
		if (strcmp(tks[i]->type, "parenr") == 0)
			//mathexp.push_back((char*)"))");
			mathexp.insert(mathexp.end(), { (char*)")", (char*)")", (char*)")", (char*)")" });
	}
	//mathexp.push_back((char*)"))");
	mathexp.insert(mathexp.end(), { (char*)")", (char*)")", (char*)")", (char*)")" });

	return 1;
}

bool Parser::is_operator(const char *c)
{
	if ((strcmp(c, "+") == 0 || strcmp(c, "-") == 0 || strcmp(c, "*") == 0 || strcmp(c, "/") == 0 || strcmp(c, "^") == 0))
		return true;
	return false;
}