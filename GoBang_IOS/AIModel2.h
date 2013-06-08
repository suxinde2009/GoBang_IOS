//
//  AIModel.h
//  GoBang_IOS
//
//  Created by su xinde on 13-1-22.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ChessMan.h"


#define BOARDSIZE 10
#define BOARDWIDTH 10*30
#define BOARDHEIGHT 10*30
#define SQUARESIZE 30
#define INAVAILABLE 4
#define EMPTY 2
#define WHITE 0
#define BLACK 1
#define SQUAREFULL 15
#define MEMORYFAIL 16
#define CHESSWIN 8
#define CHESSFAIL 7
#define OUTSIDE 5


@interface AIModel : NSObject
{
    int m_board[BOARDSIZE+2*OUTSIDE][BOARDSIZE+2*OUTSIDE];
	int m_temp[BOARDSIZE+2*OUTSIDE][BOARDSIZE+2*OUTSIDE];
	int m_level[BOARDSIZE][BOARDSIZE];

    NSMutableArray *m_list;
}


- (void)initBoard;


@end
