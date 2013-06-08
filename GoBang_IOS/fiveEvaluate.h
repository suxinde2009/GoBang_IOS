//
//  fiveEvaluate.h
//  GoBang_IOS
//
//  Created by apple on 13-4-16.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#import <Foundation/Foundation.h>

//棋盘的行列数
#define MAX_LINE 9 //15

//每个棋位的状态，空为0，我为1，对手为2
#define EMPTY 0
#define MYSELF -1
#define RIVAL 2

//初始化的最大值
#define INIT_MAX 2147483647

#define FIVE 1
#define FOUR 2
#define SLEEP_FOUR 3
#define THREE 4
#define SLEEP_THREE 5
#define TWO 6
#define SLEEP_TWO 7
#define UNANALYSED 0
#define ANALYSED 10

//赢、输、和局
#define  WIN 1
#define  LOSE -1
#define  TIE 0

@interface fiveEvaluate : NSObject
{
   int  numOfState[ 2 ][ 8 ] ;
    int nodeValue[ MAX_LINE ][ MAX_LINE ];
    int stateScore[ 8 ];
}
int getValue(  int player , int board[ MAX_LINE ][ MAX_LINE ] , int *whether_win ) ;//得到估价值，whether_win表示当前选手能否赢
void analyseLine( int player , NSString * line ) ;//对某一行(水平，垂直或倾斜)进行分析
void findStateNum( int board[ MAX_LINE ][ MAX_LINE ]) ;//找出各个状态的个数

@end
