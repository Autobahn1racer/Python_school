#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/stat.h>
#include<sys/stat.h>
#define retract fseek(fp,-1,SEEK_CUR)
FILE* fp;
int row=1;
int col=0;
int flag = 0;
char keywords[32][33] = {"printf","int","float","double","void"};
struct token
{
    char name[30];
    int row;
    int col;
    int lex_length;
};
struct token* tkn;
int isKeyword(char* str)
{
    int i;
    for(i=0;i<5;i++)
    {
        if(strcmp(keywords[i],str)==0)
        {
            return 1;
        }
    }
    return 0;
}
void resetGlobalVariables()
{
    tkn=(struct token*)malloc(sizeof(struct token));
    flag = 0;
    row=1;
    col=0;
    flag=0;
}
void ungetToken()
{
    fseek(fp,-(tkn->lex_length),SEEK_CUR);
    col=col-(tkn->lex_length+1);
}
void print(struct token* tkn)
{
    printf("<%s,%d,%d,%d>\n",tkn->name,tkn->row,tkn->col,tkn->lex_length);
}

int getKeyword(struct token* tkn)
{
    retract;
    char c = getc(fp);
    int l = 0;
    char word[81];
    int temp = col;
    while(isalpha(c))
    {
        col++;
        word[l++]=c;
        c=getc(fp);
    }
    retract;
    word[l]=0;
    if(isKeyword(word))
    {
        tkn->row=row;
        tkn->col=temp;
        strcpy(tkn->name,word);
        tkn->lex_length=strlen(word);
        return 1;
    }
    col=temp;
    return 0;
}

int getWhiteSpace(struct token* tkn)
{
    col=col-1;
    char c = getc(fp);
    if(c=='\t'||c=='\n'||c=='\r'||c=='\0'||c==' ')
    {
        if(flag)
        printf("%c",c);

        if(c=='\t')
        {
            col=col+4;
        }

        if(c=='\n')
        {
            col=0;
            row++;
        }
        tkn->row=row;
        tkn->col=col;
        strcpy(tkn->name,"WS");
        return 1;
    }
    return 0;
}

int getNum(struct token* tkn)
{
    int temp = col;
    tkn->col=col;
    char c = getc(fp);
    if(isdigit(c))
    {
        while(isdigit(c))
        {
            col++;
            c=getc(fp);
        }
        retract;
        tkn->row=row;
        strcpy(tkn->name,"number");
        tkn->lex_length=col-temp;
        return 1;
    }
    col=temp;
    return 0;
}

int getSS(struct token* tkn)
{
   char c = getc(fp);
   tkn->lex_length=1;
   if(c=='{')
   {
       tkn->row=row;
       tkn->col=col;
       strcpy(tkn->name,"{");
       return 1;
   } 
   else if(c=='}')
   {
       tkn->row=row;
       tkn->col=col;
       strcpy(tkn->name,"}");
       return 1;
   } 
   else if(c=='[')
   {
       tkn->row=row;
       tkn->col=col;
       strcpy(tkn->name,"[");
       return 1;
   }
   else if(c==']')
   {
       tkn->row=row;
       tkn->col=col;
       strcpy(tkn->name,"]");
       return 1;
   }
   else if(c=='(')
   {
       tkn->row=row;
       tkn->col=col;
       strcpy(tkn->name,"(");
       return 1;
   }
   else if(c==')')
   {
       tkn->row=row;
       tkn->col=col;
       strcpy(tkn->name,")");
       return 1;
   }
   else if(c==';')
   {
       tkn->row=row;
       tkn->col=col;
       strcpy(tkn->name,";");
       return 1;
   }
   else if(c==',')
   {
       tkn->row=row;
       tkn->col=col;
       strcpy(tkn->name,",");
       return 1;
   }
   else if(c=='=')
   {
       tkn->row=row;
       tkn->col=col;
       strcpy(tkn->name,"=");
       return 1;
   }
   return 0;
}

int getID(struct token* tkn)
{
    char word[81];
    int l=0;
    int temp=col;
    char c = getc(fp);
    if(!(isalnum(c)) || c=='_')
    {
        retract;
        return 0;
    }
    while (isalnum(c) || c=='_')
    {
        col++;
        word[l++]=c;
        c=getc(fp);
    }
    retract;
    word[l]=0;
    tkn->row=row;
    tkn->col=temp;
    strcpy(tkn->name,"id");
    tkn->lex_length=strlen(word);
    return 1;
}

int getStrLit(struct token* tkn)
{
    int l = 0;
    char c = getc(fp);
    int temp=col;
    if(c=='"')
    {
        tkn->col=col;
        while((c=getc(fp))!='"' && c!=EOF)
        {
            col++;
            l++;
        }
        tkn->row=row;
        tkn->lex_length=l;
        strcpy(tkn->name,"literal");
        return 1;
    }
    return 0;
}
struct token* getNextToken()
{
    int curr = ftell(fp);
    char c = getc(fp);
    if(c==EOF)
    {
        return NULL;
    }
    col++;
    struct token* tkn = (struct token*)malloc(sizeof(struct token));
    int temp=col;

	if(getKeyword(tkn))
	{
		return tkn;
	}
	else fseek(fp,curr,SEEK_SET);
	col=temp;
	
	if(getNum(tkn))
	{
		return tkn;
	}
	else fseek(fp,curr,SEEK_SET);
	col=temp;
	
	if(getID(tkn))
	{
		return tkn;
	}
	else fseek(fp,curr,SEEK_SET);
	col=temp;

	if(getStrLit(tkn))
	{
		return tkn;
	}
	else fseek(fp,curr,SEEK_SET);
	col=temp;

	if(getSS(tkn))
	{
		return tkn;
	}
	else fseek(fp,curr,SEEK_SET);
	col=temp;

	if(getWhiteSpace(tkn))
	{
		return getNextToken();
	}
	return tkn;
}
// int main()
// {
//     fp=fopen("bruh.c","r");
//     tkn=(struct token*)malloc(sizeof(struct token));

//     while((tkn=getNextToken())!=NULL)
//     {
//         print(tkn);
//     }
//     fclose(fp);
//     exit(0);
// }