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
   int permutIndex;
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

static Board allPossibilities[boardPossibilities];

int boardPermutIndex(Board b)
{
    return permutationIndex(b->squares);
}
int permutationIndex(BoardPieces* pieces)
{
    int index = 0;
    int position = 2;// position 1 is paired with factor 0 and so is skipped
    int factor = 1;
    for (int p = 9 - 2; p >= 0; p--) {
        int successors = 0;
        for (int q = p + 1; q < 9; q++) {
            if (pieces[p] > pieces[q]) {
                successors++;
            }
        }
        index += (successors * factor);
        factor *= position;
        position++;
    }
    return index;
}


static void swap (BoardPieces *x, BoardPieces *y)
{
    BoardPieces temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
int permute(Board b, int i, int n)
{
    int j;
    static int k=0;
//    if(k==0)
//    {
//        printf("orBoard\n");
//        printBoard(b);
//    }
    if (i == n)
    {
        b=createBoard(b,b->squares);
       // b->permutIndex=k;
        printf("k: %d permut: %d\n",k,b->permutIndex);
        printBoard(b);
        allPossibilities[b->permutIndex]=b;
        k++;
    }
    else
    {
        for (j = i; j <= n; j++)
        {
            
            swap(b->squares+i, b->squares+j) ;//swap((a+i), (a+j));
            permute(b, i+1, n);
            swap(b->squares+i, b->squares+j) ; //swap((a+i), (a+j)); //backtrack
        }
    }
    return k;
}
Board* generateAllPossibilities(Board orBoard)
{
    int i,k;
    k=permute(orBoard, 0, 8);
    for(i=0;i<k;i++)
    {
        printf("index %d, permut %d\n",i,allPossibilities[i]->permutIndex);
        printBoard(allPossibilities[i]);
    }
    
    return allPossibilities;
}
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
    board->permutIndex= permutationIndex(pieces);
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
           // printf("(%d,%d)\n",*i,*j);
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
bit boardCompare(Board b1, Board b2)
{
    int i=0;
    //printf("Boards CMP\n");
    
    //printBoard(b1);
    //printBoard(b2);
    //printf("END Boards CMP\n");
    for(i=0;i<boardLimit;i++)
    {
        if(b1->squares[i]!=b2->squares[i])
            return False;
    }
    return True;
}
BoardPieces** adjacentConfigs(Board board,int* refTam)
{
    char voidPosition;
    int row,column;
    int cont;
    BoardPieces** configs;
    configs=(BoardPieces**)malloc(sizeof(BoardPieces*)*4);
    findVoidAsMatrix((BoardPieces*)board->squares, &row, &column);
    //printf("void found on position [%d,%d]\n",row,column);
    
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
        //printf("%d down\n",cont);
        cont++;
        
    }
    if(column+1<boardColumns)
    {
        configs[cont]= (BoardPieces*)malloc(sizeof(BoardPieces)*boardLimit);
        MCopy(board->squares, (Matrix)configs[cont], boardColumns);
        swapX(&((configs[cont])[MIndex(row, column+1, boardRows)]), &((configs[cont])[MIndex(row, column, boardRows)]));
        //printf("%d right\n",cont);
        cont++;
        
    }
    if(column-1>=0)
    {
        configs[cont]= (BoardPieces*)malloc(sizeof(BoardPieces)*boardLimit);
        MCopy(board->squares, (Matrix)configs[cont], boardColumns);
        swapX(&((configs[cont])[MIndex(row, column-1, boardRows)]), &((configs[cont])[MIndex(row, column, boardRows)]));
        //printf("%d left\n",cont);
        cont++;
        
    }
    if(row-1>=0)
    {
        configs[cont]= (BoardPieces*)malloc(sizeof(BoardPieces)*boardLimit);
        MCopy(board->squares, (Matrix)configs[cont], boardColumns);
        swapX(&((configs[cont])[MIndex(row-1, column, boardRows)]), &((configs[cont])[MIndex(row, column, boardRows)]));
        //printf("%d up\n",cont);
        cont++;
        
    }
    *refTam=cont;
    #ifdef this_debug
    printf("Board: \n");
    printBoard(board);
    printf("generated %d configurations:\n",cont);
    
    printBoardConfigurations(configs, cont);
    printf("end\n");
    #endif
    return configs;
    
    
    
}


