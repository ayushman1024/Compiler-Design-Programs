// Subject: Compiler , to find first of given symbol from supplied grammar
#include<stdio.h>
#include<string.h>

int prodCount;
//.....productions array......non-terminal[]............terminal[].............
char prod[30][30];
char nt[10];
char t[10];
//...............................................
char frst[20];      // stores first set
int frc;            // count firsts 
//..............................................
void first(char c,int hop);
int prevr,prevc;        // it will store row n col of previous called first()
int ntc;

//......................FIRST.........................
void first(char c,int hop)
{  
    int i,j;
    char res[20];
    int prodIndex = 0;
    if(c != '#')        // not a null
    {
        for(i=0;i<prodCount;i++) 
        {
            if(prod[i][0] == c){     //checks if non-terminal symbol
                prodIndex = i;
                hop = 0;
                first(prod[prodIndex][3+hop],hop); 
                prevr= prodIndex;
                prevc= 3 + hop;
            }
            else                    // if terminal
            {
                if(!strchr(frst,c) && !strchr(nt,c))    // if not already in set & not a Non-Terminal
                {
                    frst[frc] = c;
                    frc ++;
                }           
            }
        }
    }
    else
    {      // if it is null
        if(!strchr(frst,c))
        {
            frst[frc] = c;
            frc ++;
        }
        hop++;
        prevc = prevc + hop; 
        char d = prod[prevr][prevc+3];
        first(d , hop);
    }
}

//................MAIN..............................
int main()
{   
    int i,j=0,flag=0;
    frc = 0;
    printf("Number of productions? ");
    scanf("%d",&prodCount);
    for(i=0;i<prodCount;i++)
    {
        printf("Enter prod %d:  ",i);
        scanf("%s",prod[i]);
        nt[ntc] = prod[i][0];
        ntc++;
    }
    char ip[1];
    printf("Enter char symbol ? ");
    scanf("%s",ip);

        printf("\n first of %c is : {  ",ip[0]);
        first(ip[0],0);
        for(i=0;i<frc;i++)
        {
            printf(" %c",frst[i]);
        }
        printf(" }");
} 
/*
Number of productions? 5
Enter prod 0:  A->BCDx
Enter prod 1:  B->#
Enter prod 2:  C->#
Enter prod 3:  D->d
Enter prod 4:  D->e
Enter char symbol ? A

first of A is : {   # d e } 
 */


