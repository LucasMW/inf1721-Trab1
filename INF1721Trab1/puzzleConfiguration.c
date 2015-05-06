//
//  puzzleConfiguration.c
//  INF1721Trab1
//
//  Created by Lucas Menezes on 18/04/15.
//  Copyright (c) 2015 MWAPPTECH. All rights reserved.
//

#include "puzzleConfiguration.h"
#include "vectorAsMatrix.h"
#include <stdlib.h>

#define _thisDebug
struct board
{
   char squares[boardLimit];
    //char squareMatrix[boardRows][boardColumns];
};
typedef enum
{    upLeftRoom =0,
     upMiddleRoom ,
     upRightRoom ,
     middleRightRoom,
     middleMiddleRoom,
     middleLeftRoom,
     downRightRoom,
     downMiddleRoom,
     downLeftRoom
    
} boardSQUARES;

typedef enum
{
    True='$',
    False=0
    
} bit;



static bit checkRepeatedBoardPieces(Board board)
{
    int i;
    BoardPieces pieces[boardLimit];
    
    for(i=0;i<boardLimit;i++)
    {
        pieces[i]=0;
        
    }
    for(i=0;i<boardLimit;i++)
    {
        pieces[board->squares[i]]++;
        
    }
    for(i=0;i<boardLimit;i++)
    {
        if(pieces[i]>1)
            return True;
        
    }
    
    
    return False;
}
Board createBoard(Board board, BoardPieces pieces[boardLimit] )
{   int i;
    
    board = (Board)malloc(sizeof(struct board));
    for(i=0;i<boardLimit;i++)
    {
        board->squares[i]=pieces[i];
    }
    if(!checkRepeatedBoardPieces(board))
        return board;
    return NULL;
    
}
static char findVoid(Board board)
{
    char i;
    for(i=0;i<boardLimit;i++)
        if(board->squares[i]==Void)
            break;
    return i;
}
static void findVoidAsMatrix(BoardPieces* config,int* i,int* j)
{
    for(*i=0;*i<boardRows;i++)
    {
        for(*j=0;*j<boardColumns;j++)
        {
            if(config[MIndex(*i, *j, boardRows)]==Void)
                break;
        }
    }
}
static void swapX(BoardPieces * a, BoardPieces* b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
BoardPieces** adjacentConfigs(Board board)
{
    char voidPosition;
    int row,column;
    int cont;
    BoardPieces** configs;
    findVoidAsMatrix(board->squares, &row, &column);
    
    /* candidates
     void[i][j+1] //to the right
     void[i][j-1] //to the left
     void[i+1][j] // down
     void[i-1][j] // up
     */
    cont=0;
    if(row+1<boardRows)
    {
        configs[cont]= (BoardPieces*)malloc(sizeof(BoardPieces)*boardLimit);
        MCopy(board->squares, configs[cont], boardColumns);
        swapX(&((configs[cont])[MIndex(row+1, column, boardRows)]), &((configs[cont])[MIndex(row, column, boardRows)]));
        cont++;
        
    }
    if(column+1>boardColumns)
    {
        configs[cont]= (BoardPieces*)malloc(sizeof(BoardPieces)*boardLimit);
        MCopy(board->squares, configs[cont], boardColumns);
        swapX(&((configs[cont])[MIndex(row, column+1, boardRows)]), &((configs[cont])[MIndex(row, column, boardRows)]));
        cont++;
        
    }
    if(column-1>0)
    {
        configs[cont]= (BoardPieces*)malloc(sizeof(BoardPieces)*boardLimit);
        MCopy(board->squares, configs[cont], boardColumns);
        swapX(&((configs[cont])[MIndex(row, column-1, boardRows)]), &((configs[cont])[MIndex(row, column, boardRows)]));
        cont++;
        
    }
    
    return configs;
    
    
    
}


