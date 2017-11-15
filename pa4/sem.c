# include <stdio.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"
# define MAXARGS 50
# define MAXLOCS 50

extern int ntmp;
extern int formalnum;
extern int localnum;
extern char formaltypes[MAXARGS];
extern char localtypes[MAXLOCS];
extern int localwidths[MAXLOCS];

/*
 * backpatch - backpatch list of quadruples starting at p with k
 */
void backpatch(struct sem_rec *p, int k)
{
	fprintf(stderr, "sem: backpatch not implemented\n");
}

/*
 * bgnstmt - encountered the beginning of a statement
 */
void bgnstmt()
{
	extern int lineno;

	printf("bgnstmt %d\n", lineno);
	//   fprintf(stderr, "sem: bgnstmt not implemented\n");
}

/*
 * call - procedure invocation
 */
struct sem_rec *call(char *f, struct sem_rec *args)
{
	fprintf(stderr, "sem: call not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * ccand - logical and
 */
struct sem_rec *ccand(struct sem_rec *e1, int m, struct sem_rec *e2)
{
	fprintf(stderr, "sem: ccand not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * ccexpr - convert arithmetic expression to logical expression
 */
struct sem_rec *ccexpr(struct sem_rec *e)
{
	fprintf(stderr, "sem: ccexpr not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * ccnot - logical not
 */
struct sem_rec *ccnot(struct sem_rec *e)
{
	fprintf(stderr, "sem: ccnot not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * ccor - logical or
 */
struct sem_rec *ccor(struct sem_rec *e1, int m, struct sem_rec *e2)
{
	fprintf(stderr, "sem: ccor not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * con - constant reference in an expression
 */
struct sem_rec *con(char *x)
{
	//fprintf(stderr, "sem: con not implemented\n");
	//return ((struct sem_rec *) NULL);
	
	//TODO: Finish
	nexttemp();
	printf("[CON   ] t%d := %s\n", currtemp(), x);
	struct sem_rec* snum = node(currtemp(), T_INT, NULL, NULL);

	return snum;
}

/*
 * dobreak - break statement
 */
void dobreak()
{
	fprintf(stderr, "sem: dobreak not implemented\n");
}

/*
 * docontinue - continue statement
 */
void docontinue()
{
	fprintf(stderr, "sem: docontinue not implemented\n");
}

/*
 * dodo - do statement
 */
void dodo(int m1, int m2, struct sem_rec *e, int m3)
{
	fprintf(stderr, "sem: dodo not implemented\n");
}

/*
 * dofor - for statement
 */
void dofor(int m1, struct sem_rec *e2, int m2, struct sem_rec *n1,
		int m3, struct sem_rec *n2, int m4)
{
	fprintf(stderr, "sem: dofor not implemented\n");
}

/*
 * dogoto - goto statement
 */
void dogoto(char *id)
{
	fprintf(stderr, "sem: dogoto not implemented\n");
}

/*
 * doif - one-arm if statement
 */
void doif(struct sem_rec *e, int m1, int m2)
{
	fprintf(stderr, "sem: doif not implemented\n");
}

/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, int m1, struct sem_rec *n,
		int m2, int m3)
{
	fprintf(stderr, "sem: doifelse not implemented\n");
}

/*
 * doret - return statement
 */
void doret(struct sem_rec *e)
{
	fprintf(stderr, "sem: doret not implemented\n");
}

/*
 * dowhile - while statement
 */
void dowhile(int m1, struct sem_rec *e, int m2, struct sem_rec *n,
		int m3)
{
	fprintf(stderr, "sem: dowhile not implemented\n");
}

/*
 * endloopscope - end the scope for a loop
 */
void endloopscope(int m)
{
	fprintf(stderr, "sem: endloopscope not implemented\n");
}

/*
 * exprs - form a list of expressions
 */
struct sem_rec *exprs(struct sem_rec *l, struct sem_rec *e)
{
	if (l != NULL)
	printf(
		"INFO: %d %d\n",
		l->s_place,
		l->s_mode
	);
	printf(
		"INFO: %d %d\n",
		e->s_place,
		e->s_mode
	);
	fprintf(stderr, "sem: exprs not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * fhead - beginning of function body
 */
void fhead(struct id_entry *p)
{
	//fprintf(stderr, "sem: fhead not implemented\n");
	printf("func %s\n", p->i_name);
	unsigned int i;
	for (i = 0; i < formalnum; i++) {
		if (formaltypes[i] == 'f') {
			printf("formal 8\n");
		} else if (formaltypes[i] == 'i') {
			printf("formal 4\n");
		} else {
			yyerror("formal type somehow stored incorrectly");
		}
	}
	for (i = 0; i < localnum; i++) {
		if (localtypes[i] == 'f') {
			printf("localloc %d\n", 8 * localwidths[i]);
		} else if (localtypes[i] == 'i') {
			printf("localloc %d\n", 4 * localwidths[i]);
		} else {
			yyerror("formal type somehow stored incorrectly");
		}
	}
}

/*
 * fname - function declaration
 */
struct id_entry *fname(int t, char *id)
{
	struct id_entry *p;

	if ((p = lookup(id, 0)) == NULL) {
		p = install(id, 0);
	} else if (p->i_defined) {
		yyerror("procedure previously declared");
	} else if (p->i_type != t) {
		yyerror("function declaration types do not match");
	}

	p->i_type = t;
	p->i_scope = GLOBAL;
	p->i_defined = 1;
	enterblock();
	formalnum = 0;
	localnum = 0;

	return p;
	//fprintf(stderr, "sem: fname not implemented\n");
	//return ((struct id_entry *) NULL);
}

/*
 * ftail - end of function body
 */
void ftail()
{
	exit_block();
	printf("fend\n");
	//fprintf(stderr, "sem: ftail not implemented\n");
}

/*
 * id - variable reference
 */
struct sem_rec *id(char *x)
{
	//fprintf(stderr, "sem: id not implemented\n");
	//return ((struct sem_rec *) NULL);
	struct id_entry* p = lookup(x, 0);
	extern int lineno;
	
	if (p == NULL) {
		printf(" undeclared identifier.  Line %d\n", lineno);
		p = install(x, 0);
		//return (struct sem_rec*) NULL;
	}

	//DEBUG
	/*
	printf(
		"INFO: %s - %d %d %d %d %d %d\n",
		x,
		p->i_type,
		p->i_blevel,
		p->i_defined,
		p->i_width,
		p->i_scope,
		p->i_offset
	);
	*/
	
	nexttemp();
	struct sem_rec* snum = node(currtemp(), p->i_type, NULL, NULL);

	//Print out information
	printf(
		(p->i_scope == GLOBAL) ?
			"[ID    ] t%d := %s %s\n":
			"[ID    ] t%d := %s %d\n",

		//Temporary Number
		snum->s_place,

		//Truly disgusting ternary statements to determine what to print...
		//...inside printf
		(p->i_scope == LOCAL) ?
			"local":
		(p->i_scope == PARAM) ?
			"param":
			"global", //Must be "GLOBAL" at this point...

		//ID/Offset, or the global name IF it's a global
		(p->i_scope == GLOBAL) ?
			x :
			p->i_offset
	);



	return snum;
}

/*
 * indx - subscript
 */
struct sem_rec *indx(struct sem_rec *x, struct sem_rec *i)
{
	fprintf(stderr, "sem: indx not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * labeldcl - process a label declaration
 */
void labeldcl(char *id)
{
	fprintf(stderr, "sem: labeldcl not implemented\n");
}

/*
 * m - generate label and return next temporary number
 */
int m()
{
	fprintf(stderr, "sem: m not implemented\n");
	return (0);
}

/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n()
{
	fprintf(stderr, "sem: n not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * op1 - unary operators
 */
struct sem_rec *op1(char *op, struct sem_rec *y)
{
	//fprintf(stderr, "sem: op1 not implemented (%s)\n", op);
	//return ((struct sem_rec *) NULL);
	if (y == NULL)
		return ((struct sem_rec *) NULL);

	//DEBUG
	/*printf(
		"INFO: %s - %d %d\n",
		op,
		y->s_place,
		y->s_mode
	);*/

	//But wait, now let's also make another temp number and have it store the type
	nexttemp();

	//Print...
	printf(
		"[OP1   ] t%d := %s%c t%d\n",

		//Temporary Number
		currtemp(),

		//Operator String
		op,

		//Again. I like my ternaries
		(y->s_mode == T_INT)    ? 'i' :
		(y->s_mode == T_STR)    ? 'i' :
		(y->s_mode == T_DOUBLE) ? 'f' : 'i',

		//sem_rec number
		y->s_place
	);
	struct sem_rec* snum = node(currtemp(), y->s_mode, NULL, NULL);

	return snum;
}

/*
 * op2 - arithmetic operators
 */
struct sem_rec *op2(char *op, struct sem_rec *x, struct sem_rec *y)
{
	fprintf(stderr, "sem: op2 not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * opb - bitwise operators
 */
struct sem_rec *opb(char *op, struct sem_rec *x, struct sem_rec *y)
{
	fprintf(stderr, "sem: opb not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * rel - relational operators
 */
struct sem_rec *rel(char *op, struct sem_rec *x, struct sem_rec *y)
{
	fprintf(stderr, "sem: rel not implemented\n");
	return ((struct sem_rec *) NULL);
}

/*
 * set - assignment operators
 */
struct sem_rec *set(char *op, struct sem_rec *x, struct sem_rec *y)
{
	//fprintf(stderr, "sem: set not implemented\n");
	//return ((struct sem_rec *) NULL);
	
	//TODO: Implement some way to handle x = y = z
	//set(op, x, y);

	/*printf(
		"INFO: %s - %d %d\n",
		op,
		x->s_place,
		x->s_mode
	);
	printf(
		"INFO: %s - %d %d\n",
		op,
		y->s_place,
		y->s_mode
	);*/
	if (x->s_mode != y->s_mode) {
		nexttemp();
		printf(
			"[SET   ] t%d := cv%c %d\n",

			//Temporary ID
			currtemp(),

			//The type to convert to
			(x->s_mode == T_INT)    ? 'i' :
			(x->s_mode == T_STR)    ? 'i' :
			(x->s_mode == T_DOUBLE) ? 'f' : 'i',

			//y->s_place
			currtemp() - 1
		);
	}
	nexttemp();
	printf(
		"[SET   ] t%d := t%d =%c t%d\n",

		//Temporary ID
		currtemp(), 
		x->s_place,

		//The type to convert to
		(x->s_mode == T_INT)    ? 'i' :
		(x->s_mode == T_STR)    ? 'i' :
		(x->s_mode == T_DOUBLE) ? 'f' : 'i',

		currtemp() - 1
	);
	//return ((struct sem_rec *) NULL);
	return x;
}

/*
 * startloopscope - start the scope for a loop
 */
void startloopscope()
{
	fprintf(stderr, "sem: startloopscope not implemented\n");
}

/*
 * string - generate code for a string
 */
struct sem_rec *string(char *s)
{
	//fprintf(stderr, "sem: string not implemented\n");
	//TODO: Finish
	nexttemp();
	printf("[STRING] t%d := %s\n", currtemp(), s);
	return ((struct sem_rec *) NULL);
}
