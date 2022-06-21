#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "CDLA.h"
void valid()
{
	    printf("SUCCESS!\n");
	    exit(0);
}
void invalid(char *msg)
{
	printf("ERROR: %s",msg);
	print(tkn);
	fclose(fp);
	exit(0);
}
void Start();
void Idnum();
void Term();
void A();
void From_clause();
void Identifier();
void B();
void Start()
{
	tkn=getNextToken();
	if(strcmp(tkn->name,"SUBTRACT")==0)
	{
		Idnum();
		From_clause();
		return;
	}
	else
		invalid("Missing SUBTRACT\n");
}

void Idnum()
{
	Term();
	A();
	return;
}
void A()
{
	tkn=getNextToken();
	if(strcmp(tkn->name,",")==0)
	{
		Idnum();
		return;
	}
	else
	{
		if(strcmp(tkn->name,"FROM")==0)
		{
			ungetToken();
			return;
		}
		else
			invalid("Missing FROM\n");
	}
}
void Term()
{
	tkn=getNextToken();
	if(strcmp(tkn->name,"id")==0 || strcmp(tkn->name,"num")==0)
	{
		return;
	}
	else
		invalid("Expected id or num");
}

void From_clause()
{
	tkn=getNextToken();
	if(strcmp(tkn->name,"FROM")==0)
	{
		Identifier();
		return;
	}
	else
		invalid("Missing FROM\n");
}

void Identifier()
{
	tkn=getNextToken();
	if(strcmp(tkn->name,"id")==0)
	{
		B();
		return;
	}
	else
		invalid("Expected ID\n");
}
void B()
{
	tkn=getNextToken();
	if(strcmp(tkn->name,",")==0)
	{
		Identifier();
		return;
	}
	else if(strcmp(tkn->name,"$")==0)
	{
		return;
	}
	else
		invalid("Unexpected statements\n");
}

int main(int argc,char* argv[])
{
	loadKeywords();
	fp = fopen("hmmbruh.txt","r");
	Start();
	char ca = getc(fp);
	while(ca=='\n'||ca==' '||ca=='\t'||ca=='\r') ca = getc(fp);
	if(ca==EOF) valid();
	else printf("Unrecognised statements at the end\n");   
	fclose(fp);
	return 0;
}
