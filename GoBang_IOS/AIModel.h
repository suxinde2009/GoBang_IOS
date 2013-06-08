//
//  AIModel.h
//  GoBang_IOS
//
//  Created by su xinde on 13-3-10.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#ifndef GoBang_IOS_AIModel_h
#define GoBang_IOS_AIModel_h


#include <stdio.h>
#include <stdlib.h>

#define BOOL int
#define FALSE 0
#define TRUE 1

#define Size 10

//单四
extern BOOL isTo4D(int x,
                   int y,
                   int shapeChess[Size][Size][Size],
                   int shapeSpace[Size][Size][Size]);
//活三活二
extern BOOL isTo3L2L(int x,
                     int y,
                     int shapeChess[Size][Size][Size],
                     int shapeSpace[Size][Size][Size]);
//双活二
extern BOOL isToD2L(int x,
                    int y,
                    int shapeChess[Size][Size][Size],
                    int shapeSpace[Size][Size][Size]);
//双冲三
extern BOOL isToD3D(int x,
                    int y,
                    int shapeChess[Size][Size][Size],
                    int shapeSpace[Size][Size][Size]);
//实现冲三
extern BOOL isTo3D(int x,
                   int y,
                   int shapeChess[Size][Size][Size],
                   int shapeSpace[Size][Size][Size]);
//是否能实现活三7
extern BOOL isTo3L(int x,
                   int y,
                   int shapeChess[Size][Size][Size],
                   int shapeSpace[Size][Size][Size]);
//四和冲三6
extern BOOL isTo4DAnd3D(int x,
                        int y,
                        int shapeChess[Size][Size][Size],
                        int shapeSpace[Size][Size][Size]);
//双四3
extern BOOL isToD4D(int x,
                    int y,
                    int shapeChess[Size][Size][Size],
                    int shapeSpace[Size][Size][Size]);
//是否连五1
extern BOOL isTo5L(int x,
                   int y,
                   int shapeChess[Size][Size][Size],
                   int shapeSpace[Size][Size][Size]);
//是否成活四2
extern BOOL isTo4L(int x,
                   int y,
                   int shapeChess[Size][Size][Size],
                   int shapeSpace[Size][Size][Size]);

//实现四和活三或者是双活三4
extern BOOL isTo4D3LANDD3L(int x,
                           int y,
                           int shapeChess[Size][Size][Size],
                           int shapeSpace[Size][Size][Size]);


#endif
