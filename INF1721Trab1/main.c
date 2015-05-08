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
int main(int argc, const char * argv[]) {
    // insert code here...
    Board b,b2;

    BoardPieces pieces[boardLimit]={One,Two,Three,Four,Five,Six,Seven,Eight,Void};
    BoardPieces pieces2[boardLimit]={One,Two,Three,Three,Five,Seven,Eight,Void};
    BoardPieces finalConfiguration[boardLimit]={Void,Three,Five,Eight,Two,Seven,One,Four,Six};
    BoardPieces** adjcConfig;
    Board* boards;
    GRA_tppGrafo grafo;
  
    int cont;
    int i;
    int tempInt;
    b=createBoard(b, pieces);
    if(b)
        printf("b created\n");
    else
        printf("failed\n");
    b2=createBoard(b2, pieces2);
    if(b2)
        printf("b2 created\n");
    else
        printf("failed\n");
    
    printBoard(b);

	//part that Really matters
    adjcConfig=adjacentConfigs(b,&cont);
    printf("cont %d\n",cont);
    printBoardConfigurations(adjcConfig, cont);
    boards=generateBoardsFromConfigurationVectors(adjcConfig,cont);
    
    GRA_CriarGrafo(&grafo, (void*)boardDestroy);
    GRA_InserirNo(grafo, b, &tempInt);
    boardSetId(b, tempInt); //sets initial configuration
    for(i=0;i<cont;i++)
    {
        GRA_InserirNo(grafo,boards[i] ,&tempInt);
        boardSetId(boards[i], tempInt);
        GRA_InserirAresta(grafo, boardGetId(boards[i]), boardGetId(b), 1);
    }
	
    
    GRA_ImprimirGrafo(grafo);
    GRA_DestruirGrafo(grafo);
    printf("Hello, World!\n");
    
    return 0;
}
