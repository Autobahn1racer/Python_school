#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "CDLA.h"
/*
query -> SELECT parameters Fclause Wclause
parameters -> idA
A-> ,parameters| e
Fclause -> FROM parameters
Wclause -> WHERE exp
exp -> id='char'
*/
void valid()
{
    printf("SUCCESS!\n");
}
void invalid(char *msg)
{
    printf("ERROR: %s",msg);
    print(tkn);
    fclose(fp);
    exit(0);
}
void query();
void parameters();
void A();
void Fclause();
void Wclause();
void Exp();


void query()
{
    tkn = getNextToken();
    if(strcmp(tkn->name,"SELECT")==0)
    {
        parameters();
        Fclause();
        Wclause();
        return;
    }
    else invalid("Missing SELECT \n");
}
void parameters()
{
    tkn = getNextToken();
    if(strcmp(tkn->name,"ID")==0)
    {
        A();
        return;
    }
    else
    {
        invalid("Missing id \n");
    }
    return;
}
void A()
{
    tkn = getNextToken();
    if(strcmp(tkn->name,",")==0)
    {
        parameters();
        return;
    }
    else
    {
        if(strcmp(tkn->name,"FROM")==0)
        {
            ungetToken();
            return;
        }
        else if(strcmp(tkn->name,"WHERE")==0)
        {
            ungetToken();
            return;
        }
        else
        {
            invalid("Missing FROM or WHERE\n");
        }
    }
}
void Fclause()
{
    tkn = getNextToken();
    if(strcmp(tkn->name,"FROM")==0)
    {
        parameters();
        return;
    }
    else invalid("Missing FROM.");
}
void Wclause()
{
    tkn = getNextToken();
    if(strcmp(tkn->name,"WHERE")==0)
    {
        Exp();
        return;
    }
    else invalid("Missing WHERE \n");
}
void Exp()
{
    tkn = getNextToken();
    if(strcmp(tkn->name,"ID")==0)
    {
        tkn = getNextToken();
        if(strcmp(tkn->name,"=")==0)
        {
            tkn = getNextToken();
            if(strcmp(tkn->name,"character")==0)
            {
                if((tkn = getNextToken())!=NULL)
                {
                    if(strcmp(tkn->name,"$")==0)
                    {
                        return;
                    }
                    else invalid("Expected $ \n");
                }
                else 
                {
                    printf("Expected $ \n");
                    fclose(fp);
                    exit(0);
                }
            }
            else invalid("Expected literal \n");
        }
        else invalid("Expected = \n");
    }
    else invalid("Expected id \n");
}

int main(int argc,char* argv[])
{
	loadKeywords();
	fp = fopen("sample.txt","r");
    query();
	char ca = getc(fp);
	while(ca=='\n'||ca==' '||ca=='\t'||ca=='\r') ca = getc(fp);
	if(ca==EOF) valid();
	else printf("Unrecognised statements at the end\n");
    while((tkn = getNextToken())!=NULL)
    {
        print(tkn);
    }
    printf("\n");
    printST();
   
    fclose(fp);
    return 0;
}
