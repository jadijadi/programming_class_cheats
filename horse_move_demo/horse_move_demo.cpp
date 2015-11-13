#include <iostream>//needs these three lines
#include <stdlib.h>//needs these three lines
#include <stdio.h>


class PlayChess {
	int horsex, horsey;
	public:
		int sleepTime;
		void setHorseXY (int newx, int newy);
		void DrawBoard ();
};

void PlayChess::setHorseXY (int newx, int newy)
{
	horsex = newx*3-1;
	horsey = newy*2;
}
	
void PlayChess::DrawBoard()
{    
    system ("clear");	
    for(int y=0; y<18; y++)
        for(int x=0; x<26; x++)
            if(y==0)
                if(x==25)       printf(" \n");
                else if(x%3==2) putchar(65+(x/3)); // 65 mishe 'A' ezafash mikonim ba x/3 ke A...E ro benevise  
                else            putchar(' ');
            else if (y==1)
                if(x==0)        putchar(' ');
                else if(x==1)   putchar('|');
                else if(x==25)  printf("|\n");
                else if(x%3==1) putchar('-');
                else            putchar('=');
            else if(y==17)
                if(x==0)        putchar(' ');
                else if(x==1)   putchar('+');
                else if(x==25)  printf("|\n");
                else if(x%3==1) putchar('-');
                else            putchar('=');
            else if(y%2==1)
                if(x==0)        putchar(' ');
                else if(x==1)   putchar('|');
                else if(x==25)  printf("|\n");
                else if(x%3==1) putchar('+');
                else            putchar('-');
            else
                if (x==0)       putchar(48+(y/2)); // 48 code ascii 1 ast. jami mizanim ba nesfe Y ke adad haye samte rast ro eshoon bede
                else if(x==25)  printf("|\n");
                else if(x%3==1) putchar('|');
		else if(x == horsex && y==horsey) printf("@ "); // namayeshe asb
                else if(x%3==2) printf("  ");

		sleep(sleepTime);
}

int main()
{	
	PlayChess thisgame; 

	thisgame.sleepTime = 5;
	char movex [] = {3, 4, 5, 6, 6};
	char movey [] = {4, 4, 4, 4, 5};
	
	for (int i; i<sizeof(movex); i++)  {
		thisgame.setHorseXY (movex[i], movey[i]);
		thisgame.DrawBoard();
	}
}
