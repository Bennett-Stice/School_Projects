#include <iostream>
#include <fstream>

using namespace std;

#define BOARDSIZE 9
int board[BOARDSIZE][BOARDSIZE];
int rownum;
int colnum;
int xHold;
int yHold;

void printBoard(int outBoard[BOARDSIZE][BOARDSIZE])
{
    cout<<"-------------------------"<<endl;
    for (int row=0;row<BOARDSIZE;row++)
    {
        for (int col=0;col<BOARDSIZE;col++)
        {
            if ((row==3||row==6)&&col==0)
            {
                cout<<"-------------------------"<<endl;
            }
            if (col==0||col==3||col==6)
            {
                cout<<"| ";
            }
            if (outBoard[row][col]==0)
            {
                cout<<'_'<<' ';
            }
            else
            {
                cout<<outBoard[row][col]<<' ';
            }
            if (col==8)
            {
                cout<<'|'<<endl;
            }
        }
    }
    cout<<"-------------------------"<<endl;
}

bool checkCol (int outBoardC[BOARDSIZE][BOARDSIZE],int xLocC,int yLocC,int posInValC)
{
    for (int i=0;i<BOARDSIZE;i++)
    {
        if (outBoardC[i][yLocC]==(posInValC))
        {
            return false;
        }
    }
    return true;
}

bool checkRow (int outBoardR[BOARDSIZE][BOARDSIZE],int xLocR,int yLocR,int posInValR)
{
    for (int i=0;i<BOARDSIZE;i++)
    {
        if (outBoardR[xLocR][i]==(posInValR))
        {
            return false;
        }
    }
    return true;
}

int findSector(int xIn,int yIn)
{
    if (xIn<3&&yIn<3)
        return 1;
    if (xIn>=3&&xIn<6&&yIn<3)
        return 2;
    if (xIn>=6&&yIn<3)
        return 3;
    if (xIn<3&&yIn>=3&&yIn<6)
        return 4;
    if (xIn>=3&&xIn<6&&yIn>=3&&yIn<6)
        return 5;
    if (xIn>=6&&yIn>=3&&yIn<6)
        return 6;
    if (xIn<3&&yIn>=6)
        return 7;
    if (xIn>=3&&xIn<6&&yIn>=6)
        return 8;
    if (xIn>=6&&yIn>=6)
        return 9;
    return 0;
}
/*
void checkBoxHelper(int outBoardBH[BOARDSIZE][BOARDSIZE],int xStart,int xStop,int yStart,int yStop,int posInValBH,bool trigger)
{
    for (int x=xStart;x<xStop;x++)
    {
        for (int y=yStart;y<yStop;y++)
        {
            if (outBoardBH[x][y]==posInValBH)
            {
                trigger=false;
            }
        }
    }
}

bool checkBox(int outBoardB[BOARDSIZE][BOARDSIZE],int xLocB,int yLocB,int posInValB)
{
    int sector=findSector(xLocB,yLocB);
    bool goodbox=true;

    if (sector==1)
    {
        checkBoxHelper(outBoardB,0,3,0,3,posInValB,goodbox);
    }

    if (sector==2)
    {
        checkBoxHelper(outBoardB,3,6,0,3,posInValB,goodbox);
    }

    if (sector==3)
    {
        checkBoxHelper(outBoardB,6,9,0,3,posInValB,goodbox);
    }

    if (sector==4)
    {
        checkBoxHelper(outBoardB,0,3,3,6,posInValB,goodbox);
    }

    if (sector==5)
    {
        checkBoxHelper(outBoardB,3,6,3,6,posInValB,goodbox);
    }

    if (sector==6)
    {
        checkBoxHelper(outBoardB,6,9,3,6,posInValB,goodbox);
    }

    if (sector==7)
    {
        checkBoxHelper(outBoardB,0,3,6,9,posInValB,goodbox);
    }

    if (sector==8)
    {
        checkBoxHelper(outBoardB,3,6,6,9,posInValB,goodbox);
    }

    if (sector==9)
    {
        checkBoxHelper(outBoardB,6,9,6,9,posInValB,goodbox);
    }

    return goodbox;

}
*/

bool checkBox(int outBoardB[BOARDSIZE][BOARDSIZE],int xLocB,int yLocB,int posInValB)
{
    int sector = findSector(xLocB,yLocB);

    //check sector 1
    if (sector ==1)
    {
        for (int x=0;x<3;x++)
        {
            for (int y=0;y<3;y++)
            {
                if (outBoardB[x][y]==(posInValB))
                {
                    return false;
                }
            }
        }
    }

    //check sector 2
    if (sector ==2)
    {
        for (int x=3;x<6;x++)
        {
            for (int y=0;y<3;y++)
            {
                if (outBoardB[x][y]==(posInValB))
                {
                    return false;
                }
            }
        }
    }

    //check sector 3
    if (sector ==3)
    {
        for (int x=6;x<9;x++)
        {
            for (int y=0;y<3;y++)
            {
                if (outBoardB[x][y]==(posInValB))
                {
                    return false;
                }
            }
        }
    }

    //check sector 4
    if (sector ==4)
    {
        for (int x=0;x<3;x++)
        {
            for (int y=3;y<6;y++)
            {
                if (outBoardB[x][y]==(posInValB))
                {
                    return false;
                }
            }
        }
    }

    //check sector 5
    if (sector ==5)
    {
        for (int x=3;x<6;x++)
        {
            for (int y=3;y<6;y++)
            {
                if (outBoardB[x][y]==(posInValB))
                {
                    return false;
                }
            }
        }
    }

    //check sector 6
    if (sector ==6)
    {
        for (int x=6;x<9;x++)
        {
            for (int y=3;y<6;y++)
            {
                if (outBoardB[x][y]==(posInValB))
                {
                    return false;
                }
            }
        }
    }

    //check sector 7
    if (sector ==7)
    {
        for (int x=0;x<3;x++)
        {
            for (int y=6;y<9;y++)
            {
                if (outBoardB[x][y]==(posInValB))
                {
                    return false;
                }
            }
        }
    }

    //check sector 8
    if (sector ==8)
    {
        for (int x=3;x<6;x++)
        {
            for (int y=6;y<9;y++)
            {
                if (outBoardB[x][y]==(posInValB))
                {
                    return false;
                }
            }
        }
    }

    //check sector 9
    if (sector==9)
    {
        for (int x=6;x<9;x++)
        {
            for (int y=6;y<9;y++)
            {
                if (outBoardB[x][y]==(posInValB))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool checkSequence (int outBoardS[BOARDSIZE][BOARDSIZE],int xLocS,int yLocS,int posInValS)
{
    if (checkRow(outBoardS,xLocS,yLocS,posInValS)&&(checkCol(outBoardS,xLocS,yLocS,posInValS))&&(checkBox(outBoardS,xLocS,yLocS,posInValS)))
    {
        return true;
    }

    return false;
}

bool completionCheck (int outBoard[BOARDSIZE][BOARDSIZE])
{
    for (int x=0;x<BOARDSIZE;x++)
    {
        for (int y=0;y<BOARDSIZE;y++)
        {
            if (outBoard[x][y]==0)
            {
                return false;
            }
        }
    }
    return true;
}

void sectorSolverHelper(int outBoardSSH[BOARDSIZE][BOARDSIZE],int xStart,int xStop,int yStart, int yStop)
{
    int validEntries=0;
    for (int posIn=1;posIn<=BOARDSIZE;posIn++)
    {
        for (int sX=xStart;sX<xStop;sX++)
        {
            for (int sY=yStart;sY<yStop;sY++)
            {
                if ((outBoardSSH[sX][sY]==0)&&checkSequence(outBoardSSH,sX,sY,posIn))
                {
                    validEntries++;
                    xHold=sX;
                    yHold=sY;
                }
            }
        }
        if (validEntries==1)
        {
            outBoardSSH[xHold][yHold]=(posIn);
        }
        validEntries=0;
    }

}



void sectorSolver(int outBoardSS[BOARDSIZE][BOARDSIZE])
{
    for (int x=0;x<BOARDSIZE;x+=3)
    {
        for (int y=0;y<BOARDSIZE;y+=3)
        {
            int sector=findSector(x,y);

            if (sector==1)
            {
                sectorSolverHelper(outBoardSS,0,3,0,3);
            }

            if (sector==2)
            {
                sectorSolverHelper(outBoardSS,3,6,0,3);
            }

            if (sector==3)
            {
                sectorSolverHelper(outBoardSS,6,9,0,3);
            }

            if (sector==4)
            {
                sectorSolverHelper(outBoardSS,0,3,3,6);
            }

            if (sector==5)
            {
                sectorSolverHelper(outBoardSS,3,6,3,6);
            }

            if (sector==6)
            {
                sectorSolverHelper(outBoardSS,6,9,3,6);
            }

            if (sector==7)
            {
                sectorSolverHelper(outBoardSS,0,3,6,9);
            }

            if (sector==8)
            {
                sectorSolverHelper(outBoardSS,3,6,6,9);
            }

            if (sector==9)
            {
                sectorSolverHelper(outBoardSS,6,9,6,9);
            }
        }
    }
}

void numberSolverHelper(int outBoardNSH[BOARDSIZE][BOARDSIZE],int xStart,int xStop,int yStart,int yStop,int posEntry)
{
    int validEntries=0;

    for (int sX=xStart;sX<xStop;sX++)
    {
        for (int sY=yStart;sY<yStop;sY++)
        {
            if ((outBoardNSH[sX][sY]==0)&&checkSequence(outBoardNSH,sX,sY,posEntry))
            {
                validEntries++;
                xHold=sX;
                yHold=sY;
            }
        }
    }
    if (validEntries==1)
    {
        outBoardNSH[xHold][yHold]=(posEntry);
    }
    validEntries=0;
}

void numberSolver(int outBoardNS[BOARDSIZE][BOARDSIZE])
{
    for (int posIn=1;posIn<=BOARDSIZE;posIn++)
    {
        for (int y=0;y<BOARDSIZE;y++)
        {
            for (int x=0;x<BOARDSIZE;x++)
            {
                int sector=findSector(x,y);

                if (sector==1)
                {
                    numberSolverHelper(outBoardNS,0,3,0,3,posIn);
                }

                if (sector==2)
                {
                    numberSolverHelper(outBoardNS,3,6,0,3,posIn);
                }

                if (sector==3)
                {
                    numberSolverHelper(outBoardNS,6,9,0,3,posIn);
                }

                if (sector==4)
                {
                    numberSolverHelper(outBoardNS,0,3,3,6,posIn);
                }

                if (sector==5)
                {
                    numberSolverHelper(outBoardNS,3,6,3,6,posIn);
                }

                if (sector==6)
                {
                    numberSolverHelper(outBoardNS,6,9,3,6,posIn);
                }

                if (sector==7)
                {
                    numberSolverHelper(outBoardNS,0,3,6,9,posIn);
                }

                if (sector==8)
                {
                    numberSolverHelper(outBoardNS,3,6,6,9,posIn);
                }

                if (sector==9)
                {
                    numberSolverHelper(outBoardNS,6,9,6,9,posIn);
                }
            }
        }
    }
}

void boxSolver(int outBoardBS[BOARDSIZE][BOARDSIZE])
{
    int validEntries=0;
    int entryHold=0;

    for (int y=0;y<BOARDSIZE;y++)
    {
        for (int x=0;x<BOARDSIZE;x++)
        {
            if (outBoardBS[x][y]==0)
            {
                validEntries=0;
                for (int posIn=1;posIn<=BOARDSIZE;posIn++)
                {
                    if (checkSequence(outBoardBS,x,y,posIn))
                    {
                        validEntries++;
                        entryHold=posIn;
                    }
                }
                if(validEntries==1)
                {
                    outBoardBS[x][y]=(entryHold);
                }
            }
        }
    }
}

int emptySlotsCounter(int outBoardESC[BOARDSIZE][BOARDSIZE])
{
    int slotsLeft=0;

    for (int x=0;x<BOARDSIZE;x++)
    {
        for (int y=0;y<BOARDSIZE;y++)
        {
            if (outBoardESC[x][y]==0)
            {
                slotsLeft++;
            }
        }
    }

    return slotsLeft;
}

int main (int argc, char *argv[])
{


    //This ask the user for the name of the input file and reads it into the program so we can get values from it later.
    string fname;
    cout<< "What is the name of the sodoku file? ";
    cin>>fname;

    //ifstream reader(fname);
    ifstream reader("easypuzzle2.txt");

    //If the user types in a file that can't be found, this tells them that.
    if (!reader)
    {
        cerr<<"Could not open " <<fname<<endl;
        return 1;
    }

    //This populates our array with char values from the file.

    for (int i=0; i<BOARDSIZE;i++)
    {
        for (int j=0; j<BOARDSIZE; j++)
        {
            reader>> board[i][j];
        }
    }

    //print out current board to be solved
    printBoard(board);

    int passesToCompletion=0;

    while(!completionCheck(board))
    {

        sectorSolver(board);
        numberSolver(board);
        boxSolver(board);

        passesToCompletion++;

        printBoard(board);

        //emptySlotsCounter(board);
        cout<<"There are "<<emptySlotsCounter(board)<<" spots left."<<endl;
    }


    //print out completed board
    printBoard(board);

    cout<<"It took "<<passesToCompletion<<" passes to complete."<<endl;


    return 0;
}
