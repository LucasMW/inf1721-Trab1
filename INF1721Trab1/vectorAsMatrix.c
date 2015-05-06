//
//  vectorAsMatrix.c
//  INF1721Trab1
//
//  Created by Lucas Menezes on 19/04/15.
//  Copyright (c) 2015 MWAPPTECH. All rights reserved.
//

#include "vectorAsMatrix.h"



int MIndex(int i, int j,int n)
{
    return i*n+j;
}
void MPrint(Matrix A,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        printf("| ");
        for(j=0;j<n;j++)
        {
            printf("%c ",A[MIndex(i,j,n)]);
        }
        printf("|\n");
    }
    printf("\n");
}
 void MCopy(Matrix  org, Matrix dest,int n)
{
    int i,n2;
    n2=n*n;
    for(i=0;i<n2;i++)
        dest[i]=org[i];
}