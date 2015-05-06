//
//  vectorAsMatrix.h
//  INF1721Trab1
//
//  Created by Lucas Menezes on 19/04/15.
//  Copyright (c) 2015 MWAPPTECH. All rights reserved.
//

#ifndef __INF1721Trab1__vectorAsMatrix__
#define __INF1721Trab1__vectorAsMatrix__

#include <stdio.h>
typedef char* Matrix; //the type of matrix
int MIndex(int i, int j,int n);
void MPrint(Matrix A,int n);
void MCopy(Matrix  org, Matrix dest,int n);
#endif /* defined(__INF1721Trab1__vectorAsMatrix__) */


