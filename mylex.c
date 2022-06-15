 #include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>
 #include<string.h>
 #include<sys/types.h>
 #include<sys/types.h>
 #include<fcntl.h>
 #include<ctype.h>
 #define retract fseek(fp,-1,SEEK_CUR)
 int row=1,col=0,flag=0,in=-1;
 char dtbuf[20];
 char* keywords[33]={"int","double","printf","main","for","char"};
 FILE* fp;
 struct token 
 {
     char name[30];
     int row;
     int col;
     int lex_length;
 };
 struct token *tkn;
 int isKeyword(char *str)
 {
     int i;
     for(i = 0;i<6;i++)
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
     tkn=(struct token*)malloc(sizeof(struct token*));
     flag=0;
     row=0;
     col=0;
     in=-1;
 }
 int isDatatype(char *str)
 {
     if(strcmp("int",str)==0||strcmp("float",str)==0||strcmp("char",str)==0||strcmp("double",str)==0)
     {
         return 1;
     }
     return 0;
 }
 int getKeyword(struct token* tkn)
 {
     retract;
     char word[81];
     int temp=col;
     int l=0;
     char c = getc(fp);
     while(isalpha(c))
     {
         word[l++]=c;
         col++;
         c=getc(fp);
     }
     retract;
     word[l]=0;
     if(isKeyword(word))
     {
         if(isDatatype(word))
         {
             strcpy(dtbuf,word);
         }
         tkn->row=row;
         tkn->col=temp;
         strcpy(tkn->name,word);
         tkn->lex_length=strlen(word);
         return 1;
     }
     else
        col=temp;

    return 0;
 }
 int getStrLit(struct token* tkn)
 {
     //retract;
     int temp=col;
     char c=getc(fp);
     int l=0;
     if(c=='"')
     {
         tkn->col=col;
         while((c=getc(fp))!='"'&& c!=EOF)
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
 int getID(struct token* tkn)
 {
     //retract;
     char word[81];
     int temp=col;
     char c=getc(fp);
     int l=0;
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
     strcpy(tkn->name,"id");
     tkn->lex_length=strlen(word);
     return 1;
 }
 int getSS(struct token* tkn)
 {
     //retract;
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
     return 0;
 }
 int getWhiteSpaces(struct token* tkn)
 {
    //retract;
    col=col-1;
    char c = getc(fp);
    if(c=='\t'||c=='\n'||c==' '||c=='\r'||c=='\0')
    {
        if(flag)
            printf("%c",c);

        if(c=='\n')
        {
            row++;
            col=0;
        }
        if(c=='\t')
        {
            col=col+4;
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
    //retract;
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
        strcpy(tkn->name,"number");
        tkn->lex_length=temp-col;
        return 1;
    } 
    col=temp;
    return 0;
 }

 void ungetToken()
 {
     fseek(fp,-(tkn->lex_length),SEEK_CUR);
     col=col-(tkn->lex_length - 1);
 }
 struct token* getNextToken()
 {
     int curr=ftell(fp);
     char c = getc(fp);
     if(c==EOF)
     {
         return NULL;
     }
     col++;
     struct token* tkn;
     tkn = (struct token*)malloc(sizeof(struct token));
     int temp = col;

     if(getKeyword(tkn))
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

     if(getWhiteSpaces(tkn))
     {
         return getNextToken();
     }
     return (tkn);
 }
 void print(struct token* tkn)
 {
     printf("<%s,%d,%d,%d>\n",tkn->name,tkn->row,tkn->col,tkn->lex_length);
 }

// int main()
// {
// 	fp = fopen("bruh.c","r");
// 	struct token* tkn;
// 	tkn = (struct token*) malloc(sizeof(struct token));
// 	while((tkn=getNextToken())!=NULL)
// 	{
// 		print(tkn);
// 	}
// 	printf("\n");
// 	fclose(fp);
// 	return 0;
// }