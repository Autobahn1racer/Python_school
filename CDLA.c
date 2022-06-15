#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#define retract fseek(fp,-1,SEEK_CUR)
char keywords[33][32],dtbuff[20],buff[34];
FILE *fp;
int column=0,row=1,in=-1;
int flag=0;
struct token
{
	int row;
	int column;
	char name[200];
    int lexeme_length;
};
struct token* tkn;
struct ST
{
	char lexeme[20];
	char type[10];
	int size;
}table[1000];
void resetGlobalVariables()
{
    tkn = (struct token*)malloc(sizeof(struct token));
    column = 0;
    row = 1;
    in = -1;
    flag = 0;
}
void loadKeywords()
{
	FILE* fb;
	char cb;
	int l,i = 0;
	char word[80];
	fb = fopen("keywords.txt","r");
	if(fb == NULL)
	{
		printf("Cannot open file \n");
		exit(0); 
	}
	cb = getc(fb);
	while(cb!=EOF)
	{
		l = 0;
		while(isalpha(cb))
		{
			word[l++] = cb;
			cb = getc(fb); 
		}
		word[l] = 0;
		if(l>0)
		{
			strcpy(keywords[i++],word);
		}
		cb = getc(fb);
	}
    fclose(fb);
}
int getArithOp(struct token* tkn)
{
		retract;
        char ca;
		ca = getc(fp);
		if(ca=='+')
		{
			ca = getc(fp);
			if(ca=='+')
			{
				strcpy(tkn->name,"++");
				tkn->row = row;
				tkn->column = column++;
                tkn->lexeme_length = 2;
				return 1;
			}
			else
			{
				retract;
				strcpy(tkn->name,"+");
				tkn->row = row;
				tkn->column = column;
				tkn->lexeme_length = 1;
                return 1;
			}
		}
		else if(ca=='-')
		{
			ca = getc(fp);
			if(ca=='-')
			{
				strcpy(tkn->name,"--");
				tkn->row = row;
				tkn->column = column++;
                tkn->lexeme_length = 2;
        		return 1;
			}
			else
			{
				retract;
				strcpy(tkn->name,"-");
				tkn->row = row;
				tkn->column = column;
                tkn->lexeme_length = 1;
            	return 1;
			}
		}
		else if(ca=='*')
		{
			strcpy(tkn->name,"*");
			tkn->row = row;
			tkn->column = column;
            tkn->lexeme_length = 1;
			return 1;
		}
		else if(ca=='/')
		{
			strcpy(tkn->name,"/");
			tkn->row = row;
			tkn->column = column;
			tkn->lexeme_length = 1;
            return 1;
		}
		else if(ca=='%')
		{
			strcpy(tkn->name,"%");
			tkn->row = row;
			tkn->column = column;
            tkn->lexeme_length = 1;
        	return 1;
		}
		return 0;
}
int getRelOp(struct token* tkn)
{
    retract;
    int state = 0;
    char c;
    while(7)
    {
        switch(state)
        {
            case 0: c = getc(fp);
            if(c=='<') state = 1;
            else if(c=='=') state = 4;
            else if(c=='!') state = 6;
            else if(c=='>') state = 8;
            else return 0;
            break;
            case 1: c = getc(fp);
            if(c=='=') state = 2;
            else state = 3;
            break;
            case 2: strcpy(tkn->name,"<="); 
            tkn->row = row; 
            tkn->column = column++;
            tkn->lexeme_length = 2; 
            return 1;
            case 3: retract;
            strcpy(tkn->name,"<"); 
            tkn->row = row; 
            tkn->column = column; 
            tkn->lexeme_length = 1;
            return 1;
            case 4: c = getc(fp);
            if(c=='=') state = 5;
            else 
            {
                retract;
                strcpy(tkn->name,"="); 
                tkn->row = row; 
                tkn->column = column;
                tkn->lexeme_length = 1; 
                return 1;
            }
            break;
            case 5: strcpy(tkn->name,"=="); 
            tkn->row = row; 
            tkn->column = column++; 
            tkn->lexeme_length = 2;
            return 1;
            case 6: c = getc(fp);
            if(c=='=') state = 7;
            else return 0;
            break;
            case 7: strcpy(tkn->name,"!="); 
            tkn->row = row; 
            tkn->column = column++;
            tkn->lexeme_length = 2; 
            return 1;
            case 8: c = getc(fp);
            if(c=='=')state = 9;
            else state = 10;
            break;
            case 9: strcpy(tkn->name,">="); 
            tkn->row = row; 
            tkn->column = column++;
            tkn->lexeme_length = 2; 
            return 1;
            case 10: retract;
            strcpy(tkn->name,">"); 
            tkn->row = row; 
            tkn->column = column; 
            tkn->lexeme_length = 1;
            return 1;
        }
    }
    return 0;
}

int getLogOp(struct token* tkn)
{
    retract;
    char c;
    c = getc(fp);
    if(c=='!')
    {
        strcpy(tkn->name,"!"); 
        tkn->row = row; 
        tkn->column = column; 
        tkn->lexeme_length = 1;
        return 1;
    }
    else if(c=='&')
    {
        c = getc(fp);
        if(c=='&')
        {
            strcpy(tkn->name,"&&"); 
            tkn->row = row; 
            tkn->column = column++; 
            tkn->lexeme_length = 2;
            return 1;
        }
        else retract;
    }
    else if(c=='|')
    {
        c = getc(fp);
        if(c=='|')
        {
            strcpy(tkn->name,"||"); 
            tkn->row = row; 
            tkn->column = column++; 
            tkn->lexeme_length = 2;
            return 1;
        }
        else retract;
    }
    return 0;    
}
int getSpecSym(struct token* tkn)
{
        retract;
        char c = getc(fp);
        tkn->lexeme_length = 1;
        if(c==';')
        {
            strcpy(tkn->name,";");
            tkn->row = row;
            tkn->column = column;
            return 1;
        }
        else if(c==',')
        {
            strcpy(tkn->name,",");
            tkn->row = row;
            tkn->column = column;
            return 1;
        }
        else if(c=='{')
        {
            strcpy(tkn->name,"{");
            tkn->row = row;
            tkn->column = column;
            return 1;
        }
        else if(c=='}')
        {
            strcpy(tkn->name,"}");
            tkn->row = row;
            tkn->column = column;
            return 1;
        }
        else if(c=='[')
        {
            strcpy(tkn->name,"[");
            tkn->row = row;
            tkn->column = column;
            return 1;
        }
        else if(c==']')
        {
            strcpy(tkn->name,"]");
            tkn->row = row;
            tkn->column = column;
            return 1;
        }
        else if(c=='(')
        {
            strcpy(tkn->name,"(");
            tkn->row = row;
            tkn->column = column;
            return 1;
        }
        else if(c==')')
        {
            strcpy(tkn->name,")");
            tkn->row = row;
            tkn->column = column;
            return 1;
        }
        else if(c=='$')
        {
            strcpy(tkn->name,"$");
            tkn->row = row;
            tkn->column = column;
            return 1;            
        }
        return 0;
}
int getUNo(struct token* tkn)
{
    int state = 0;
    retract;
    int temp_col = column;
    tkn->column = column;
    char c;
    while(7)
    {
        switch(state)
        {
            case 0: c = getc(fp);
            if(c=='-') state = 1;
            else if(isdigit(c)) state = 1;
            else { column = temp_col; return 0; }
            break;
            case 1: c = getc(fp);
            if(isdigit(c)) state = 1;
            else if(c=='.') state = 2;
            else if(c=='E') state = 4;
            else state = 8;
            column++;
            break;
            case 2: c = getc(fp);
            if(isdigit(c)){ state = 3; column++; }
            else { column = temp_col; return 0; }
            break;
            case 3: c = getc(fp);
            if(isdigit(c)) state = 3;
            else if(c=='E') state = 4;
            else state = 9;
            column++;
            break;
            case 4: c = getc(fp);
            if(c=='+'||c=='-') { state = 5; column++; }
            else if(isdigit(c)) { state = 6; column ++; }
            else { column = temp_col; return 0; }
            break;
            case 5: c = getc(fp);
            if(isdigit(c)) { state = 6; column++; }
            else { column = temp_col; return 0; }
            break;
            case 6: c = getc(fp);
            if(isdigit(c)) state = 6;
            else state = 7;
            column++;
            break;
            case 7: retract;
            column--;
            strcpy(tkn->name,"number");
            tkn->row = row;
            return 1;
            case 8: retract;
            column--;
            strcpy(tkn->name,"number");
            tkn->row = row;
            return 1;
            case 9: retract;
            column--;
            strcpy(tkn->name,"number");
            tkn->row = row;
            return 1;
        }
    }
    column = temp_col;
    return 0;
}
int getStrLit(struct token* tkn) 
{
    retract;
    char c;
    int temp = column;
    int l =0;
    c = getc(fp);
    if(c == '"')
    {
        tkn->column = column;
        while((c = getc(fp))!='"'&&c!=EOF)
        {
            column++; l++;
        }
        tkn->row = row;
        strcpy(tkn->name,"character");
        tkn->lexeme_length = l;
        return 1;
    }
    return 0;
}
int isDataType(char* str)
{
	if(strcmp(str,"int")==0||strcmp(str,"float")==0||strcmp(str,"double")==0||strcmp(str,"char")==0||strcmp(str,"void")==0) return 1;
	return 0;
}

int isKeyword(char* str)
{
	for(int i =0;i<33;i++)
	{
		if(strcmp(keywords[i],str)==0) return 1;
	}
	return 0;
}
int getKeyword(struct token* tkn)
{
	retract;
	tkn->column = column;
	int temp = column;
	char c;
	char word[81];
	c = getc(fp);
	int l =0;
	while(isalpha(c))
	{
		word[l++] = c;
		column++;
		c = getc(fp); 
	}
    retract;
	word[l] = 0;
	if(isKeyword(word))
	{
		if(isDataType(word)) strcpy(dtbuff,word);
		strcpy(tkn->name,word);
		tkn->row = row;
        tkn->lexeme_length = strlen(word);
		return 1;
	}
	else column = temp;
	return 0;
}

int SearchOrInsert(char* str)
{
	for(int i =0;i<=in;i++) if(strcmp(table[i].lexeme,str)==0) return i;
	in++;
	char num[10];
	int j =0;
	strcpy(table[in].lexeme,str);
	int pos = ftell(fp);
	char c = getc(fp);
	if(c == '(')
	{
		strcpy(table[in].type,"FUNC");
		table[in].size = 0;
		fseek(fp,pos,SEEK_SET);
		return -1;
	}
	if(strcmp(dtbuff,"int")==0) table[in].size = 4;
	else if(strcmp(dtbuff,"float")==0) table[in].size = 4;
	else if(strcmp(dtbuff,"char")==0) table[in].size = 1;
	else if(strcmp(dtbuff,"double")==0) table[in].size = 8;
	if(c == '[')
	{
		c = getc(fp);
		while(isdigit(c))
		{
			num[j++] = c;
			c = getc(fp);
		}
		num[j] = 0;
		table[in].size*=(atoi(num));
		fseek(fp,pos,SEEK_SET);
	}
	strcpy(table[in].type,dtbuff);
    fseek(fp,pos,SEEK_SET);
	return -1;
}

int getID(struct token* tkn)
{
	retract;
	tkn->column = column;
	int temp = column;
	char c;
	char word[81];
	c = getc(fp);
	if(!(isalpha(c)||c=='_')) {retract; return 0;}
	int l =0;
	while(isalnum(c)||c=='_')
	{
		word[l++] = c;
		column++;
		c = getc(fp); 
	}
	word[l] = 0;
	retract;
    //retract;
	SearchOrInsert(word);
	strcpy(tkn->name,"ID");
	tkn->row = row;
    tkn->lexeme_length = strlen(word);
	return 1;
}
void ungetToken()
{
    fseek(fp,-(tkn->lexeme_length),SEEK_CUR);
    column-=(tkn->lexeme_length+1);
}
int getWhitespace(struct token* tkn)
{
    retract;
    char c = getc(fp);
    if(c==' '||c=='\n'||c=='\r'||c=='\t'||c=='\b'||c=='\0')
    {
        if(flag) printf("%c",c);
        if(c=='\n')
        {
            row++; column = 0;
        }
        if(c=='\t') column+=4;            
        strcpy(tkn->name,"WS");
        tkn->row = row;
        tkn->column = column;
        return 1;
    }
    return 0;
}
void print(struct token* tkn)
{
    printf("<%s,%d,%d,%d> ",tkn->name,tkn->row,tkn->column,tkn->lexeme_length);
}
void printST()
{
	for(int i =0;i<=in;i++)
	{
		printf("Index: %d, Lexeme: %s, Type: %s, Size: %d\n",i,table[i].lexeme,table[i].type,table[i].size);
	}
}
struct token* getNextToken()
{
    int f;
	char ca = getc(fp);
    while(ca=='#')
    {
        while(ca!='\n') ca = getc(fp);
        row++;
        ca = getc(fp);
    }
    if(ca==EOF) return NULL;
	f = 0;
    if (ca=='/')
	{
        int temp = ftell(fp);
	    ca = getc(fp);
	    if (ca == '/')
	    {
	        while(ca != '\n')
	        ca = getc(fp);
        }
        else if (ca == '*')
        {
	        do
	        {
		        while(ca != '*')
			    {
                    ca = getc(fp);
                    if(ca==10){ row++; column = 0;}
                }
		        ca = getc(fp);
	        }while (ca != '/');
            ca = getc(fp);
        }
        else
        {
            fseek(fp,temp,SEEK_SET);
        //    ca = getc(fp);
	    }
    }
        column++;
	    int temp = ftell(fp);
        int col = column;
		struct token *tkn;
        tkn = (struct token*) malloc(sizeof(struct token));
		if(getArithOp(tkn))
		{
//			print(tkn);
			return tkn;
		}
		else fseek(fp,temp,SEEK_SET);
        column = col;
		if(getRelOp(tkn))
		{
//				print(tkn);
				return tkn;
		}
		else fseek(fp,temp,SEEK_SET);
        column = col;
		if(getLogOp(tkn))
		{
//				print(tkn);
				return tkn;
		}
		else fseek(fp,temp,SEEK_SET);
        column = col;
        if(getSpecSym(tkn))
		{
//				print(tkn);
				return tkn;
		}
		else fseek(fp,temp,SEEK_SET);
        column = col;
		if(getUNo(tkn))
		{
//				print(tkn);
				return tkn;
		}
		else fseek(fp,temp,SEEK_SET);
        column = col;
		if(getStrLit(tkn))
		{
//				print(tkn);
				return tkn;
		}
		else fseek(fp,temp,SEEK_SET);
        column = col;
		if(getKeyword(tkn))
		{
//				print(tkn);
				return tkn;
		}
		else fseek(fp,temp,SEEK_SET);
        column = col;
		if(getID(tkn))
		{
//				print(tkn);
				return tkn;
		}
		else fseek(fp,temp,SEEK_SET);
        column = col;
		if(getWhitespace(tkn)) return getNextToken();
		strcpy(tkn->name,"Unidentified");
		tkn->row = row;
		tkn->column = column;
        print(tkn);
		return tkn;
}
/*
int main()
{
    int f;
	loadKeywords();
	fp = fopen("/home/rsk/LABS/CD_Lab/Lab6/lab6dummy.c","r");
	tkn = (struct token*) malloc(sizeof(struct token));
    while((tkn = getNextToken())!=NULL)
    {
        print(tkn);
    }
    printST();
    fclose(fp);
    return 0;
}*/