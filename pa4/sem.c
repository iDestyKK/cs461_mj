# include <stdio.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"
# define MAXARGS 50
# define MAXLOCS 50

extern int lineno;
extern int nlbl;
extern int ntmp;
extern int formalnum;
extern int localnum;
extern char formaltypes[MAXARGS];
extern char localtypes[MAXLOCS];
extern int localwidths[MAXLOCS];

/*
 * DEBUG LABELS
 *
 * Set certain macros to be defined for various debugging modes. This is mainly
 * to help with printing out data that may be useful when finding errors in the
 * intermediate code generation.
 *
 * LABELS:
 *     FUNC_LABEL - Print out the function name along with each operation.
 *                  Useful because sometimes I don't know where the hell a line
 *                  of code breaks. This just says what function the program is
 *                  at when printing.
 *
 *     FUNC_NOTIM - Forces the functions to not be implemented and return the
 *                  "sem: X not implemented" message to be printed to stderr.
 */

#define FUNC_LABEL
//#define FUNC_NOTIM


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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: bgnstmt not implemented\n");
		return;
	#endif

	int c;
	static int laststmt = 0;

	skip();
	c = getchar();
	putbak(c);

	if (c != '}' && lineno != laststmt) {
		printf(
			#ifdef FUNC_LABEL
				"[BGNSTMT] bgnstmt %d\n",
			#else
				"bgnstmt %d\n",
			#endif

			lineno
		);
		laststmt = lineno;
	}
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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: con not implemented\n");
		return ((struct sem_rec *) NULL);
	#endif
	
	//TODO: Finish
	nexttemp();
	printf(
		#ifdef FUNC_LABEL
			"[CON    ] t%d := %s\n",
		#else
			"t%d := %s\n",
		#endif
		currtemp(),
		x
	);
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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: doif not implemented %d %d\n", m1, m2);
	#endif

	printf("[DOIF   ] B%d=L%d\n", m1, m1);
	printf("[DOIF   ] B%d=L%d\n", m2, m2);
	/*printf(
		"INFO: %d %d\n",
		e->s_place,
		e->s_mode
	);*/
}

/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, int m1, struct sem_rec *n,
		int m2, int m3)
{
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: doifelse not implemented %d %d %d\n", m1, m2, m3);
	#endif

	printf("[DOIFELS] B%d=L%d\n", m1, m1);
	printf("[DOIFELS] B%d=L%d\n", m2, m2);
	printf("[DOIFELS] B%d=L%d\n", m3, m3);
	/*printf(
		"INFO: %d %d\n",
		e->s_place,
		e->s_mode
	);*/
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
	FILE* fp = fopen("test.bin", "w");
	dump(1, fp);
	fclose(fp);
	//fprintf(stderr, "sem: ftail not implemented\n");
}

/*
 * id - variable reference
 */
struct sem_rec *id(char *x)
{
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: id not implemented\n");
		return ((struct sem_rec *) NULL);
	#endif

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
		#ifdef FUNC_LABEL
			(p->i_scope == GLOBAL) ?
				"[ID     ] t%d := %s %s\n":
				"[ID     ] t%d := %s %d\n",
		#else
			(p->i_scope == GLOBAL) ?
				"t%d := %s %s\n":
				"t%d := %s %d\n",
		#endif

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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: m not implemented\n");
		return (0);
	#endif
	
	nlbl++;
	printf("[M      ] label L%d\n", nlbl);

	return nlbl;
}

/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n()
{
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: n not implemented\n");
		return ((struct sem_rec *) NULL);
	#endif

	printf("[N      ] br B%d\n", nlbl + 2);
	return ((struct sem_rec *) NULL);
}

/*
 * op1 - unary operators
 */
struct sem_rec *op1(char *op, struct sem_rec *y)
{
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: op1 not implemented (%s)\n", op);
		return ((struct sem_rec *) NULL);
	#endif

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
		#ifdef FUNC_LABEL
			"[OP1    ] t%d := %s%c t%d\n",
		#else
			"t%d := %s%c t%d\n",
		#endif

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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: rel not implemented\n");
		return ((struct sem_rec *) NULL);
	#endif
	
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
			#ifdef FUNC_LABEL
				"[REL    ] t%d := cv%c t%d\n",
			#else
				"t%d := cv%c t%d\n",
			#endif

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
		#ifdef FUNC_LABEL
			"[REL    ] t%d := t%d %s%c t%d\n",
		#else
			"t%d := t%d %s%c t%d\n",
		#endif

		//Temporary ID
		currtemp(), 
		x->s_place,

		//Operator
		op,

		//The type to convert to
		(x->s_mode == T_INT)    ? 'i' :
		(x->s_mode == T_STR)    ? 'i' :
		(x->s_mode == T_DOUBLE) ? 'f' : 'i',

		currtemp() - 1
	);
	printf("[REL    ] bt t%d B%d\n", currtemp(), nlbl + 1);
	printf("[REL    ] br B%d\n", nlbl + 2);
	//return ((struct sem_rec *) NULL);
	return x;
}

/*
 * set - assignment operators
 */
struct sem_rec *set(char *op, struct sem_rec *x, struct sem_rec *y)
{
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: set not implemented\n");
		return ((struct sem_rec *) NULL);
	#endif
	
	//DEBUG: Print Out Info
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
			#ifdef FUNC_LABEL
				"[SET    ] t%d := cv%c t%d\n",
			#else
				"t%d := cv%c t%d\n",
			#endif

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
		#ifdef FUNC_LABEL
			"[SET    ] t%d := t%d =%c t%d\n",
		#else
			"t%d := t%d =%c t%d\n",
		#endif

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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: string not implemented\n");
		return ((struct sem_rec *) NULL);
	#endif

	//TODO: Finish
	nexttemp();
	printf(
		#ifdef FUNC_LABEL
			"[STRING ] t%d := %s\n",
		#else
			"t%d := %s\n",
		#endif

		currtemp(),
		s
	);
	return ((struct sem_rec *) NULL);
}
