#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/stat.h>
#define retract fseek(fp,-1,SEEK_CUR)
int row=1;
int col=0;
int flag=0;
int in=-1;
FILE* fp;
char dtbuf[30];
char* keywords[33]={"double","int","char","for","while","main"};
struct token
{
	int row;
	int col;
	int lex_length;
	char name[30];
};
struct token* tkn;
void resetGlobalVariables()
 {
     tkn=(struct token*)malloc(sizeof(struct token*));
     flag=0;
     row=1;
     col=0;
     in=-1;
 }

int isKeyword(char* str)
{
	int i;
	for(i=0;i<6;i++)
	{
		if(strcmp(keywords[i],str)==0)
		{
			return 1;
		}
	}
	return 0;
}

int isDataType(char *str)
{
	if(strcmp(str,"int")==0||strcmp(str,"char")==0||strcmp(str,"float")==0||strcmp(str,"double")==0)
		{
			return 1;
		}
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
int getWhiteSpaces(struct token* tkn)
{
	col=col-1;
	char c = getc(fp);
	if(c=='\t'||c=='\0'||c=='\n'||c=='\r'||c==' ')
	{
		if(flag)
		printf("%c",c);
		if(c=='\t')
		{
			col=col+4;
		}
		if(c=='\n')
		{
			row++;
			col=0;
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
	tkn->col=col;
	int temp=col;
	
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
		tkn->lex_length=col-temp;
		strcpy(tkn->name,"number");
		return 1;
	}
	else
	col=temp;

	return 0;
}
int getID(struct token* tkn)
{
	
	
	int l=0;
	int temp=col;
	char c = getc(fp);
	char word[81];
	if(!(isalnum(c)) || c=='_')
	{
		retract;
		return 0;
	}
	while(isalnum(c) || c=='_')
	{
		col++;
		word[l++]=c;
		c=getc(fp);
	}
	retract;
	word[l]=0;
	tkn->row=row;
	tkn->col=temp;
	tkn->lex_length=strlen(word);
	strcpy(tkn->name,"id");
	return 1;

}
int getStrLit(struct token* tkn)
{
	int temp=col;
	int l = 0;
	char c = getc(fp);
	if(c=='"')
	{
		tkn->col=col;
		while((c=getc(fp))!='"' && c!=EOF)
		{
			l++;
			col++;
		}
		tkn->col=col;
		tkn->lex_length=l;
		strcpy(tkn->name,"literal");
		return 1;
	}
	return 0;
}
int getKeyword(struct token* tkn)
{
	retract;
	char c = getc(fp);
	int temp=col;
	int l=0;
	char word[81];
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
		if(isDataType(word))
		{
			strcpy(dtbuf,word);
		}
		tkn->row=row;
		tkn->col=temp;
		strcpy(tkn->name,word);
		tkn->lex_length=strlen(word);
		return 1;
	}
	col=temp;
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

	if(getWhiteSpaces(tkn))
	{
		return getNextToken();
	}
	return tkn;
}

void ungetToken()
{
	fseek(fp,-(tkn->lex_length),SEEK_SET);
	col=col-(tkn->lex_length-1);
}

void print(struct token* tkn)
{
	printf("<%s,%d,%d,%d>\n",tkn->name,tkn->row,tkn->col,tkn->lex_length);
}
// int main()
// {
// 	fp=fopen("bruh.c","r");
// 	struct token* tkn;
// 	tkn = (struct token*)malloc(sizeof(struct token));
// 	while((tkn=getNextToken())!=NULL)
// 	{
// 		print(tkn);
// 	}
// 	fclose(fp);
// }