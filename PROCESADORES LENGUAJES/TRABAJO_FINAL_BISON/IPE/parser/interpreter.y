/*! 
  \file interpreter.y
  \brief Grammar file
*/


%{
#include <iostream>
#include <string>

/*******************************************/
/* NEW in example 5 */
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* NEW in example 6 */
/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"


/*******************************************/
/* 
  NEW in example 16
  AST class
  IMPORTANT: this file must be before init.hpp
*/
#include "../ast/ast.hpp"


/*******************************************/
/* NEW in example 7 */
/* Table of symbol */
#include "../table/table.hpp"
/*******************************************/

/*******************************************/
#include "../table/numericVariable.hpp"
/*******************************************/

/* NEW in example 15 */
#include "../table/logicalVariable.hpp"

/*******************************************/
/* NEW in example 11 */
#include "../table/numericConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 15 */
#include "../table/logicalConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 13 */
#include "../table/builtinParameter1.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 14 */
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
/*******************************************/

#include "../table/cadenaVariable.hpp"
/*******************************************/
/* NEW in example 10 */
#include "../table/init.hpp"
/*******************************************/

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

extern int lineNumber; //!< External line counter

/* NEW in example 15 */
extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter


/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  Program name
/***********************************************************/

/*******************************************/
/* NEW in example 6 */
/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 
/*******************************************/


/*******************************************/
/* NEW in example 7 */
extern lp::Table table; //!< Extern Table of Symbols
extern int control; //!< Variable Control the interactive mode of execution of the interpreter

/*******************************************/
/* NEW in example 16 */
extern lp::AST *root; //!< External root of the abstract syntax tree AST

%}



/* In case of a syntactic error, more information is shown */
%error-verbose

/* Initial grammar symbol */
%start program

/*******************************************/
/* Data type YYSTYPE  */
/* NEW in example 4 */
%union {
  char * identifier; 				 
  double number;  
  bool logic;						 
  lp::ExpNode *expNode;  			 
  std::list<lp::ExpNode *>  *parameters;    
  std::list<lp::Statement *> *stmts; 
  lp::Statement *st;				 
  lp::AST *prog;					 
  char *cadena;
}

/* Type of the non-terminal symbols */

%type <expNode> exp cond 


%type <parameters> listOfExp  restOfListOfExp

%type <stmts> stmtlist


%type <st> stmt asgn print read if while read_string print_string repeat for

%type <prog> program

// Defined token 

/* Minimum precedence */

/*******************************************/

%token SEMICOLON
/*******************************************/

 
%token PRINT READ IF ELSE WHILE DO END_WHILE READ_STRING PRINT_STRING THEN END_IF REPEAT UNTIL FOR SINCE END_FOR STEP BORRAR LUGAR


%token LETFCURLYBRACKET RIGHTCURLYBRACKET


%right ASSIGNMENT


%token COMMA

/*******************************************/

%token <number> NUMBER
/*******************************************/
%token <cadena> CADENA
/*******************************************/

%token <logic> BOOL
/*******************************************/


%token <identifier> VARIABLE UNDEFINED CONSTANT BUILTIN

/* Left associativity */

/*******************************************************/

%left OR

%left AND

%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN  EQUAL NOT_EQUAL

%left NOT
/*******************************************************/


%left PLUS MINUS CONCAT


%left MULTIPLICATION DIVISION_ENTERA DIVISION MODULO

%left LPAREN RPAREN

%nonassoc  UNARY

// Maximum precedence 

%right POWER

%%
//! \name Grammar rules



program : stmtlist
		  { 
		    // Create a new AST
			$$ = new lp::AST($1); 

			// Assign the AST to the root
			root = $$; 

			// End of parsing
			//	return 1;
		  }
;

stmtlist:  /* empty: epsilon rule */
		  { 
			// create a empty list of statements
			$$ = new std::list<lp::Statement *>(); 
		  }  

        | stmtlist stmt 
		  { 
			// copy up the list and add the stmt to it
			$$ = $1;
			$$->push_back($2);

			// Control the interative mode of execution of the interpreter
			if (interactiveMode == true && control==0)   //Aqui hay que controlar con una variable control=0
 			   $2->evaluate();
           }


        | stmtlist error 
           { 
			// just copy up the stmtlist when an error occurs
			$$ = $1;

			// The previous look-ahead token ought to be discarded with `yyclearin;'
			yyclearin; 
           } 
;
 

stmt: SEMICOLON  /* Empty statement: ";" */
	  {
		// Create a new empty statement node
		$$ = new lp::EmptyStmt(); 
	  }
	| asgn  SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| print SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| read SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	/*  NEW in example 17 */
	| if 
	 {
		// Default action
		// $$ = $1;
	 }
	/*  NEW in example 17 */
	| while 
	 {
		// Default action
		// $$ = $1;
	 }
	/*  NEW in example 17 */
	/*| block 
	 {
		// Default action
		// $$ = $1;
	 }
	 */
	 /*read_string*/
	 | read_string SEMICOLON
	  {
	   
	  }
	 
	 | print_string SEMICOLON
	 	{
	 	
	 	}
	| repeat
		{
		
		}
		
	| for
		{
		
		}
		
	| BORRAR SEMICOLON
		{
			$$ = new lp::BorrarStmt();
		}
	| LUGAR LPAREN exp COMMA exp RPAREN SEMICOLON
		{
		$$ = new lp::LugarStmt($3,$5);
		}
;



	
if:	/* Simple conditional statement */
	IF cond THEN stmtlist END_IF
    {
		// Create a new if statement node
		$$ = new lp::IfStmt($2, $4);
		 
    }

	/* Compound conditional statement */
	| IF cond THEN stmtlist ELSE stmtlist END_IF
	 {
		// Create a new if statement node
		$$ = new lp::IfStmt($2, $4, $6);
	 }
;
repeat:	REPEAT stmtlist UNTIL cond 
	{
		$$ = new lp::RepeatStmt($4,$2);
	}
;

while:  	WHILE cond DO stmtlist END_WHILE 
		{
			// Create a new while statement node
			$$ = new lp::WhileStmt($2, $4);
       	}
;

for:	 	 FOR VARIABLE SINCE exp UNTIL exp DO stmtlist END_FOR

		{
			$$ = new lp::ForStmt($2,$4,$6,$8);
		}
		
		| FOR VARIABLE SINCE exp UNTIL exp STEP exp DO stmtlist END_FOR
		
		{
			$$ = new lp::ForStmt($2,$4,$6,$8, $10);
		}
;



cond: 	LPAREN exp RPAREN
		{ 
			$$ = $2;
		}
;


asgn:   VARIABLE ASSIGNMENT exp 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, $3);
		}

	|  VARIABLE ASSIGNMENT asgn 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, (lp::AssignmentStmt *) $3);
		}


	| CONSTANT ASSIGNMENT exp 
		{   
 			execerror("Semantic error in assignment: it is not allowed to modify a constant ", $1);
		}

	| CONSTANT ASSIGNMENT asgn 
		{   
 			execerror("Semantic error in multiple assignment: it is not allowed to modify a constant ",$1);
		}
;


print:  PRINT exp 
		{
			// Create a new print node
			 $$ = new lp::PrintStmt($2);
		}
;	

print_string:	PRINT_STRING exp
		{
			$$ = new lp::print_stringStmt($2);
		} 
;

read:  READ LPAREN VARIABLE RPAREN  
		{
			// Create a new read node
			
			 $$ = new lp::ReadStmt($3);
		}


	| READ LPAREN CONSTANT RPAREN  
		{   
 			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",$3);
		}
;
//*****************************************************************************
read_string:	READ_STRING LPAREN VARIABLE RPAREN
		{
			//Create a new read node
			
			$$ = new lp::read_stringStmt($3);
		
		}
		

	| READ_STRING LPAREN CONSTANT RPAREN  
		{   
 			execerror("Semantic error in \"read_string statement\": it is not allowed to modify a constant ",$3);
		}
;
//*********************************************************************************


exp:	
	CADENA
		{
			$$ = new lp::CadenaNode($1);
		}
	
	|
	exp CONCAT exp
		{
			$$ = new lp::ConcatNode($1,$3);
		}
	|
	NUMBER 
		{ 
			// Create a new number node
			$$ = new lp::NumberNode($1);
		}
		
	
	| 	exp PLUS exp 
		{ 
			// Create a new plus node
			 $$ = new lp::PlusNode($1, $3);
		 }

	| 	exp MINUS exp
      	{
			// Create a new minus node
			$$ = new lp::MinusNode($1, $3);
		}

	| 	exp MULTIPLICATION exp 
		{ 
			// Create a new multiplication node
			$$ = new lp::MultiplicationNode($1, $3);
		}

	| 	exp DIVISION exp
		{
		  // Create a new division node	
		  $$ = new lp::DivisionNode($1, $3);
	   }
	   
	 | 	exp DIVISION_ENTERA exp
	 	{
	 		$$ = new lp::DivisionEnteraNode($1, $3);
	 	}

	| 	LPAREN exp RPAREN
       	{ 
		    // just copy up the expression node 
			$$ = $2;
		 }

  	| 	PLUS exp %prec UNARY
		{ 
		  // Create a new unary plus node	
  		  $$ = new lp::UnaryPlusNode($2);
		}

	| 	MINUS exp %prec UNARY
		{ 
		  // Create a new unary minus node	
  		  $$ = new lp::UnaryMinusNode($2);
		}

	|	exp MODULO exp 
		{
		  // Create a new modulo node	

		  $$ = new lp::ModuloNode($1, $3);
       }

	|	exp POWER exp 
     	{ 
		  // Create a new power node	
  		  $$ = new lp::PowerNode($1, $3);
		}

	 | VARIABLE
		{
		  // Create a new variable node	
		  $$ = new lp::VariableNode($1);
		}

	 | CONSTANT
		{
		  // Create a new constant node	
		  $$ = new lp::ConstantNode($1);

		}

	| BUILTIN LPAREN listOfExp RPAREN
		{
			// Get the identifier in the table of symbols as Builtin
			lp::Builtin *f= (lp::Builtin *) table.getSymbol($1);

			// Check the number of parameters 
			if (f->getNParameters() ==  (int) $3->size())
			{
				switch(f->getNParameters())
				{
					case 0:
						{
							// Create a new Builtin Function with 0 parameters node	
							$$ = new lp::BuiltinFunctionNode_0($1);
						}
						break;

					case 1:
						{
							// Get the expression from the list of expressions
							lp::ExpNode *e = $3->front();

							// Create a new Builtin Function with 1 parameter node	
							$$ = new lp::BuiltinFunctionNode_1($1,e);
						}
						break;

					case 2:
						{
							// Get the expressions from the list of expressions
							lp::ExpNode *e1 = $3->front();
							$3->pop_front();
							lp::ExpNode *e2 = $3->front();

							// Create a new Builtin Function with 2 parameters node	
							$$ = new lp::BuiltinFunctionNode_2($1,e1,e2);
						}
						break;

					default:
				  			 execerror("Syntax error: too many parameters for function ", $1);
				} 
			}
			else
	  			 execerror("Syntax error: incompatible number of parameters for function", $1);
		}

	| exp GREATER_THAN exp
	 	{
		  // Create a new "greater than" node	
 			$$ = new lp::GreaterThanNode($1,$3);
		}

	| exp GREATER_OR_EQUAL exp 
	 	{
		  // Create a new "greater or equal" node	
 			$$ = new lp::GreaterOrEqualNode($1,$3);
		}

	| exp LESS_THAN exp 	
	 	{
		  // Create a new "less than" node	
 			$$ = new lp::LessThanNode($1,$3);
		}

	| exp LESS_OR_EQUAL exp 
	 	{
		  // Create a new "less or equal" node	
 			$$ = new lp::LessOrEqualNode($1,$3);
		}

	| exp EQUAL exp 	
	 	{
		  // Create a new "equal" node	
 			$$ = new lp::EqualNode($1,$3);
		}

    | exp NOT_EQUAL exp 	
	 	{
		  // Create a new "not equal" node	
 			$$ = new lp::NotEqualNode($1,$3);
		}

    | exp AND exp 
	 	{
		  // Create a new "logic and" node	
 			$$ = new lp::AndNode($1,$3);
		}

    | exp OR exp 
	 	{
		  // Create a new "logic or" node	
 			$$ = new lp::OrNode($1,$3);
		}

    | NOT exp 
	 	{
		  // Create a new "logic negation" node	
 			$$ = new lp::NotNode($2);
		}
;


listOfExp: 
			/* Empty list of numeric expressions */
			{
			    // Create a new list STL
				$$ = new std::list<lp::ExpNode *>(); 
			}

	|  exp restOfListOfExp
			{
				$$ = $2;

				// Insert the expression in the list of expressions
				$$->push_front($1);
			}
;

restOfListOfExp:
			/* Empty list of numeric expressions */
			{
			    // Create a new list STL
				$$ = new std::list<lp::ExpNode *>(); 
			}

		|	COMMA exp restOfListOfExp
			{
				// Get the list of expressions
				$$ = $3;

				// Insert the expression in the list of expressions
				$$->push_front($2);
			}
;



%%



