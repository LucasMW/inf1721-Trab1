//
//  puzzleConfiguration.h
//  INF1721Trab1
//
//  Created by Lucas Menezes on 18/04/15.
//  Copyright (c) 2015 MWAPPTECH. All rights reserved.
//

#ifndef __INF1721Trab1__puzzleConfiguration__
#define __INF1721Trab1__puzzleConfiguration__

#include <stdio.h>
#define boardLimit 9
#define boardRows 3
#define boardColumns 3
typedef struct board* Board;
typedef enum
{   One=1,
    Two=2 ,
    Three=3 ,
    Four=4,
    Five=5,
    Six=6,
    Seven=7,
    Eight=8,
    Void = '-'
    
} BoardPieces;
typedef enum
{
    True='$',
    False=0
    
} bit;
Board createBoard(Board board, BoardPieces pieces[boardLimit] );
BoardPieces** adjacentConfigs(Board board,int* refTam);
Board* generateBoardsFromConfigurationVectors(BoardPieces** piecesVector, int cont);
bit boardCompare(Board b1, Board b2);
void printBoardConfiguration(BoardPieces* pieces);
void printBoardConfigurations(BoardPieces** boardPiecesVector,int tam);
void printBoard(Board b);
void boardDestroy(Board b);
int boardGetId(Board b);
void boardSetId(Board b,int id);
#endif /* defined(__INF1721Trab1__puzzleConfiguration__) */
