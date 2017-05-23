#include "tree.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>

tree *
tree_add(int op, tree *left, tree *right, tree_union *val, char *name)
{
    tree *ret = malloc(sizeof (tree));
    if (ret != NULL) {
		ret->op = op;
		ret->left = left;
		ret->right = right;
		ret->val = val;	
		ret->name = name ? strdup(name) : NULL;
    }
	tree_print(ret, stdout, 0);
    return ret;
}

tree *
tree_delete(tree *node, int recursive)
{
    if (node != NULL) {
	if (node->name != NULL) {
	    free(node->name);
	    node->name = NULL;
	}
	if (recursive) {
	    if (node->left != NULL) {
		tree_delete(node->left, recursive);
		node->left = NULL;
	    }
	    if (node->right != NULL) {
		tree_delete(node->right, recursive);
		node->right = NULL;
	    }
	}
    }
	return NULL;
}

tree_union *
tree_union_int_val(int ival)
{
	tree_union *ret = malloc(sizeof (tree_union));
	ret->type = TYPE_INT;
	ret->ival = ival;
	return ret;
}

tree_union *
tree_union_double_val(double dval)
{
	tree_union *ret = malloc(sizeof (tree_union));
	ret->type = TYPE_DOUBLE;
	ret->dval = dval;
	return ret;
}

tree_union *
tree_union_string_val(char *sval)
{
	tree_union *ret = malloc(sizeof (tree_union));
	ret->type = TYPE_STRING;
	ret->sval = strdup(sval);
	return ret;
}

tree_union *
tree_union_clear(tree_union *val)
{
	if (val != NULL)
	{
		if (val->type == TYPE_STRING && val->sval != NULL) {
			free(val->sval);
		}
		free(val);
	}
	return NULL;
}

tree*  tree_not(tree *node)
{
    return tree_add(L_NOT, node, NULL, NULL, "NOT");
}

tree*  
tree_function_name(tree *node)
{
	node->op = L_FUNCTIONNAME;	// @@	Проверка, имя ли это функции
	return node;
}

tree*  
tree_identifier(char *name)
{
	return tree_add(L_IDENTIFIER, NULL, NULL, NULL, name);
}

tree*  
tree_int_const(int iconst)
{
	tree_union *val = tree_union_int_val(iconst);
	return tree_add(L_NUMBERLITERAL, NULL, NULL, val, "ICONST");
}

tree*  
tree_double_const(double dconst)
{
	tree_union *val = tree_union_double_val(dconst);
	return tree_add(L_DOUBLELITERAL, NULL, NULL, val, "DCONST");
}

tree *
tree_rational_const(const char *s)
{
	tree_union *val = tree_union_string_val(s);
	return tree_add(L_RATIONALLITERAL, NULL, NULL, val, "RCONST");
}

tree*  tree_string_const(char *sconst)
{
	tree_union *val = tree_union_string_val(sconst);
	return tree_add(L_STRINGLITERAL, NULL, NULL, val, "SCONST");
}

tree * 
tree_function_call(tree *node, tree *arguments)
{
	return tree_add(L_FUNCTIONCALL, node, arguments, NULL, "Function call");
}

void
tree_print(tree *tree, FILE *out, int level)
{
	int i;
	for (i = 0; i < level; i++)
	{
		fprintf(out, "  ");
	}
	if (tree == NULL) {
		fprintf(out, "NULL\n");
		return;
	}
	fprintf(out, "OP=%d NAME=%s\n", tree->op, tree->name == NULL ? "NULL" : tree->name);
	tree_print(tree->left, out, level+1);
	tree_print(tree->right, out, level+1);
}

tree *
tree_declare(tree *type, tree *varlist)
{
	return NULL; // @@
}

tree *
tree_new_function(tree *type, tree *name, tree *arg_list, tree *var_list, tree *stmt_list)
{
	return NULL; // @@ 
}


