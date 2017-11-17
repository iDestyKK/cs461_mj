# include <stdio.h>
# include <stdlib.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"
# define MAXARGS 50
# define MAXLOCS 50

extern int lineno;
extern int ntmp;
extern int formalnum;
extern int localnum;
extern char formaltypes[MAXARGS];
extern char localtypes[MAXLOCS];
extern int localwidths[MAXLOCS];

int nlbl  = 0; //Global for number of labels
int ngoto = 0; //Glboal for number of gotos

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
 *                  at when printing (well, the first 7 characters of it).
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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: backpatch not implemented\n");
		return;
	#endif

	printf(
		#ifdef FUNC_LABEL
			"[BACKPAT] "
		#endif
		"B%d=L%d\n",

		//Parametre information
		p->s_place,k
	);
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

	//Thank you Dr. Jantz
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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: call not implemented\n");
		return ((struct sem_rec *) NULL);
	#endif
	
	//Linked List traversal... except we are at the end. Go to the front.
	//
	//Also, because we have links only going one way, we need to store pointer
	//information too.
	unsigned int     argc      = 0,
	                 i         = 0;
	struct sem_rec  *orig      = args;
	struct sem_rec **sem_array = NULL;

	//Get number of arguments.
	for (; args != NULL; args = args->back.s_link, argc++);

	//Okay... now let's put it in an array
	sem_array = (struct sem_rec**) malloc(sizeof(struct sem_rec*) * argc);
	args = orig;
	
	for (i = argc; i > 0; i--)
		sem_array[i - 1] = args, args = args->back.s_link;
	
	//Finally, print out the array of arguments.
	for (i = 0; i < argc; i++)
		printf(
			#ifdef FUNC_LABEL
				"[CALL   ] "
			#endif

			//Format String
			"arg%c t%d\n",
			
			//Type (Anything that isn't a double is "i" apparently...)
			(sem_array[i]->s_mode == T_DOUBLE) ? 'f' : 'i',

			sem_array[i]->s_place
		);

	//Now then... print out the function name.
	nexttemp();
	printf(
		#ifdef FUNC_LABEL
			"[CALL   ] "
		#endif
		"t%d := global %s\n",

		currtemp(),
		f
	);

	//Also, print out the "fi" statement which links the function and argc.
	nexttemp();
	printf(
		#ifdef FUNC_LABEL
			"[CALL   ] "
		#endif
		"t%d := fi t%d %d\n",

		currtemp(),
		currtemp() - 1, //Guaranteed to be the previous one
		argc
	);

	return node(currtemp(), T_PROC, NULL, NULL);
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
	
	//TODO: Finish?
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

	return node(currtemp(), T_INT, NULL, NULL);
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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: dofor not implemented\n");
		return;
	#endif

	backpatch(e2->back.s_true, m3);
	backpatch(e2->s_false    , m4);
	backpatch(n1             , m1);
	backpatch(n2             , m2);
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
		return;
	#endif
	
	/*printf(
		"[DOIF   ] INFO: %d %d\n",
		e->s_place,
		e->s_mode
	);*/

	//Straight from the slides...
	backpatch(e->back.s_true, m1);
	backpatch(e->s_false    , m2);
}

/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, int m1, struct sem_rec *n,
		int m2, int m3)
{
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: doifelse not implemented %d %d %d\n", m1, m2, m3);
		return;
	#endif

	//Again... straight from the slides.
	backpatch(e->back.s_true, m1);
	backpatch(e->s_false    , m2);
	backpatch(n             , m3);

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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: dowhile not implemented\n");
		return;
	#endif

	backpatch(e->back.s_true, m2);
	backpatch(e->s_false    , m3);
	backpatch(n             , m1);
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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: exprs not implemented\n");
		return ((struct sem_rec *) null);
	#endif

	//Build a list... pseudoly by linking l with e.
	/*printf(
		"INFO: %d %d\n",
		l->s_place,
		l->s_mode
	);
	printf(
		"INFO: %d %d\n",
		e->s_place,
		e->s_mode
	);*/

	//The language calls "exprs" args-1 number of times. Hence chaining like this.
	e->back.s_link = l;
	return e;
}

/*
 * fhead - beginning of function body
 */
void fhead(struct id_entry *p)
{
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: fhead not implemented\n");
		return;
	#endif

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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: fname not implemented\n");
		return ((struct id_entry *) NULL);
	#endif

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
}

/*
 * ftail - end of function body
 */
void ftail()
{
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: ftail not implemented\n");
		return;
	#endif
	leaveblock();
	printf("fend\n");

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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: indx not implemented\n");
		return ((struct sem_rec *) NULL);
	#endif
	
	//Because it's pissing me off enough, let's get rid of the T_ARRAY bit...
	unsigned char x_type = x->s_mode & 0xEF,
	              i_type = i->s_mode & 0xEF;

	if (i_type == T_DOUBLE) {
		//First have to convert if the array index isn't an integer (C Standard).
		nexttemp();
		printf(
			#ifdef FUNC_LABEL
				"[REL    ] "
			#endif
			"t%d := cvi t%d\n",

			//Temporary ID
			currtemp(),

			i->s_place
		);
	}
	
	//tX := tX []X tX
	nexttemp();
	printf(
		#ifdef FUNC_LABEL
			"[INDX   ] "
		#endif
		"t%d := t%d []%c t%d\n",
		
		//Current Temporary
		currtemp(),

		//Variable name
		x->s_place,

		//The type...
		(x_type == T_DOUBLE) ? 'f' : 'i',

		//Value inside the []'s
		(i_type == T_DOUBLE) ? currtemp() - 1 : i->s_place
	);

	return node(currtemp(), x_type, NULL, NULL);
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
	printf(
		#ifdef FUNC_LABEL
			"[M      ] "
		#endif
		"label L%d\n",
		nlbl
	);

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

	ngoto++;

	printf(
		#ifdef FUNC_LABEL
			"[N      ] "
		#endif
		"br B%d\n",

		ngoto
	);

	return node(ngoto, T_LBL, NULL, NULL);
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

	return node(currtemp(), y->s_mode, NULL, NULL);
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
	//printf("%d\n", nlbl);
	
	//Generate a sem_rec for the operation
	struct sem_rec* s = node(currtemp(), x->s_mode, NULL, NULL);
	
	
	//BT Statement (Branch on True)
	ngoto++;
	#ifdef FUNC_LABEL
		printf("[REL    ] bt t%d B%d\n", currtemp(), ngoto);
	#else
		printf("bt t%d B%d\n", currtemp(), ngoto);
	#endif
	
	//If the condition is true, we have to go somewhere. In this case, let's make
	//sure it knows to go to the "ngoto" node.
	s->back.s_true = node(ngoto, T_LBL, NULL, NULL);

	//BR (Unconditional Branch)
	ngoto++;
	#ifdef FUNC_LABEL
		printf("[REL    ] br B%d\n", ngoto);
	#else
		printf("br B%d\n", ngoto);
	#endif

	//If the condition is false... we have to go to... well... whatever wasn't the
	//last one. Therefore, let's make another sem_rec and point it to another
	//place.
	s->s_false = node(ngoto, T_LBL, NULL, NULL);

	//return ((struct sem_rec *) NULL);
	return s;
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
	#ifdef FUNC_NOTIM
		fprintf(stderr, "sem: startloopscope not implemented\n");
		return;
	#endif
	
	enterblock();
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

	return node(currtemp(), T_STR, NULL, NULL);
}
