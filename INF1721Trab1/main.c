//
//  main.c
//  INF1721Trab1
//
//  Created by Lucas Menezes on 18/04/15.
//  Copyright (c) 2015 MWAPPTECH. All rights reserved.
//

#include <stdio.h>
#include "puzzleConfiguration.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    Board b,b2;
    BoardPieces pieces[boardLimit]={One,Two,Three,Four,Five,Six,Seven,Eight,Void};
    BoardPieces pieces2[boardLimit]={One,Two,Three,Three,Five,Seven,Eight,Void};
    
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
    
    
    printf("Hello, World!\n");
    
    return 0;
}
