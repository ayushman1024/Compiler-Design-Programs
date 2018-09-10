// Subject: Compiler , to find follow of given symbol from given grammar

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
char folw[20];      // stores follow
int fwc;            // count follows
//..............................................
int firstForFollow(char c,int hop);
int prevr,prevc;        // it will store row n col of previous called first()

void follow(char c);
int ntc;

//.................FOLLOW.............................
void follow(char c)
{
    int i,j;
    for(i=0;i<prodCount;i++)
    {
        for(j=3;prod[i][j]!='\0';j++)
        {
            if(prod[i][j] == c )
            {
                if(prod[i][j+1]!='\0')  // if its not at last of production
                { 
                    int hop = 1;
                    while(1>0)
                    {
                        int nu = firstForFollow(prod[i][j+hop],0);
                        if(nu == 1)
                            hop = hop + 1;
                        else
                            break;
                    }
                    strcat(folw,frst);
                }
                else
                {
                    follow(prod[i][0]);  // if its last,then find follow of LHS
                }
            }
        }
    }

    if(prod[0][0] == c)
    {                        // if it is also a start symbol
        if(!strchr(frst,'$'))
        {
            strcat(folw,"$");
            fwc ++;
        }
    }
}

int firstForFollow(char c,int hop)
{  
    int i,j;
    int nu = 0; // nu = 1 when first contains #
    int prodIndex = 0;
    if(c != '#')        // not a null
    {
        for(i=0;i<prodCount;i++) 
        {
            if(prod[i][0] == c){     //checks if non-terminal symbol
                prodIndex = i;
                hop = 0;
                firstForFollow(prod[prodIndex][3+hop],hop); 
                prevr= prodIndex;
                prevc= 3 + hop;
            }
            else                    // if terminal
            {
                if(!strchr(frst,c) && !strchr(nt,c))    // if not already in set & not a Non-Terminal
                {
                    char x[] = "" ;
                    x[0] = c;
                    strcat(frst,x);
                }           
            }
        }
    }
    else
    {      // if it is null
        nu = 1;
        if(!strchr(frst,c))
        {
            //strcat(frst,c);
        }
        hop++;
        prevc = prevc + hop; 
        char d = prod[prevr][prevc+3];
        firstForFollow(d , hop);
    }
    return nu;
}

//..............................................
int main()
{   
    int i,j=0;
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
    printf("\n follow of %c is : {  ",ip[0]);
    follow(ip[0]);
    printf(" %s",folw);
    printf(" }");
} 
/*Main ends*/


