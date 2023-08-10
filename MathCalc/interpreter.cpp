#include "interpreter.h"

Interpreter::Interpreter()
{

}

Interpreter::~Interpreter()
{

}

int Interpreter::interpret(ParseTree& tree)
{
	resolv(tree.get_parse_tree());
	// tree.traverse("infix");
	std::cout << "Res: " << tree.get_parse_tree()->val << std::endl;
	return 0;
}

void Interpreter::resolv(Binop* root)
{
	if (root == nullptr) return;
	resolv(root->left);
	resolv(root->right);
	if (is_operator(root->val)) {
		char buff_temp[128];
		if (strcmp((char*)root->val, "+") == 0)
			_itoa_s((atoi((char*)root->left->val) + atoi((char*)root->right->val)), buff_temp, 128, 10);
		else if (strcmp((char*)root->val, "-") == 0)
			_itoa_s((atoi((char*)root->left->val) - atoi((char*)root->right->val)), buff_temp, 128, 10);
		else if (strcmp((char*)root->val, "*") == 0)
			_itoa_s((atoi((char*)root->left->val) * atoi((char*)root->right->val)), buff_temp, 128, 10);
		else if (strcmp(root->val, "/") == 0)
			_itoa_s((atoi((char*)root->left->val) / atoi((char*)root->right->val)), buff_temp, 128, 10);
		else
			_itoa_s(pow(atoi((char*)root->left->val), atoi((char*)root->right->val)), buff_temp, 128, 10);
		//std::cout << root->val << std::endl;
		free(root->left), free(root->right), free(root->val);
		root->left = root->right = nullptr, root->val = nullptr;
		size_t valen = strlen(buff_temp);
		root->val = (char*)malloc((valen + 1) * sizeof(char));
		memcpy_s(root->val, (valen + 1), buff_temp, valen), root->val[valen] = '\0';
		//std::cout << root->val << std::endl;
	}
}

bool Interpreter::is_operator(const char* c)
{
	if ((strcmp(c, "+") == 0 || strcmp(c, "-") == 0 || strcmp(c, "*") == 0 || strcmp(c, "/") == 0 || strcmp(c, "^") == 0))
		return true;
	return false;
}