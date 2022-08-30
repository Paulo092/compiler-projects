%{
	#include <stdio.h>
%}

%option yylineno

L	[a-zA-Z_]
N 	[0-9]

%%

"print"					{ printf("TOK_MOSTRA\n"); }

"+"						{ printf("TOK_MAIS\n"); }
"-"						{ printf("TOK_MENOS\n"); }
"="						{ printf("TOK_IGUAL\n"); }
"*"						{ printf("TOK_MULTIPL\n"); }
"/"						{ printf("TOK_DIVIDER\n"); }
"("						{ printf("TOK_ABRE_PARENTESES\n"); }
")"						{ printf("TOK_FECHA_PARENTESES\n"); }

{N}+					{ printf("TOK_INTEIRO<%s>\n", yytext); }
{N}+\.{N}+				{ printf("TOK_REAL<%s>\n", yytext); }
{L}({L}|{N})*			{ printf("TOK_LITERAL<%s>\n", yytext); }

.						{ printf("TOK_INVALIDO: %c\n", yytext[0]); }

%%

int main(int argc, char *argv[]) {
	if(argc <= 1) {
		printf("%s [file]\n", argv[0]);
		return 1;
	}
	
	FILE *f = fopen(argv[1], "r");
	
	// Informa o arquivo que será compilado (f)
	yyin = f;
	
	// Compila
	yylex();
	
	fclose(f);
	
	return 0;
}

