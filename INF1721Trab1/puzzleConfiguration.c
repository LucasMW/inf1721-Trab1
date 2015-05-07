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
   BoardPieces squares[boardLimit];
   int id;
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
void printBoard(Board b)
{
//    int i;
//    
//    for(i=0;i<boardLimit;i+=3)
//    {
//        printf("| %.2d %.2d %.2d |\n",b->squares[i],b->squares[i+1],b->squares[i+2]);
//    }
    printBoardConfiguration(b->squares);
}
void printBoardConfiguration(BoardPieces* pieces)
{
    int i;
    for(i=0;i<boardLimit;i+=3)
    {
        printf("| %.2d %.2d %.2d |\n",pieces[i],pieces[i+1],pieces[i+2]);
    }
}
void printBoardConfigurations(BoardPieces** boardPiecesVector,int tam)
{
    int i;
    for(i=0;i<tam;i++)
    {
        printf("%d\n",i);
        printBoardConfiguration(boardPiecesVector[i]);
        printf("\n");
    }
}

Board createBoard(Board board, BoardPieces pieces[boardLimit] )
{   int i;
    
    board = (Board)malloc(sizeof(struct board));
    board->id=0;
    for(i=0;i<boardLimit;i++)
    {
        board->squares[i]=pieces[i];
    }
    if(!checkRepeatedBoardPieces(board))
        return board;
    return NULL;
    
}
Board* generateBoardsFromConfigurationVectors(BoardPieces** piecesVector, int cont)
{
    Board* boardVector;
    int i;
    boardVector=(Board*)malloc(sizeof(Board)*cont);
    for(i=0;i<cont;i++)
    {
        boardVector[i]=createBoard(boardVector[i], piecesVector[i]);
    }
    return boardVector;
}

static char findVoid(Board board)
{
    char i;
    for(i=0;i<boardLimit;i++)
        if(board->squares[i]==Void)
            break;
    return i;
}
static bit findVoidAsMatrix(BoardPieces* config,int* i,int* j)
{
    for(*i=0;*i<boardRows;(*i)++)
    {
        for(*j=0;*j<boardColumns;(*j)++)
        {
            printf("(%d,%d)\n",*i,*j);
            if(config[MIndex(*i, *j, boardRows)]==Void)
                return True;
        }
    }
    return False;
}
int boardGetId(Board b)
{
    return b->id;
}
void boardSetId(Board b,int id)
{
    b->id=id;
}
static void swapX(BoardPieces * a, BoardPieces* b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
void boardDestroy(Board b)
{
    free(b->squares);
    //free(b);
}
BoardPieces** adjacentConfigs(Board board,int* refTam)
{
    char voidPosition;
    int row,column;
    int cont;
    BoardPieces** configs;
    configs=(BoardPieces**)malloc(sizeof(BoardPieces*)*4);
    findVoidAsMatrix((BoardPieces*)board->squares, &row, &column);
    
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
        MCopy(board->squares, (Matrix)configs[cont], boardColumns);
        swapX(&((configs[cont])[MIndex(row+1, column, boardRows)]), &((configs[cont])[MIndex(row, column, boardRows)]));
        cont++;
        
    }
    if(column+1>boardColumns)
    {
        configs[cont]= (BoardPieces*)malloc(sizeof(BoardPieces)*boardLimit);
        MCopy(board->squares, (Matrix)configs[cont], boardColumns);
        swapX(&((configs[cont])[MIndex(row, column+1, boardRows)]), &((configs[cont])[MIndex(row, column, boardRows)]));
        cont++;
        
    }
    if(column-1>0)
    {
        configs[cont]= (BoardPieces*)malloc(sizeof(BoardPieces)*boardLimit);
        MCopy(board->squares, (Matrix)configs[cont], boardColumns);
        swapX(&((configs[cont])[MIndex(row, column-1, boardRows)]), &((configs[cont])[MIndex(row, column, boardRows)]));
        cont++;
        
    }
    if(row-1>0)
    {
        configs[cont]= (BoardPieces*)malloc(sizeof(BoardPieces)*boardLimit);
        MCopy(board->squares, (Matrix)configs[cont], boardColumns);
        swapX(&((configs[cont])[MIndex(row-1, column, boardRows)]), &((configs[cont])[MIndex(row, column, boardRows)]));
        printBoardConfiguration(configs[cont]);
        cont++;
        
    }
    *refTam=cont;
    printf("isdhj\n");
    printBoardConfigurations(configs, cont);
    return configs;
    
    
    
}


