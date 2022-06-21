/*
	Program --> main() { declarations statement_list }
	declarations --> data_type identifier_list; declarations | e
	data_type --> int | char
	identifier_list --> idA
	A --> , identifier_list | [number]B | e
	B --> , identifier_list | e
	statement_list --> statement statement_list | e
	statement --> assign_stat; | decision_stat | looping_stat
	assign_stat --> id = expn
	expn --> simple_expn eprime
	eprime --> relop simple_expn | e
	simple_expn --> term seprime
	seprime --> addop term seprime | e
	term --> factor tprime
	tprime --> mulop factor tprime | e
	factor --> id | num
	decision_stat --> if(expn){statement_list} dprime
	dprime --> else {statement_list}|e
	looping_stat --> while(expn){statement_list} | for(assign_stat;expn;assign_stat){ statement_list }
	relop --> == | != | <= | >= | > | <
	addop --> + | -
	mulop --> * | / | %
*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include "CDLA.c"
void valid()
{
	printf("Success!\n");
	exit(0);
}
void invalid(char* msg,int row,int col)
{
	printf("Failure in row %d, column %d: ",row,col);
	puts(msg);
    printf("Received token: %s",tkn->name);
//    print(tkn);
    fseek(fp,-1,SEEK_END);
    putc(' ',fp);
    fclose(fp);
	exit(0);
}
int isIn(char* str, char arr[][10],int N)
{
	for(int i = 0; i<N;i++)
	{
		if(strcmp(str,arr[i])==0)
			return 1;
	}
	return 0;
}
char FollowDec[5][10] = { "ID","if","for","while","}"};
char FollowA[5][10] = {";","$"};
char FollowB[5][10] = {";","$"};
char FollowSL[5][10] = {"}"};
char FollowEp[5][10] = {";",")"};
char FollowSEp[10][10] = {"==","!=","<=",">=","<",">",";",")"};
char FollowTp[10][10] = {"+","-",";","==","!=","<=",">=","<",">",")"};
char FollowDp[5][10] = {"ID","if","for","while","}"};
void Program();
void declarations();
void data_type();
void identifier_list();
void A();
void B();
void statement_list();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void decision_stat();
void dprime();
void looping_stat();
void relop();  
void addop();
void mulop();

void Program()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,"main")==0)
	{
		tkn = getNextToken();
		if(strcmp(tkn->name,"(")==0)
		{
			tkn = getNextToken();
			if(strcmp(tkn->name,")")==0)
			{
				tkn = getNextToken();
				if(strcmp(tkn->name,"{")==0)
				{
					declarations();
					statement_list();
					tkn = getNextToken();
					if(strcmp(tkn->name,"}")==0)
						return;
					else invalid("Missing }",tkn->row,tkn->column);
				}
				else invalid("Missing definition of main()",tkn->row, tkn->column);
			}
			else invalid("Missing )",tkn->row,tkn->column);
		}
		else invalid("Missing (",tkn->row,tkn->column);
	}
	else invalid("Missing main()",tkn->row,tkn->column);
}

void declarations()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,"int")==0||strcmp(tkn->name,"char")==0)
	{
		ungetToken();
		data_type();
		identifier_list();
		tkn = getNextToken();
		if(strcmp(tkn->name,";")==0)
		{
			declarations();
			return;
		}
		else invalid("Missing ;",tkn->row,tkn->column);
	}
	else if(isIn(tkn->name,FollowDec,5))
	{
		ungetToken();
		return;
	}
	else invalid("Expected ID or if or for or while or }",tkn->row,tkn->column);
}

void data_type()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,"int")==0||strcmp(tkn->name,"char")==0)
		return;
	else invalid("Expected int or char",tkn->row,tkn->column);
}

void identifier_list()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,"ID")==0)
	{
		A();
		return;
	}
	else invalid("Expected ID",tkn->row,tkn->column);
}
//A --> , identifier_list | [number]B | e
void A()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,",")==0)
	{
		identifier_list();
		return;
	}
	else if(strcmp(tkn->name,"[")==0)
	{
        tkn = getNextToken();
        if(strcmp(tkn->name,"number")==0)
        {
            tkn = getNextToken();
            if(strcmp(tkn->name,"]")==0)
            {
                B();
                return;
            }
            else invalid("Expected ]",tkn->row,tkn->column);
        }
        else invalid("Expected number",tkn->row,tkn->column);
	}
	else if(isIn(tkn->name,FollowA,2))
	{
		ungetToken();
		return;
	}
	else invalid("Expected ;",tkn->row,tkn->column);
}
//B --> , identifier_list | e
void B()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,",")==0)
	{
		identifier_list();
		return;
	}
	else if(isIn(tkn->name,FollowB,2))
	{
		ungetToken();
		return;
	}
	else invalid("Expected ;",tkn->row,tkn->column);
}

void statement_list()
{
	tkn = getNextToken();
	if(isIn(tkn->name,FollowSL,1))
	{
		ungetToken();
		return;
	}
	else
	{
		ungetToken();
		statement();
		statement_list();
		return;
	}
}

void statement()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,"ID")==0)
	{
		ungetToken();
		assign_stat();
		tkn = getNextToken();
		if(strcmp(tkn->name,";")==0)
			return;
		else invalid("Missing ;",tkn->row,tkn->column);
	}
	else if(strcmp(tkn->name,"if")==0)
	{
		ungetToken();
		decision_stat();
		return;
	}
	else if(strcmp(tkn->name,"while")==0||strcmp(tkn->name,"for")==0)
	{
		ungetToken();
		looping_stat();
		return;
	}
	else invalid("Unrecognised token at ",tkn->row,tkn->column);
}

void assign_stat()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,"ID")==0)
	{
		tkn = getNextToken();
		if(strcmp(tkn->name,"=")==0)
		{
			expn();
			return;
		}
		else invalid("Expected = ",tkn->row,tkn->column);
	}
	else invalid("Expected ID",tkn->row,tkn->column);
}

void expn()
{
	simple_expn();
	eprime();
}

void eprime()
{
	tkn = getNextToken();
	if(isIn(tkn->name,FollowEp,2))
	{
		ungetToken();
		return;
	}
	else
	{
		ungetToken();
		relop();
		simple_expn();
		return;
	}
}

void simple_expn()
{
	term();
	seprime();
}

void seprime()
{
	tkn = getNextToken();
	if(isIn(tkn->name,FollowSEp,8))
	{
		ungetToken();
		return;
	}
	else
	{
		ungetToken();
		addop();
		term();
		seprime();
		return;
	}
}

void term()
{
	factor();
	tprime();
}

void tprime()
{
	tkn = getNextToken();
	if(isIn(tkn->name,FollowTp,10))
	{
		ungetToken();
		return;
	}
	else
	{
		ungetToken();
		mulop();
		factor();
		tprime();
		return;
	}
}

void factor()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,"ID")==0||strcmp(tkn->name,"number")==0)
		return;
	else invalid("Expected ID or Number",tkn->row,tkn->column);
}

void decision_stat()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,"if")==0)
	{
		tkn = getNextToken();
		if(strcmp(tkn->name,"(")==0)
		{
			expn();
			tkn = getNextToken();
			if(strcmp(tkn->name,")")==0)
			{
				tkn = getNextToken();
				if(strcmp(tkn->name,"{")==0)
				{
					statement_list();
					tkn = getNextToken();
					if(strcmp(tkn->name,"}")==0)
					{
						dprime();
						return;
					}
					else invalid("Expected }",tkn->row,tkn->column);
				}
				else invalid("Expected {",tkn->row,tkn->column);
			}
			else invalid("Expected )",tkn->row,tkn->column);
		}
		else invalid("Expected (",tkn->row,tkn->column);
	}
	else invalid("Expected if",tkn->row,tkn->column);
}

void dprime()
{
	tkn = getNextToken();
	if(isIn(tkn->name,FollowDp,5))
	{
		ungetToken();
		return;
	}
	else
	{
		if(strcmp(tkn->name,"else")==0)
		{
			tkn = getNextToken();
			if(strcmp(tkn->name,"{")==0)
			{
				statement_list();
				tkn = getNextToken();
				if(strcmp(tkn->name,"}")==0)
					return;
				else invalid("Expected }",tkn->row,tkn->column);
			}
			else invalid("Expected {",tkn->row,tkn->column);
		}
		else invalid("Expected else",tkn->row,tkn->column);
	}
}

void looping_stat()
{
	tkn = getNextToken();
	if(strcmp(tkn->name,"while")==0)
	{
		tkn = getNextToken();
		if(strcmp(tkn->name,"(")==0)
		{
			expn();
			tkn = getNextToken();
			if(strcmp(tkn->name,")")==0)
			{
				tkn = getNextToken();
				if(strcmp(tkn->name,"{")==0)
				{
					statement_list();
					tkn = getNextToken();
					if(strcmp(tkn->name,"}")==0)
						return;
					else invalid("Expected }",tkn->row,tkn->column);
				}
				else invalid("Expected {",tkn->row,tkn->column);
			}
			else invalid("Expected )",tkn->row,tkn->column);
		}
		else invalid("Expected (",tkn->row,tkn->column);
	}
	else if(strcmp(tkn->name,"for")==0)
	{
		tkn = getNextToken();
		if(strcmp(tkn->name,"(")==0)
		{
			assign_stat();
			tkn = getNextToken();
			if(strcmp(tkn->name,";")==0)
			{
				expn();
				tkn = getNextToken();
				if(strcmp(tkn->name,";")==0)
				{
					assign_stat();
					tkn = getNextToken();
					if(strcmp(tkn->name,")")==0)
					{
						tkn = getNextToken();
						if(strcmp(tkn->name,"{")==0)
						{
							statement_list();
							tkn = getNextToken();
							if(strcmp(tkn->name,"}")==0)
								return;
							else invalid("Expected }",tkn->row,tkn->column);
						}
						else invalid("Expected {",tkn->row,tkn->column);
					}
					else invalid("Expected )",tkn->row,tkn->column);
				}
				else invalid("Expected ;",tkn->row,tkn->column);
			}
			else invalid("Expected ;",tkn->row,tkn->column);
		}
		else invalid("Expected (",tkn->row,tkn->column);
	}
	else invalid("Expected loop",tkn->row,tkn->column);
}

void relop()
{
	tkn = getNextToken();
    char relOp[6][10] = {"==","!=","<=",">=",">","<"};
    if(isIn(tkn->name,relOp,6))
	{
		return;
	}
	else invalid("Expected relop",tkn->row,tkn->column);
}

void addop()
{
	tkn = getNextToken();
	char addOp[2][10] = {"+","-"};
    if(isIn(tkn->name,addOp,2))
		return;
	else invalid("Expected addop",tkn->row,tkn->column);
}

void mulop()
{
	tkn = getNextToken();
    char mulOp[3][10] = {"*","/","%"};
	if(isIn(tkn->name,mulOp,3))
		return;
	else invalid("Expected mulop",tkn->row,tkn->column);
}

int main()
{
// Function defined in CDLA to load keywords into the keywords array
	loadKeywords();
// fp and tkn are global variables in CDLA code
// Appending $ to input
	fp = fopen("lab8sample.c","a");
    putc('$',fp);
    fclose(fp);
    fp = fopen("lab8sample.c","r+");
	Program();
	char ca = getc(fp);
	while(ca=='\n'||ca==' '||ca=='\t'||ca=='\r') ca = getc(fp);
	if(ca=='$') valid();
	else printf("Unrecognised statements at the end");
// Removing the appended $ from the file
    fseek(fp,-1,SEEK_END);
    putc(' ',fp);
    fseek(fp,0,SEEK_SET);
// Function in CDLA to reset Global Variables like row, column etc
    resetGlobalVariables();
/*
    flag is a global variable in CDLA. If flag = 1,
    then LA prints every whitespace character encountered
    to make the output more readable
*/
    flag = 1;
    while((tkn = getNextToken())!=NULL)
    {
        print(tkn); 
    }
    printf("\nPrinting Symbol Table:\n");
    printST();
    fclose(fp);
}