//header.h

#include <stdlib.h>
#include <stdio.h>

#include "header.h"

noh *create_noh(enum noh_type nt, int children) {
	static int IDCOUNT = 0;
	noh *newn = (noh*)calloc(1, 
		sizeof(noh)+
		sizeof(noh*)*(children-1));
	
	newn->type = nt;
	newn->childcount = children;
	newn->id = IDCOUNT++;
	
	return newn;
}

char * get_label(noh *noh) {
	static char aux[100];
	switch(noh->type) {
		case INTEGER:
			sprintf(aux, "%d", noh->intv);
			return aux;
		case FLOAT:
			sprintf(aux, "%f", noh->dblv);
			return aux;
		case IDENT:
			return noh->name;
		default:
			// return noh_type_names[noh->type];
			return (char *) noh_type_names[noh->type];
	}
}

void print(noh *root) {
	FILE *f = fopen("output.dot", "w");

	fprintf(f, "graph {\n");
	print_rec(f, root);
	fprintf(f, "}");

	fclose(f);
}

void print_rec(FILE *f, noh *root) {
	fprintf(f, "\tN%d[label=\"%s\"];\n", root->id, get_label(root));
	for (int i = 0; i < root->childcount; i++) {
		print_rec(f, root->children[i]);
		fprintf(f, "\tN%d -- N%d;\n", root->id, root->children[i]->id);
	}
}

int search_symbol(char *nome){
	// busca linear, nao eficiente
	for(int i = 0; i < simbolo_qnt; i++){
		if(strcmp(tsimbolos[i].nome, nome) == 0)
			return i;
	}

	return -1;
}

void check_declared_vars(noh **root, noh *no) {
	noh *nr = *root;

	if(no->type == ASSIGN) {
		int s = search_symbol(no->children[0]->name);
		if(s != -1) tsimbolos[s].exists = true;
	}
}

void visitor_leaf_first(noh ** root, visitor_action act) {
	noh *r = *root;

	for(int i = 0; i < r->childcount; i++) {
		visitor_leaf_first(&r->children[i], act);
		if(act != NULL) act(root, r->children[i]);
	}
}