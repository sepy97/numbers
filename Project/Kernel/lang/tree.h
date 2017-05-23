#ifndef _TREE_H
#define _TREE_H     1

#include <stdio.h>
#include <stdlib.h>

typedef struct tree_union
{
	enum {
		TYPE_INT,
		TYPE_DOUBLE,
		TYPE_STRING
	} type;
	union {
		int     ival;
		double  dval;
		char    *sval;
	};
} tree_union;

typedef struct tree
{
    int               op; // One of lexical tokens
    struct tree *left;
    struct tree *right;
    tree_union       *val;
    char             *name;
} tree, *ptree;

extern tree_union* tree_union_int_val(int ival);
extern tree_union* tree_union_double_val(double dval);
extern tree_union* tree_union_string_val(char *string);
extern tree_union* tree_union_clear(tree_union *val);	// Надо вызывать всегда, когда мы не пользуемся union

extern tree*  tree_add(int op, tree *left, tree *right, tree_union *val, char *name);
extern tree*  tree_delete(tree *node, int recursive);
extern void	  tree_print(tree *node, FILE *out, int level);

extern tree*  tree_not(tree *node);
extern tree*  tree_function_name(tree *node);
extern tree*   tree_new_function(tree *type, tree *name, tree *arg_list, tree *var_list, tree *stmt_list);
extern tree * tree_function_call(tree *node, tree *arguments);
extern tree*  tree_int_const(int iconst); 
extern tree*  tree_double_const(double dconst);
extern tree*  tree_string_const(char *sconst); 
extern tree*  tree_identifier(char *name);
extern tree*  tree_declare(tree *type, tree *varlist);

#endif

