#pragma once

//header.h

enum noh_type {PROGRAM, ASSIGN, SUM, MINUS, MULTI, DIVIDE, PRINT, POW, GENERIC, STMT, FLOAT, IDENT, INTEGER, PAREN};

struct noh {
	int id, childcount;
	enum noh_type type;

	double value;
	char *name;

	struct noh *children[1];
};

typedef struct noh noh;

noh *create_noh(enum noh_type nt, int children);

void print(noh *root);
void print_rec(FILE *f, noh *root);