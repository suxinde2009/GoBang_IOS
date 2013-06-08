//
//  ChessBoardView.h
//  GoBang_IOS
//
//  Created by su xinde on 13-3-10.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#import <UIKit/UIKit.h>

#define ROW_COUNT 15 //11
#define COLUMN_COUNT 15
#define maxChessCount 128
#define BLACK_CHESS '1'
#define WHITE_CHESS '2'
#define INIT_MAX 2147483647

typedef enum {
    CHESS_START = 1,
    CHESS_STOP,
    CHESS_PAUSE
}CHESS_STATUS;

@interface ChessBoardView : UIView<UIActionSheetDelegate>{

    char chessMap[ROW_COUNT][COLUMN_COUNT];
    char chessTurn;
    CHESS_STATUS status;
    int whiteHistoX[maxChessCount];
    int whiteHistoY[maxChessCount];
    int blackHistoX[maxChessCount];
    int blackHistoY[maxChessCount];
    int chessCount;
    int difficultTag;//0代表简单，1代表较难
    int firstTag;//0代表我先手，1代表我后手
    int chessType;//0代表人机对战，1代表人人对战
    int drawTag;//0代表正在画图，1代表已经画完图了
}
- (void)restartChess;
- (void)clearChessFlag;
- (void)setChessFlag:(char)flag withRow:(int)row withColumn:(int)column;
- (void)robotplaychess;
- (void)regretChess;
- (void)selectDifficulty;
- (void)selectChessType;
- (void)selectFirstChess;
@end
