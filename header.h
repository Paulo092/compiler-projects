#pragma once

//header.h
#include <stdbool.h>
#include <string.h>

enum noh_type {PROGRAM, ASSIGN, SUM, MINUS, MULTI, DIVIDE, PRINT, POW, GENERIC, STMT, FLOAT, IDENT, INTEGER, PAREN};

static const char *noh_type_names[] = {
	"program", "=", "+", "-", "*", "/", "print", "^", "generic", "stmt", "float", "identificador", "int", "()"
};

typedef struct {
	int intv;
	double dblv;

	char *ident;
} token_args;

typedef struct {
	char *nome;
	int token;
    bool exists;
} simbolo;

static int simbolo_qnt = 0;
static simbolo tsimbolos[100];
simbolo *simbolo_novo(char *nome, int token);
bool simbolo_existe(char *nome);
void debug();

struct noh {
	int id, childcount;
	enum noh_type type;

	int intv;
	double dblv;

	char *name;

	struct noh *children[1];
};

typedef struct noh noh;

typedef void (*visitor_action)(noh **root, noh *no);

void check_declared_vars(noh **root, noh *no);

void visitor_leaf_first(noh ** root, visitor_action act);

noh *create_noh(enum noh_type nt, int children);

char * get_label(noh *root);

void print(noh *root);
void print_rec(FILE *f, noh *root);