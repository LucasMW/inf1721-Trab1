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
#include "time.h"
//#define DEBUG_MAIN

Board boardFinal;
GRA_tppGrafo grafoGlobal;
Board* allPossibilities;
bit  nodeMarked[boardPossibilities];

void printGraphElements(GRA_tppGrafo grafo)
{
    int * ids;
    int tam;
    int i;
    Board b;
    GRA_ObterVertices(grafo, &ids, &tam);
    for(i=0;i<tam;i++)
    {
        printf("node %d\n",ids[i]);
        GRA_ObterValorNo(grafo, ids[i], (void**)&b);
        printBoard(b);
        
    }
}

bit boardIsInAlreadyOnGraph(GRA_tppGrafo grafo, Board b)
{
    int * ids;
    int tam;
    int i;
    Board currentBoard;
    
//    GRA_ObterVertices(grafo, &ids, &tam);
//    for(i=0;i<tam;i++)
//    {
//        //printf("v: %d\n ",i);
//        GRA_ObterValorNo(grafo, ids[i], (void**)&currentBoard);
//        if(boardCompare(b, currentBoard)==True)
//            return True;
//        
//    }
    if(nodeMarked[boardPermutIndex(b)]==True)
        return True;
    return False;
}

void verifyAdjacents(Board orBoard, Board* adjBoards, int cont)
{
    int i;
    int j;
    int tempInt;
    BoardPieces** newAdj;
    Board* newBoards;
    static int k=0;
    static bit flag = False;
    if(flag)
        return;
    if(boardCompare(orBoard,boardFinal)==True)
    {
        printf("Found\n");
        GRA_InserirAresta(grafoGlobal, boardGetId(orBoard), boardGetId(boardFinal), 1);
        flag=True;
        return;
    }
    k++;
    if(k%1000==0)
        printf("k %d\n",k);
    for(i=0;i<cont;i++)
    {
        //printf("k: %d ,adjBoard[%d]\n",k,i);
        //printBoard(adjBoards[i]);
        
        if(boardCompare(adjBoards[i],boardFinal)==True)
        {
            printf("Found\n");
            flag=True;
            GRA_InserirAresta(grafoGlobal, boardGetId(orBoard), boardGetId(boardFinal), 1);
            return;
        }
        if(flag)
            return;
        if(!boardIsInAlreadyOnGraph(grafoGlobal, adjBoards[i]))
        {
            #ifdef DEBUG_MAIN
            printf("This board Not on Graph\n");
            #endif
            GRA_InserirNo(grafoGlobal,adjBoards[i] ,&tempInt);
            boardSetId(adjBoards[i], tempInt);
            nodeMarked[boardPermutIndex(adjBoards[i])]=True;
            GRA_InserirAresta(grafoGlobal, boardGetId(adjBoards[i]), boardGetId(orBoard), 1);
            newAdj=adjacentConfigs(adjBoards[i], &tempInt);
            newBoards=generateBoardsFromConfigurationVectors(newAdj, tempInt);
            if(flag)
                return;
            #ifdef DEBUG_MAIN
            printf("it`s adjacents\n");
            for(j=0;j<tempInt;j++)
            {
                printBoard(newBoards[j]);
            }
            #endif
            verifyAdjacents(adjBoards[i], newBoards, tempInt);
            
        }
    }
}
int main(int argc, const char * argv[])
{
    // insert code here...
    Board b,b2,bF;

    BoardPieces pieces[boardLimit]={One,Two,Three,Four,Five,Six,Seven,Eight,Void};
    //BoardPieces pieces[boardLimit]={Eight,Six,One,Seven,Four,Three,Five,Two,Void};
    BoardPieces pieces2[boardLimit]={One,Two,Three,Three,Five,Seven,Eight,Void};
    //BoardPieces finalConfiguration[boardLimit]={Void,Three,Five,Eight,Two,Seven,One,Four,Six}; // slow, slow
    //BoardPieces finalConfiguration[boardLimit]={Void,Two,Three,One,Four,Five,Seven,Eight,Six}; //slow, slow
    //BoardPieces finalConfiguration[boardLimit]={One,Two,Three,Four,Five,Six,Seven,Void,Eight}; //really fast, slow
    //BoardPieces finalConfiguration[boardLimit]={One,Two,Void,Four,Five,Three,Seven,Eight,Six}; //fast, slow
    BoardPieces finalConfiguration[boardLimit]={Six,One,Three,Eight,Four,Two,Void,Seven,Five}; //slow ,slow
    //BoardPieces finalConfiguration[boardLimit]={Seven,Eight,Void,One,Two,Three,Four,Five,Six}; //slow , slow
    //BoardPieces finalConfiguration[boardLimit]={Seven,Two,Four,Six,One,Eight,Three,Void,Five}; //fast
    //BoardPieces finalConfiguration[boardLimit]={Seven,Two,Four,Six,One,Eight,Three,Five,Void}; //fast
    //BoardPieces finalConfiguration[boardLimit]={Seven,Two,Four,Six,One,Void,Three,Five,Eight}; //fast
    //BoardPieces finalConfiguration[boardLimit]={Seven,Two,Void,Six,One,Four,Three,Five,Eight}; //slow
    //BoardPieces finalConfiguration[boardLimit]={Seven,Two,Four,Six,Void,One,Three,Five,Eight}; //fast
     //BoardPieces finalConfiguration[boardLimit]={Seven,Two,Four,Void,Six,One,Three,Five,Eight}; //slow
    //BoardPieces finalConfiguration[boardLimit]={Seven,Two,Four,Six,Five,One,Three,Void,Eight}; //fast
    //BoardPieces finalConfiguration[boardLimit]={Seven,Two,Four,Six,Five,One,Void,Three,Eight}; //slow
    BoardPieces** adjcConfig;
    
    Board* boards;
    GRA_tppGrafo grafo;
    bit flag1;
    bit flag2;
    int start_time;
    int end_time;
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
    for(i=0;i<boardPossibilities;i++)
        nodeMarked[i]=False;
    
    adjcConfig=adjacentConfigs(b,&cont);
    printf("cont %d\n",cont);
    printBoardConfigurations(adjcConfig, cont);
    boards=generateBoardsFromConfigurationVectors(adjcConfig,cont);
    
    GRA_CriarGrafo(&grafo, (void*)boardDestroy);
    GRA_InserirNo(grafo, b, &tempInt);
    nodeMarked[boardPermutIndex(b)]=True;
    boardSetId(b, tempInt); //sets initial configuration
    
    GRA_InserirNo(grafo,bF ,&tempInt);
    nodeMarked[boardPermutIndex(bF)]=True;
    boardSetId(bF, tempInt); //sets final configuration
    flag1=False;
    boardFinal=bF;
    grafoGlobal=grafo;
    
   
    start_time=(int)time(NULL);
    verifyAdjacents(b, boards, cont);
    end_time=(int)time(NULL);
    printf("it took %d seconds\n",end_time-start_time);
    
    start_time=(int)time(NULL);
    GRA_ImprimirGrafo(grafo);
    end_time=(int)time(NULL);
    printf("it took %d seconds\n",end_time-start_time);
    
    start_time=(int)time(NULL);
    printGraphElements(grafo);
    end_time=(int)time(NULL);
    printf("it took %d seconds\n",end_time-start_time);
    
    start_time=(int)time(NULL);
    GRA_DFS(grafo, &ids, &cont, boardGetId(b));
    end_time=(int)time(NULL);
    printf("it took %d seconds\n",end_time-start_time);
    start_time=(int)time(NULL);
    if(GRA_ExisteCaminho(grafo, boardGetId(b), boardGetId(bF))==GRA_CondRetCaminhoExiste)
        printf("There is\n");
    else
        printf("There is not\n");
    end_time=(int)time(NULL);
    printf("it took %d seconds\n",end_time-start_time);
//    GRA_ObterValorNo(grafo, 3, (void**)&b2);
//    adjcConfig=adjacentConfigs(b2, &tempInt);
//    printf("cont %d\n",cont);
//    printBoardConfigurations(adjcConfig, cont);
    
    
    GRA_DestruirGrafo(grafo);
    printf("Hello, World!\n");
    //permute(b, 0, 8);
    //allPossibilities=generateAllPossibilities(b);
    
    
    return 0;
}
