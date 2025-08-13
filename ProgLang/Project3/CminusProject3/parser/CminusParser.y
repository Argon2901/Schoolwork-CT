/*******************************************************/
/*                     Cminus Parser                   */
/*                                                     */
/*******************************************************/

/*********************DEFINITIONS***********************/
%{
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <util/general.h>
#include <util/symtab.h>
#include <util/symtab_stack.h>
#include <util/dlink.h>
#include <util/string_utils.h>

#define SYMTABLE_SIZE 100
#define SYMTAB_VALUE_FIELD     "value"

/*********************EXTERNAL DECLARATIONS***********************/

EXTERN(void,Cminus_error,(const char*));

EXTERN(int,Cminus_lex,(void));

char *fileName;

SymTable symtab;
//SymTable symtab_globle;

extern int Cminus_lineno;

extern FILE *Cminus_in;

DLinkList list;
DLinkList strCnstList;

char* tempString;
char* registers;
//DLinkNode* tempNode;
int spOffset = 0;
int gpOffset = 0;
int stringCnstCount = 0;
int labelCount = 0;

char storingToGlobal = 1;

enum syscalls{
	PRINT_I = 1,
	PRINT_F = 2,
	PRINT_D = 3,
	PRINT_S = 4,
	READ_I = 5,
	READ_F = 6,
	READ_D = 7,
	READ_S = 8,
	MEM_ALLOC = 9,
	EXIT_CALL = 10,
	PRINT_C = 11,
	READ_C = 12
};

char getAvailableRegister();
void freeRegister(char);
void linkStringConstants(DLinkList*, DLinkList*);
void dumpList(DLinkList*);

%}

%name-prefix="Cminus_"
%defines

%union{
	char reg;
	char* string;
	int offset; 
	int index;
	int value;
}

%start Program

%token AND
%token ELSE
%token EXIT
%token FOR
%token IF 		
%token INTEGER 
%token NOT 		
%token OR 		
%token READ
%token WHILE
%token WRITE
%token LBRACE
%token RBRACE
%token LE
%token LT
%token GE
%token GT
%token EQ
%token NE
%token ASSIGN
%token COMMA
%token SEMICOLON
%token LBRACKET
%token RBRACKET
%token LPAREN
%token RPAREN
%token PLUS
%token TIMES
%token IDENTIFIER
%token DIVIDE
%token RETURN
%token STRING	
%token INTCON
%token MINUS

%left OR
%left AND
%left NOT
%left LT LE GT GE NE EQ
%left PLUS MINUS
%left TIMES DIVDE

%type <value> INTCON
%type <reg> Constant Factor MulExpr AddExpr SimpleExpr Expr Variable
%type <index> StringConstant TestAndThen Test CompoundStatement WhileStatement WhileToken WhileExpr

%type <string> STRING IDENTIFIER


/***********************PRODUCTIONS****************************/
%%
   Program		: Procedures 
		{
			sprintf(tempString, "li $v0, %d\nsyscall\n", EXIT_CALL);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			//create data section for string constants 

			sprintf(tempString, ".text\n");
			dlinkInsertBefore(dlinkNodeAlloc(strdup(tempString)), dlinkHead(&list));

			sprintf(tempString, "newl: .asciiz \"\\n\"\n");
			dlinkPush(dlinkNodeAlloc(strdup(tempString)), &list);

			linkStringConstants(&list, &strCnstList);

			sprintf(tempString, ".data\n");
			dlinkInsertBefore(dlinkNodeAlloc(strdup(tempString)), dlinkHead(&list));
			
			dumpList(&list);

			//printf("<Program> -> <Procedures>\n");
		}
	  	| DeclList Procedures //global variables, program start
		{
			
			sprintf(tempString, "li $v0, %d\nsyscall\n", EXIT_CALL);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			//create data section for string constants 

			sprintf(tempString, ".text\n");
			dlinkInsertBefore(dlinkNodeAlloc(strdup(tempString)), dlinkHead(&list));

			sprintf(tempString, "newl: .asciiz \"\\n\"\n");
			dlinkPush(dlinkNodeAlloc(strdup(tempString)), &list);

			linkStringConstants(&list, &strCnstList);

			sprintf(tempString, ".data\n");
			dlinkInsertBefore(dlinkNodeAlloc(strdup(tempString)), dlinkHead(&list));
			
			dumpList(&list);

			//printf("<Program> -> <DeclList> <Procedures>\n");
		}
          ;

Procedures 	: ProcedureDecl Procedures
		{
			//printf("<Procedures> -> <ProcedureDecl> <Procedures>\n");
		}
	   	|
		{
			//printf("<Procedures> -> epsilon\n");
		}
	   	;

ProcedureDecl : ProcedureHead ProcedureBody
		{
			//printf("<ProcedureDecl> -> <ProcedureHead> <ProcedureBody>\n");
		}
              ;

ProcedureHead : FunctionDecl DeclList //int main(){ int a,b,c;
		{
			//printf("<ProcedureHead> -> <FunctionDecl> <DeclList>\n");
		}
	      | FunctionDecl //int main(){
		{
			//printf("<ProcedureHead> -> <FunctionDecl>\n");
		}
              ;

FunctionDecl :  Type IDENTIFIER LPAREN RPAREN LBRACE 
		{
			sprintf(tempString, ".globl main\nmain :\n");
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			//printf("<FunctionDecl> ->  <Type> <IDENTIFIER> <LP> <RP> <LBR>\n"); 
		}
	      	;

ProcedureBody : StatementList RBRACE //codeblock }
		{
			//printf("<ProcedureBody> -> <StatementList> <RBR>\n");
		}
	      ;


DeclList 	: Type IdentifierList  SEMICOLON 
		{
			storingToGlobal = 0;
			//printf("<DeclList> -> <Type> <IdentifierList> <SC>\n");
		}		
	   	| DeclList Type IdentifierList SEMICOLON
	 	{
			//printf("<DeclList> -> <DeclList> <Type> <IdentifierList> <SC>\n");
	 	}
          	;


IdentifierList 	: VarDecl  
		{

			//printf("<IdentifierList> -> <VarDecl>\n");
		}
						
                | IdentifierList COMMA VarDecl
		{
			//printf("<IdentifierList> -> <IdentifierList> <CM> <VarDecl>\n");
		}
                ;

VarDecl 	: IDENTIFIER
		{ 
			int index = SymIndex(symtab, $1);
			int* offset = malloc(4);
			*offset = gpOffset;
			SymPutFieldByIndex(symtab, index, SYMTAB_VALUE_FIELD, offset);
			gpOffset += 4;
		}
		| IDENTIFIER LBRACKET INTCON RBRACKET //array declaration 
        {
			int index = SymIndex(symtab, $1);
			int* offset = malloc(4);
			
			*offset = gpOffset;
			SymPutFieldByIndex(symtab, index, SYMTAB_VALUE_FIELD, offset);
			gpOffset += $3 * 4;
			
			//printf("<VarDecl> -> <IDENTIFIER> <LBK> <INTCON> <RBK>\n");
		}
		;

Type     	: INTEGER 
		{ 
			//printf("<Type> -> <INTEGER>\n");
		}
                ;

Statement 	: Assignment
		{ 
			//printf("<Statement> -> <Assignment>\n");
		}
                | IfStatement
		{ 
			//printf("<Statement> -> <IfStatement>\n");
		}
		| WhileStatement
		{ 
			//printf("<Statement> -> <WhileStatement>\n");
		}
                | IOStatement 
		{ 
			//printf("<Statement> -> <IOStatement>\n");
		}
		| ReturnStatement
		{ 
			//printf("<Statement> -> <ReturnStatement>\n");
		}
		| ExitStatement	
		{ 
			//printf("<Statement> -> <ExitStatement>\n");
		}
		| CompoundStatement
		{ 
			//printf("<Statement> -> <CompoundStatement>\n");
		}
                ;

Assignment      : Variable ASSIGN Expr SEMICOLON
		{
			
			if($1  < 0){
				sprintf(tempString,
							"sw $%d, 0($%d)\n"
							, $3, $1);
			} else{
				sprintf(tempString,
							"sw $%d, 0($%d)\n"
							, $3, $1);
			}
			
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			freeRegister($3);
			freeRegister($1);
			//setValue($1, $3);
		}
                ;
				
IfStatement	: IF TestAndThen ELSE CompoundStatement
		{
			sprintf(tempString, "L%d:\n", $2); //after if statement
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
		}
		| IF TestAndThen
		{
			sprintf(tempString, "L%d:\n", $2); //after if statement
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
		}
		;
		
				
TestAndThen	: Test CompoundStatement
		{
			$$ = labelCount; 
			sprintf(tempString, "j L%d\n", labelCount);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			sprintf(tempString, "L%d:\n", $1); //after if statement
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			labelCount += 1;
		}
		;
				
Test		: LPAREN Expr RPAREN //returns label 
		{
			$$ = labelCount;

			sprintf(tempString, "beq $%d $0 L%d\n", $2	, labelCount);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($2);
			labelCount += 1;
		}
		;
	

WhileStatement  : WhileToken WhileExpr Statement
		{
			sprintf(tempString, "j L%d\n", $1); //after if statement
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			sprintf(tempString, "L%d:\n", $2); //after if statement
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
		}
                ;
                
WhileExpr	: LPAREN Expr RPAREN
		{
			$$ = labelCount;

			sprintf(tempString, "beq $%d $0 L%d\n", $2, labelCount); 
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			labelCount += 1;

			freeRegister($2);
		}
		;
				
WhileToken	: WHILE
		{
			$$ = labelCount;
			sprintf(tempString, "L%d:\n", labelCount);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			labelCount += 1; 

			//printf("<WhileToken> -> <WHILE>\n");
		}
		;


IOStatement     : READ LPAREN Variable RPAREN SEMICOLON
		{
			//char r = getAvailableRegister();
			if($3 < 0){
				sprintf(tempString,
							"li $v0, %d\n"
							"syscall\n"
							"sw $v0, 0($%d)\n"
							, READ_I, $3);
			} else{
				sprintf(tempString,
							"li $v0, %d\n"
							"syscall\n"
							"sw $v0, 0($%d)\n"
							, READ_I, $3);
			}
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			freeRegister($3);
		}
                | WRITE LPAREN Expr RPAREN SEMICOLON
		{

			sprintf(tempString, "move $a0, $%d\nli $v0 %d\nsyscall\nla $a0, newl\nli $v0, %d\nsyscall\n", $3, PRINT_I, PRINT_S);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			freeRegister($3);

		}
                | WRITE LPAREN StringConstant RPAREN SEMICOLON         
		{
			sprintf(tempString, "la $a0, S%d\nli $v0, %d\nsyscall\nla $a0, newl\nsyscall\n", $3, PRINT_S);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

		 	//printf("%s\n", (char *)SymGetFieldByIndex(symtab,$3, SYM_NAME_FIELD));
			//printf("<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>\n");
		}
                ;

ReturnStatement : RETURN Expr SEMICOLON
		{
			//printf("<ReturnStatement> -> <RETURN> <Expr> <SC>\n");
		}
                ;

ExitStatement 	: EXIT SEMICOLON
		{
			//printf("<ExitStatement> -> <EXIT> <SC>\n");
		}
		;

CompoundStatement : LBRACE StatementList RBRACE
		{
			
			//printf("<CompoundStatement> -> <LBR> <StatementList> <RBR>\n");
		}
                ;

StatementList   : Statement
		{		
			//printf("<StatementList> -> <Statement>\n");
		}
                | StatementList Statement
		{		
			//printf("<StatementList> -> <StatementList> <Statement>\n");
		}
                ;

Expr            : SimpleExpr
		{
			$$ = $1;
			//printf("<Expr> -> <SimpleExpr>\n");
		}
                | Expr OR SimpleExpr 
		{

			char r = getAvailableRegister();
			sprintf(tempString, 	"or $%d, $%d, $%d\n"
									"sne $%d, $%d, $0\n", 
									r, $1, $3, r, r);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;

		        //$$ = $1 | $3;
			//printf("<Expr> -> <Expr> <OR> <SimpleExpr> \n");
		}
                | Expr AND SimpleExpr 
		{
			char r = getAvailableRegister();
			sprintf(tempString, 	"sne $%d, $%d, $0\n"
									"sne $%d, $%d, $0\n"
									"and $%d, $%d, $%d\n", 
									$1, $1, $3, $3, r, $1, $3);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;


			//$$ = $1 & $3;
			//printf("<Expr> -> <Expr> <AND> <SimpleExpr> \n");
		}
                | NOT SimpleExpr 
		{
			sprintf(tempString, 	"seq $%d, $%d, $0\n", 
									$2, $2);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			$$ = $2;
		        //$$ = ($1 <= $3);
			//$$ = $2 ^ 1;
			//printf("<Expr> -> <NOT> <SimpleExpr> \n");
		}
                ;

SimpleExpr	: AddExpr
		{
			$$ = $1;
			//printf("<SimpleExpr> -> <AddExpr>\n");
		}
                | SimpleExpr EQ AddExpr
		{
			char r = getAvailableRegister();

			sprintf(tempString, 	"seq $%d, $%d, $%d\n", 
									r, $1, $3);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;

			//$$ = ($1 == $3);
			//printf("<SimpleExpr> -> <SimpleExpr> <EQ> <AddExpr> \n");
		}
                | SimpleExpr NE AddExpr
		{
			char r = getAvailableRegister();
			sprintf(tempString, 	"sne $%d, $%d, $%d\n", 
									r, $1, $3);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;

		        //$$ = ($1 != $3);
			//printf("<SimpleExpr> -> <SimpleExpr> <NE> <AddExpr> \n");
		}
                | SimpleExpr LE AddExpr
		{
			char r = getAvailableRegister();
			sprintf(tempString, 	"sle $%d, $%d, $%d\n", 
									r, $1, $3);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;
		        //$$ = ($1 <= $3);
			//printf("<SimpleExpr> -> <SimpleExpr> <LE> <AddExpr> \n");
		}
                | SimpleExpr LT AddExpr
		{
			char r = getAvailableRegister();
			sprintf(tempString, 	"slt $%d, $%d, $%d\n", 
									r, $1, $3);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;
		        //$$ = ($1 < $3);
			//printf("<SimpleExpr> -> <SimpleExpr> <LT> <AddExpr> \n");
		}
                | SimpleExpr GE AddExpr
		{
			char r = getAvailableRegister();
			sprintf(tempString, 	"sle $%d, $%d, $%d\n", 
									r, $3, $1);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;
		        //$$ = ($1 <= $3);
		        //$$ = ($1 >= $3);
			//printf("<SimpleExpr> -> <SimpleExpr> <GE> <AddExpr> \n");
		}
                | SimpleExpr GT AddExpr
		{
			char r = getAvailableRegister();
			sprintf(tempString, 	"slt $%d, $%d, $%d\n", 
									r, $3, $1);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;
			//printf("<SimpleExpr> -> <SimpleExpr> <GT> <AddExpr> \n");
		        //$$ = ($1 > $3);
		}
                ;

AddExpr		:  MulExpr            
		{
			$$ = $1;
			//printf("<AddExpr> -> <MulExpr>\n");
		}
                |  AddExpr PLUS MulExpr
		{
			char r = getAvailableRegister();
			sprintf(tempString, "add $%d, $%d, $%d\n", r, $1, $3);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;

			//$$ = $1 + $3;
			//printf("<AddExpr> -> <AddExpr> <PLUS> <MulExpr> \n");
		}
                |  AddExpr MINUS MulExpr
		{
			char r = getAvailableRegister();
			sprintf(tempString, "sub $%d, $%d, $%d\n", r, $1, $3);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;

			//$$ = $1 - $3;
			//printf("<AddExpr> -> <AddExpr> <MINUS> <MulExpr> \n");
		}
                ;

MulExpr		:  Factor // returns register
		{
			$$ = $1;
			//printf("<MulExpr> -> <Factor>\n");
		}
                |  MulExpr TIMES Factor //returns register
		{
			char r = getAvailableRegister();
			sprintf(tempString, "mult $%d, $%d\nmfhi $%d\nmflo $%d\n", $1, $3, r, r);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister($1);
			freeRegister($3);

			$$ = r;
			

			//$$ = $1 * $3;
			//printf("<MulExpr> -> <MulExpr> <TIMES> <Factor> \n");
		}
                |  MulExpr DIVIDE Factor//returns register
		{
			char r = getAvailableRegister();
			sprintf(tempString, "div $%d, $%d\nmfhi $%d\nmflo $%d\n", $1, $3, r, r);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			
			freeRegister($1);
			freeRegister($3);

			$$ = r;

			//$$ = $1 / $3;
			//printf("<MulExpr> -> <MulExpr> <DIVIDE> <Factor> \n");
		}		
                ;
				
Factor          : Variable //returns register
		{ 
			//remake to find all 
			char r = getAvailableRegister();

			if($1 < 0){
				sprintf(tempString, "lw $%d, 0($%d)\n", r, $1);
			} else{
				sprintf(tempString, "lw $%d, 0($%d)\n", r, $1);
			}

			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			$$ = r; 
			freeRegister($1);

		}
                | Constant
		{ 
			$$ = $1;
			//printf("<Factor> -> <Constant>\n");
		}
                | IDENTIFIER LPAREN RPAREN //function?
		{	
			//printf("<Factor> -> <IDENTIFIER> <LP> <RP>\n");
		}
         	| LPAREN Expr RPAREN //returns register
		{
			$$ = $2;
			//printf("<Factor> -> <LP> <Expr> <RP>\n");
		}
                ;  

Variable        : IDENTIFIER //returns a register containing the address
		{
			int* a = ((int*)SymGetField(symtab, $1, SYMTAB_VALUE_FIELD));
			char r = getAvailableRegister();

			if(*a < 0){
				sprintf(tempString, 	"li $%d %d\n"
										"add $%d $%d $sp\n", r, *a, r, r);
			} else{
				sprintf(tempString, 	"li $%d %d\n"
										"add $%d $%d $gp\n", r, *a, r, r);
			}
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			$$ = r;
		}
                | IDENTIFIER LBRACKET Expr RBRACKET    //array index
		{
			char r = getAvailableRegister();
			int* a = ((int*)SymGetField(symtab, $1, SYMTAB_VALUE_FIELD)); //offset of first element in array
			
			sprintf(tempString,	"sll $%d $%d 2\n", $3, $3); //index adjusted for size
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			sprintf(tempString, "add $%d $%d $gp\n", r, $3);  //increasing gp by index offset
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			sprintf(tempString, "li $%d %d\n"
								"add $%d $%d $%d\n", $3, *a, r, r, $3);  //increasing gp by index offset
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));


			$$ = r;

			freeRegister($3);
		}
                ;			       

StringConstant 	: STRING //returns index of label in symtab
		{ 
			$$ = stringCnstCount;
			stringCnstCount += 1; 

			dlinkAppend(&strCnstList, dlinkNodeAlloc(strdup($1)));
			
			//printf("<StringConstant> -> <STRING>\n");
		}
                ;

Constant        : INTCON //returns register of constant
		{
			char reg = getAvailableRegister();
			sprintf(tempString, "li $%d, %d\n", reg, $1);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			$$ = reg;
			//printf("<Constant> -> <INTCON>\n");
		}
                ;

%%


/********************C ROUTINES *********************************/

char getAvailableRegister(){
	for(int i = 0; i < 16; i++){
		if(registers[i] == 0){
			registers[i] = 1;
			return i + 8;
		}
	}
}

void freeRegister(char reg){
	reg = reg - 8;
	registers[reg] = 0;
}

void linkStringConstants(DLinkList* list, DLinkList* strings){
	int count = 0;
	DLinkNode* node = dlinkHead(strings);
	if(node == NULL){
		return;
	}

	do{
		sprintf(tempString, "S%d: .asciiz \"%s\"\n", count, (char*)dlinkNodeAtom(node));
		dlinkPush(dlinkNodeAlloc(strdup(tempString)), list);
		count++;
	} while((node = dlinkNext(node)));
}

void dumpList(DLinkList* list){
	DLinkNode* node = dlinkHead(list);
	if(node == NULL){
		return;
	}

	do{
		printf("%s", (char*)dlinkNodeAtom(node));
	} while((node = dlinkNext(node)));
}


void Cminus_error(const char *s)
{
  fprintf(stderr,"%s: line %d: %s\n",fileName,Cminus_lineno,s);
}

int Cminus_wrap() {
	return 1;
}

static void initialize(char* inputFileName) {

	Cminus_in = fopen(inputFileName,"r");
        if (Cminus_in == NULL) {
          fprintf(stderr,"Error: Could not open file %s\n",inputFileName);
          exit(-1);
        }

	char* dotChar = rindex(inputFileName,'.');
	int endIndex = strlen(inputFileName) - strlen(dotChar);
	char *outputFileName = nssave(2,substr(inputFileName,0,endIndex),".s");
	stdout = freopen(outputFileName,"w",stdout);
        if (stdout == NULL) {
          fprintf(stderr,"Error: Could not open file %s\n",outputFileName);
          exit(-1);
        }


	 symtab = SymInit(SYMTABLE_SIZE);
	 SymInitField(symtab,SYMTAB_VALUE_FIELD,(Generic)-1,NULL);

	 tempString = malloc(200);
	 registers = calloc(16, 1);
}

static void finalize() {

    SymKillField(symtab,SYMTAB_VALUE_FIELD);
    SymKill(symtab);
    fclose(Cminus_in);
    fclose(stdout);

}

int main(int argc, char** argv)

{	
	fileName = argv[1];
	initialize(fileName);
	
        Cminus_parse();
  
  	finalize();

  	return 0;
}

/*int getValue(int index)
{
  return (int)SymGetFieldByIndex(symtab, index, SYMTAB_VALUE_FIELD); 
}

int setValue(int index, int value)
{
  SymPutFieldByIndex(symtab, index, SYMTAB_VALUE_FIELD, (Generic)value); 
}*/
/******************END OF C ROUTINES**********************/
