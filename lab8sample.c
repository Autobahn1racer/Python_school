#include<stdio.h>
#include<stdlib.h>
main()
{
    int a,b[10],c,d,e[12];
    char str[10],f;
    a = c * 10 + d % 2;
    d = 2;
    // This is a single line comment
    if (d != 2)
    {
        if(c>=5)
        {
            while(c>5)
            {
                c = c-1;
            }
        }
        else
        {
            /* This is a multi-
                line comment */
            if(c<=5)
            {
                while(c<5)
                {
                    c = c +1;
                }
            }
        }
    }
    d = d / 10;
    for(a = 2; a < 6; a = a+1)
    {
        if(a==2)
        {
            a=4;
        }
    }
}$