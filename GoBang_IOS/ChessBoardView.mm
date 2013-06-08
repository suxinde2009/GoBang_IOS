//
//  ChessBoardView.m
//  GoBang_IOS
//
//  Created by su xinde on 13-3-10.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#import "ChessBoardView.h"
#include "Search.h"
#include "ChessMan.h"
//#include "Evaluate.h
@implementation ChessBoardView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
    }
    return self;
}
- (void)dealloc
{
    [super dealloc];
}

- (void)clearChessFlag{//清理棋盘
    memset(chessMap, '0', sizeof(char)*ROW_COUNT*COLUMN_COUNT);
    memset(whiteHistoX, -1, sizeof(int)*maxChessCount);
    memset(whiteHistoY, -1, sizeof(int)*maxChessCount);
    memset(blackHistoX, -1, sizeof(int)*maxChessCount);
    memset(blackHistoY, -1, sizeof(int)*maxChessCount);
    chessCount = -1;
}

- (void)setChessFlag:(char)flag withRow:(int)row withColumn:(int)column{//设置棋子
    
    chessMap[row][column] = flag;
    ChessMan *chessMan = [[ChessMan alloc] initWithType:flag x:30+20+40*row y:30+20+40*column];
    [self addSubview:chessMan];
    [chessMan release];
    if (flag == WHITE_CHESS) {
        chessCount ++;
        if (chessType == 0) {
            whiteHistoX[chessCount] = row;
            whiteHistoY[chessCount] = column;
        }
    }
    else{
        if (chessType == 0) {
            blackHistoX[chessCount] = row;
            blackHistoY[chessCount] = column;
        }
    }
    // [self setNeedsDisplay];
}

- (int)judgeSuccess:(char)flag withRow:(int)row withColumn:(int)column{//判断胜负
    int count = 0;
    // |
    for (int i = row; i >= 0; i--) {
        if (chessMap[i][column]==flag) {
            count++;
        }else{
            break;
        }
        
    }
    
    for (int i = row+1; i < ROW_COUNT; i++) {
        if (chessMap[i][column]==flag) {
            count++;
        }else{
            break;
        }
        
    }
    if (count >= 5) {
        
        return flag;
    }
    
    // -
    count = 0;
    for (int i = column; i >= 0; i--) {
        if (chessMap[row][i]==flag) {
            count++;
        }else{
            break;
        }
        
    }
    
    for (int i = column+1; i < COLUMN_COUNT; i++) {
        if (chessMap[row][i]==flag) {
            count++;
        }else{
            break;
        }
        
    }
    if (count >= 5) {
       
        return flag;
    }
    
    count = 0;
    for (int i = row,j=column; i >= 0&&j < COLUMN_COUNT; i--,j++) {
        if (chessMap[i][j]==flag) {
            count++;
        }else{
            break;
        }
        
    }
    
    for (int i = row+1,j=column-1; i < ROW_COUNT&& j >=0; i++,j--) {
        if (chessMap[i][j]==flag) {
            count++;
        }else{
            break;
        }
        
    }
    if (count >= 5) {
        
        return flag;
    }
    
    count = 0;
    for (int i = row , j = column; i >= 0 && j >= 0; i -- ,j --) {
        if (chessMap[i][j] == flag) {
            count ++;
        }
        else{
            break;
        }
    }
    for (int i = row+1 , j = column+1; i < ROW_COUNT && j < COLUMN_COUNT; i ++ ,j ++) {
        if (chessMap[i][j] == flag) {
            count ++;
        }
        else{
            break;
        }
    }
    if (count >= 5) {

        return flag;
    }
    
    return 0;
}


- (void)drawBackground {
	// Draw a rectangle fill with color from skins
	CGContextRef context = UIGraphicsGetCurrentContext();
	[[UIColor colorWithRed:241/255.0 green:235/255.0 blue:222/255.0 alpha:1.0] set];
    
    CGContextFillRect(context, CGRectMake(0, 0, 700, 700));
    
    
	[[UIColor blackColor] set];
    int startx = 30.0;
	int starty = 30.0;
	// Draw horizontal line
    for (int i = 0; i < ROW_COUNT + 2; i++)
        CGContextFillRect(context, CGRectMake(startx, starty+i*40.0, 640.0, 1.0));
    
	// Draw vertical line
    
    for (int i = 0; i < COLUMN_COUNT + 2; i++)
        CGContextFillRect(context, CGRectMake(startx+i*40.0, starty, 1.0, 640.0));
}

//- (void)drawChess {
//    CGContextRef context = UIGraphicsGetCurrentContext();
//    for (int i = 0; i < ROW_COUNT; i++) {
//        for (int j = 0; j < COLUMN_COUNT; j++) {
//            if (chessMap[i][j]==WHITE_CHESS) {
//                [[UIColor grayColor] setStroke];
//                [[UIColor whiteColor] setFill];
//                CGContextStrokeEllipseInRect(context, CGRectMake(30+20+40*j, 30+20+40*i, 40, 40));
//                CGContextFillEllipseInRect(context, CGRectMake(30+20+40*j, 30+20+40*i, 40, 40));
//            }else if(chessMap[i][j]==BLACK_CHESS){
//                [[UIColor blackColor] set];
//                CGContextFillEllipseInRect(context, CGRectMake(30+20+40*j, 30+20+40*i, 40, 40));
//            }
//        }
//    }
////drawTag = 1;
//}

- (void)drawRect:(CGRect)rect{
    // @synchronized(self){
    [self drawBackground];
    //[self drawChess];
    //}
    
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
    
    if (status != CHESS_START) {
        return;
    }
    if (chessType == 0) {
        if (chessTurn != WHITE_CHESS ) {
            UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil message:@"机器人正在思考，请稍后" delegate:nil cancelButtonTitle:@"确定"
                                                      otherButtonTitles:nil,nil];
            [alertView show];
            [alertView release];
            return;
        }
    }
    UITouch *touch = [touches anyObject];
    CGPoint touchPoint = [touch locationInView:self];
    
    if (touchPoint.x > 20+30 && touchPoint.y > 20+30 && touchPoint.x < 700-30-20 && touchPoint.y < 700-30-20) {
        int column = (touchPoint.x - 20-30)/40;
        int row = (touchPoint.y - 20-30)/40;
        
        if (chessMap[row][column] == '0') {
            [self setChessFlag:chessTurn withRow:row withColumn:column];
            if([self judgeSuccess:chessTurn withRow:row withColumn:column] == chessTurn){
                NSString *msg;
                if (chessTurn == WHITE_CHESS) {
                    msg = @"白子胜利!";
                }
                else{
                    msg = @"黑子胜利!";
                }
                
                UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示" message:msg delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];
                [alert show];
                [alert release];
                status = CHESS_STOP;
            }
            chessTurn = (chessTurn == WHITE_CHESS)? BLACK_CHESS:WHITE_CHESS  ;
            if (chessType == 0) {
                [self robotplaychess];
            }
        }
    }
}
- (void)robotplaychess{
    if (status != CHESS_START) {
        return;
    }
    Node node;
    if (difficultTag == 0) {
        Search fiveSearch = Search(2,3,chessMap);
        int result = fiveSearch.alphaBetaSearch(1,-INIT_MAX, INIT_MAX, '1');
        node = fiveSearch.bestMove;
    }
    else{
        Search fiveSearch = Search(2,6,chessMap);
        int result = fiveSearch.alphaBetaSearch(1,-INIT_MAX, INIT_MAX, '1');
        node = fiveSearch.bestMove;
    }

    [self setChessFlag:chessTurn withRow:node.x withColumn:node.y];
    if([self judgeSuccess:chessTurn withRow:node.x withColumn:node.y] == chessTurn){
        NSString *msg = @"黑子胜利!";
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示" message:msg delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];
        [alert show];
        [alert release];
        status = CHESS_STOP;
    }
    chessTurn =  WHITE_CHESS;
    NSLog(@"转换");
}

- (void)restartChess{
    
    [self clearChessFlag];
    NSArray *subviews = self.subviews;
    for (int i = 0; i < subviews.count; i ++) {
        UIView *view = [subviews objectAtIndex:i];
        [view removeFromSuperview];
    }
    
    status = CHESS_START;
    [self selectChessType];
    [self setNeedsDisplay];
}
- (void)regretChess{
    if (chessType == 1) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil message:@"人人对战,无法悔棋" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil,nil];
        [alertView show];
        [alertView release];
    }
    else{
        if (chessCount >= 0) {
            int whiteX = whiteHistoX[chessCount];
            whiteHistoX[chessCount] = -1;
            
            int whiteY = whiteHistoY[chessCount];
            whiteHistoY[chessCount] = -1;
            
            int blackX = blackHistoX[chessCount];
            blackHistoX[chessCount] = -1;
            
            int blackY = blackHistoY[chessCount];
            blackHistoY[chessCount] = -1;
            
            chessMap[whiteX][whiteY] = EMPTY;
            chessMap[blackX][blackY] = EMPTY;
            
            ChessMan *subView;
            for (subView in self.subviews) {
                int tag = 0;
                if (subView.x == (30+20+whiteX*40)&&subView.y == (30+20+whiteY*40)) {
                    [subView removeFromSuperview];
                    tag ++;
                }
                if (subView.x == (30+20+blackX*40)&&subView.y == (30+20+blackY*40)) {
                    [subView removeFromSuperview];
                    tag ++;
                }
                if (tag == 2) {
                    return;
                }
            }
            
            [self setNeedsDisplay];
            chessCount --;
        }
        else{
            UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil message:@"已经是新的棋局了，无法悔棋" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil,nil];
            [alertView show];
            [alertView release];
        }
    }
}

- (void)selectDifficulty{
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"难度" delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil otherButtonTitles:@"普通",@"较难", nil];
    actionSheet.tag = 0;
    [actionSheet showInView:self];
    [actionSheet release];
}
- (void)selectFirstChess{
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"选择" delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil otherButtonTitles:@"我先手",@"我后手", nil];
    actionSheet.tag = 1;
    [actionSheet showInView:self];
    [actionSheet release];
    
}
- (void)selectChessType{
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"类型" delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil otherButtonTitles:@"人机对战",@"人人对战", nil];
    actionSheet.tag = 2;
    [actionSheet showInView:self];
    [actionSheet release];
}

#pragma mark - UIActionSheetDelegate
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex{
    if (actionSheet.tag == 2) {//选择下棋类型
        if (buttonIndex == 0) {
            chessType = 0;
            [self selectDifficulty];
        }
        else if(buttonIndex == 1){
            chessType = 1;
            [self selectFirstChess];
        }
        
    }
    
    else if (actionSheet.tag == 0) {//选择下棋难度
        if (buttonIndex == 0) {
            difficultTag = 0;
        }
        else if (buttonIndex == 1){
            difficultTag = 1;
        }else {
            return;
        }
        [self selectFirstChess];
        
    }
    else if (actionSheet.tag == 1){//选择先后手
        if (buttonIndex == 0) {
            firstTag = 0;
            chessTurn = WHITE_CHESS;
        }
        else if (buttonIndex == 1){
            firstTag = 1;
            chessTurn = BLACK_CHESS;
            if (chessType == 0 ) {
                [self robotplaychess];
            }
        }
        
    }
}


@end
