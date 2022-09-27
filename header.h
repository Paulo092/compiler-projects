#pragma once

//header.h

enum noh_type {PROGRAM, ASSIGN, SUM, MINUS, MULTI, DIVIDE, PRINT, POW, GENERIC, STMT, FLOAT, IDENT, INTEGER, PAREN};

static const char *noh_type_names[] = {
	"program", "=", "+", "-", "*", "/", "print", "^", "generic", "stmt", "float", "identificador", "int", "()"
};

typedef struct {
	int intv;
	double dblv;

	char *ident;
} token_args;

struct noh {
	int id, childcount;
	enum noh_type type;

	int intv;
	double dblv;

	char *name;

	struct noh *children[1];
};

typedef struct noh noh;

noh *create_noh(enum noh_type nt, int children);

char * get_label(noh *root);

void print(noh *root);
void print_rec(FILE *f, noh *root);