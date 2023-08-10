#include "parse_tree.h"
#include <iostream>
#include <cstdlib>
#include <string>

ParseTree::ParseTree() {}

ParseTree::ParseTree(const char* val)
{
	root = create_node(val);
}

ParseTree::~ParseTree()
{
	prune(root);
}

int ParseTree::insert_node(Binop* node)
{
	if (root == nullptr) {
		root = node;
		return 0;
	}
	if (root->left != nullptr)
		root->left = node;
	else if (root->right != nullptr)
		root->right = node;
	else {
		node->left = root;
		root = node;
	}
	return 0;
}

Binop* ParseTree::create_node(const char* val)
{
	Binop* rt = (Binop*)malloc(sizeof(Binop));
	if (rt == nullptr) return rt;
	size_t valen = strlen(val);
	rt->val = (char*)malloc((valen + 1) * sizeof(char));
	memcpy_s(rt->val, (valen + 1), val, valen), rt->val[valen] = '\0';
	rt->left = rt->right = nullptr;
	return rt;
}

void ParseTree::traverse(const char *mode) const
{
	if (strcmp(mode, "prefix") == 0)
		traverse_prefix(root);
	else if (strcmp(mode, "infix") == 0)
		traverse_infix(root);
	else
		traverse_postfix(root);
}

void ParseTree::traverse_prefix(Binop* root) const
{
	if (root == nullptr) return;
	std::cout << root->val << std::endl;
	traverse_prefix(root->left);
	traverse_prefix(root->right);
}

void ParseTree::traverse_infix(Binop* root) const
{
	if (root == nullptr) return;
	traverse_infix(root->left);
	std::cout << root->val << std::endl;
	traverse_infix(root->right);
}

void ParseTree::traverse_postfix(Binop* root) const
{
	if (root == nullptr) return;
	traverse_postfix(root->left);
	traverse_postfix(root->right);
	std::cout << root->val << std::endl;
}

void ParseTree::prune(Binop* root)
{
	if (root == nullptr) return;
	prune(root->left);
	prune(root->right);
	//std::cout << "Removing " << root->val << std::endl;
	free((char*)root->val);
	free((Binop*)root);
}

Binop* ParseTree::get_parse_tree(void)
{
	return root;
}