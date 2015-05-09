//
//  main.c
//  INF1721Trab1
//
//  Created by Lucas Menezes on 18/04/15.
//  Copyright (c) 2015 MWAPPTECH. All rights reserved.
//

#include <stdio.h>

#include "puzzleConfiguration.h"
#include "grafo.h"

Board boardFinal;
GRA_tppGrafo grafoGlobal;
bit boardIsInAlreadyOnGraph(GRA_tppGrafo grafo, Board b)
{
    int * ids;
    int tam;
    int i;
    Board currentBoard;
    GRA_ObterVertices(grafo, &ids, &tam);
    for(i=0;i<tam;i++)
    {
        printf("v: %d\n ",i);
        GRA_ObterValorNo(grafo, ids[i], (void**)&currentBoard);
        if(boardCompare(b, currentBoard)==True)
            return True;
        
    }
    return False;
}

void verifyAdjacents(Board orBoard, Board* adjBoards, int cont)
{
    int i;
    int tempInt;
    BoardPieces** newAdj;
    Board* newBoards;
    static int k=0;
    if(boardCompare(orBoard,boardFinal)==True)
    {
        printf("Found\n");
        return;
    }
    k++;
    for(i=0;i<cont;i++)
    {
        printf("k: %d\n",k);
        printBoard(adjBoards[i]);
        
        if(boardCompare(adjBoards[i],boardFinal)==True)
        {
            printf("Found\n");
            
            GRA_InserirAresta(grafoGlobal, boardGetId(adjBoards[i]), boardGetId(boardFinal), 1);
            return;
        }
        if(!boardIsInAlreadyOnGraph(grafoGlobal, adjBoards[i]))
        {
            printf("Not on Graph\n");
            GRA_InserirNo(grafoGlobal,adjBoards[i] ,&tempInt);
            boardSetId(adjBoards[i], tempInt);
            GRA_InserirAresta(grafoGlobal, boardGetId(adjBoards[i]), boardGetId(orBoard), 1);
            newAdj=adjacentConfigs(adjBoards[i], &tempInt);
            newBoards=generateBoardsFromConfigurationVectors(newAdj, tempInt);
            verifyAdjacents(adjBoards[i], newBoards, tempInt);
            
        }
    }
}
int main(int argc, const char * argv[])
{
    // insert code here...
    Board b,b2,bF;

    BoardPieces pieces[boardLimit]={One,Two,Three,Four,Five,Six,Seven,Eight,Void};
    BoardPieces pieces2[boardLimit]={One,Two,Three,Three,Five,Seven,Eight,Void};
    //BoardPieces finalConfiguration[boardLimit]={Void,Three,Five,Eight,Two,Seven,One,Four,Six};
    BoardPieces finalConfiguration[boardLimit]={Void,Two,Three,One,Four,Five,Seven,Eight,Six};
    //BoardPieces finalConfiguration[boardLimit]={One,Two,Three,Four,Five,Six,Seven,Void,Eight};
    BoardPieces** adjcConfig;
    
    Board* boards;
    GRA_tppGrafo grafo;
    bit flag1;
    bit flag2;
    int* ids;
  
    int cont;
    int i;
    int tempInt;
    b=createBoard(b, pieces);
    if(b)
    {
        printf("b created\n");
        printBoard(b);
    }
    else
        printf("failed\n");
    b2=createBoard(b2, pieces2);
    if(b2)
        printf("b2 created\n");
    else
        printf("failed\n");
    b=createBoard(b, pieces);
    bF=createBoard(bF, finalConfiguration);
    if(bF)
    {
        printf("bF created\n");
        printBoard(bF);
    }
    else
        printf("failed\n");
    
    
	//part that Really matters
    adjcConfig=adjacentConfigs(b,&cont);
    printf("cont %d\n",cont);
    printBoardConfigurations(adjcConfig, cont);
    boards=generateBoardsFromConfigurationVectors(adjcConfig,cont);
    
    GRA_CriarGrafo(&grafo, (void*)boardDestroy);
    GRA_InserirNo(grafo, b, &tempInt);
    boardSetId(b, tempInt); //sets initial configuration
    
    GRA_InserirNo(grafo,bF ,&tempInt);
    boardSetId(bF, tempInt); //sets final configuration
    flag1=False;
    boardFinal=bF;
    grafoGlobal=grafo;
    verifyAdjacents(b, boards, cont);
    
    
    GRA_ImprimirGrafo(grafo);
    GRA_DFS(grafo, &ids, &cont, boardGetId(b));
    if(GRA_ExisteCaminho(grafo, boardGetId(b), boardGetId(bF))==GRA_CondRetCaminhoExiste)
        printf("There is\n");
    else
        printf("There is not\n");
    
    GRA_DestruirGrafo(grafo);
    printf("Hello, World!\n");
    
    return 0;
}
