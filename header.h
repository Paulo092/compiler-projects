#pragma once

//header.h

enum noh_type {PROGRAM, ASSIGN, SUM, MINUS, MULTI, DIVIDE, PRINT, POW};

struct noh {
	int id, childcount;
	enum noh_type type;
	
	struct noh *children[1];
};

typedef struct noh noh;
