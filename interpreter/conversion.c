#include "conversion.h"

/**
*	conversion.c by Henry Thacker
*	Version 2 - Rewritten 14/11/2009
*
*	Conversion functions for the --C language
*
*/

int t_count = 1;

/* NODE -> TOKEN CAST */
TOKEN * cast_from_node(NODE *node) {
	return (node==NULL ? NULL : (TOKEN *)node);
}

/* Return type of node */
int type_of(NODE *node) {
	if (node==NULL) {
		return -1;
	}
	return node->type;
}

/* ==== C TYPE -> VALUE UTILITIES ==== */

/* Make a string value out of a string */
value *string_value(char *val) {
	value *tmp_value = calloc(1, sizeof(value));
	char temporary_name[10];
	sprintf(temporary_name, "t%d", t_count);
	tmp_value->identifier = temporary_name;
	tmp_value->value_type = VT_STRING;
	tmp_value->data.string_value = (char *) malloc((sizeof(char) * strlen(val)) + 1);
	strcpy(tmp_value->data.string_value, val);
	t_count++;
	return tmp_value;
}

/* Make an int value out of an int */
value *int_value(int val) {
	value *tmp_value = calloc(1, sizeof(value));
	char temporary_name[10];
	sprintf(temporary_name, "t%d", t_count);
	tmp_value->identifier = temporary_name;
	tmp_value->value_type = VT_INTEGR;
	tmp_value->data.int_value = val;
	t_count++;
	return tmp_value;
}

/* ==== VALUE -> C TYPE UTILITIES ==== */
char *to_string(value *val) {
	if (val==NULL) return NULL;
	if (val->value_type!=VT_STRING) return NULL;
	return val->data.string_value;
}

int to_int(environment *env, value *val) {
	if (val==NULL) return UNDEFINED;
	if (val->value_type==VT_STRING && env) {
		/* It might be a variable that we should resolve */
		val = search(env, val->data.string_value, VT_INTEGR, VT_ANY, 1);
		if (!val) fatal("Integer value expected");
		return val->data.int_value;
	}
	else if (val->value_type==VT_INTEGR) {
		return val->data.int_value;		
	}
	fatal("Integer value expected");
	return UNDEFINED;
}