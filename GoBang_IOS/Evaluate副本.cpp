//
//  Evaluate.cpp
//  GoBang_IOS
//
//  Created by su xinde on 13-3-8.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#include "Evaluate.h"

//每个位置所占用的分值，越往外越小
int nodeValue[ MAX_LINE ][ MAX_LINE ] =
{
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ,
    { 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 } ,
    { 0 , 1 , 2 , 2 , 2 , 2 , 2,  1 , 0 } ,
    { 0 , 1 , 2 , 3 , 3 , 3 , 2 , 1 , 0 } ,
    { 0 , 1 , 2 , 3 , 4 , 3 , 2 , 1 , 0 } ,
    { 0 , 1 , 2 , 3 , 3 , 3 , 2 , 1 , 0 } ,
    { 0 , 1 , 2 , 2 , 2 , 2 , 2 , 1 , 0 } ,
    { 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 } ,
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
};
//对每一种状态所对应的分数
int stateScore[ 8 ] = { 0 , 100000 , 10000 , 5000 , 3000 , 500 , 100 , 50 } ;

Evaluate::Evaluate()
{
    memset( numOfState , 0 , sizeof( numOfState ) ) ;//初始化为0
}

//对单独的一行进行分析,line表示一行的棋子情况
void Evaluate::analyseLine( char player , string line )
{
    char enemy = ( player == MYSELF ) ? RIVAL : MYSELF ;//对手
    int current_player = player - '1' ;//将字符转换成int，以利于计算当前选手各种状态的个数
    int line_size = line.size() ;//一行总共的个数
    int nodeStates[ MAX_LINE ] ;//记录各个点是否被分析过
    int leftEdge , rightEdge ;//标志一下搜索的过程中连续的左右边界
    memset( nodeStates , UNANALYSED , sizeof( nodeStates ) ) ;//初始化为未被分析过
    for ( int i = 0 ; i < line_size ; ++ i )
    {
        if ( line[ i ] == player && nodeStates[ i ] == UNANALYSED )
        {
            leftEdge = rightEdge = i ;
            //向左搜索
            while( leftEdge >= 0 )
            {
                if ( line[ leftEdge ] != player )
                {
                    break ;
                }
                leftEdge -- ;
            }
            //向右搜索
            while( rightEdge < line_size )
            {
                if ( line[ rightEdge ] != player )
                {
                    break ;
                }
                rightEdge ++ ;
            }
            ++ leftEdge , --rightEdge ;
            for( int index = leftEdge ; index <= rightEdge ; ++ index )
            {
                nodeStates[ index ] = ANALYSED ;
            }
            
            if ( leftEdge == rightEdge )
            {
                nodeStates[ leftEdge ] = UNANALYSED ;
            }
            
            //如果是五连 xxxxx
            if ( rightEdge - leftEdge > 3 )
            {
                numOfState[ current_player ][ FIVE ] ++ ;
            }
            //如果是4连
            if ( rightEdge - leftEdge == 3 )
            {
                //如果是活四 _xxxx_
                if ( leftEdge > 0 && rightEdge < line_size - 1 && line[ leftEdge - 1 ] == EMPTY && line[ rightEdge + 1 ] == EMPTY)
                {
                    numOfState[ current_player ][ FOUR ] ++ ;
                }
                //如果是冲四,则有且仅有一侧空，另一侧或者为边界或者为敌方棋子 _xxxxo或者oxxxx_
                else if ( ( ( leftEdge == 0 || (leftEdge > 0 && line[ leftEdge - 1 ] == enemy ) ) && (rightEdge < line_size - 1 && line[ rightEdge + 1 ] == EMPTY) ) || ( (rightEdge == line_size - 1 || ( rightEdge < line_size - 1 && line[ rightEdge + 1 ] == enemy )) && ( leftEdge > 0 && line[ leftEdge - 1 ] == EMPTY) ))
                {
                    numOfState[ current_player ][ SLEEP_FOUR ] ++ ;
                }
            }
            //如果是3连
            else if ( rightEdge - leftEdge == 2 )
            {
                //如果是冲四 xxx_x或x_xxx
                if ( (leftEdge > 1 && line[ leftEdge - 2 ] == player && nodeStates[ leftEdge - 2 ] == UNANALYSED && line[ leftEdge - 1 ] == EMPTY) || (rightEdge < line_size - 2 && line[ rightEdge + 1 ] == EMPTY && line[ rightEdge + 2 ] == player && nodeStates[ rightEdge + 2 ] == UNANALYSED ) )
                {
                    numOfState[ current_player ][ SLEEP_FOUR ] ++ ;
                }
                //如果是活三 _xxx__或__xxx_
                else if ( leftEdge > 0 && rightEdge < line_size - 1 && line[ leftEdge - 1 ] == EMPTY && line[ rightEdge + 1 ] == EMPTY && ( (leftEdge > 1 && line[ leftEdge - 2 ] == EMPTY) || ( rightEdge < line_size - 2 && line[ rightEdge + 2 ] == EMPTY ) ) )
                {
                    numOfState[ current_player ][ THREE ] ++ ;
                }
                //如果是眠三
                else
                {
                    //第一种形式 oxxx__或__xxxo
                    if( ((leftEdge == 0 || (leftEdge > 0 && line[ leftEdge - 1 ] == enemy)) && ( rightEdge < line_size - 2 && line[ rightEdge + 1 ] == EMPTY && line[ rightEdge + 2 ] == EMPTY )) || ( (leftEdge > 1 && line[ leftEdge - 1 ] == EMPTY && line[ leftEdge - 2 ] == EMPTY) && (rightEdge == line_size - 1 || (rightEdge < line_size - 1 && line[ rightEdge + 1 ] == enemy ) ) ) )
                    {
                        numOfState[ current_player ][ SLEEP_THREE ] ++ ;
                    }
                    //第二种形式o_xxx_o
                    else if ( leftEdge > 0 && line[ leftEdge - 1 ] == EMPTY && rightEdge < line_size - 1 && line[ rightEdge + 1 ] == EMPTY && ( leftEdge == 1 || (leftEdge > 1 && line[ leftEdge - 2 ] == enemy)) && ( rightEdge == line_size - 2 || ( rightEdge < line_size - 2 && line[ rightEdge + 2 ] == enemy )))
                    {
                        numOfState[ current_player ][ SLEEP_THREE ] ++ ;
                    }
                }
            }
            //如果是二连
            else if ( rightEdge - leftEdge == 1 )
            {
                //冲四 oxx_xx或xx_xxo
                if ( ((leftEdge == 0 || (leftEdge > 0 && line[ leftEdge - 1 ] == enemy )) && ( rightEdge < line_size - 3 && line[ rightEdge + 1 ] == EMPTY && line[ rightEdge + 2 ] == player && nodeStates[ rightEdge + 2 ] == UNANALYSED && line[ rightEdge + 3 ] == player && nodeStates[ rightEdge + 3 ] == UNANALYSED ))
                    || ( (rightEdge == line_size - 1 || (rightEdge < line_size - 1 && line[ rightEdge + 1 ] == enemy )) && leftEdge > 2 && line[ leftEdge - 1 ] == EMPTY && line[ leftEdge - 2 ] == player && nodeStates[ leftEdge - 2 ] == UNANALYSED && line[ leftEdge - 3 ] == player && nodeStates[ leftEdge - 3 ] == UNANALYSED ) )
                {
                    numOfState[ current_player ][ SLEEP_FOUR ] ++ ;
                }
                //如果是跳活三 _xx_x_或_x_xx_
                else if ( leftEdge > 0 && line[ leftEdge - 1 ] == EMPTY && rightEdge < line_size - 1 && line[ rightEdge + 1 ] == EMPTY && ( (rightEdge < line_size - 3 && line[ rightEdge + 2 ] == player && nodeStates[ rightEdge + 2 ] == UNANALYSED && line[ rightEdge + 3 ] == EMPTY ) || ( leftEdge > 2 && line[ leftEdge - 2 ] == player && nodeStates[ leftEdge - 2 ] == UNANALYSED && line[ leftEdge - 3 ] == EMPTY ) ))
                {
                    numOfState[ current_player ][ THREE ] ++ ;
                }
                //如果是眠三 oxx_x_或_x_xxo
                else if ( ( (leftEdge == 0 || (leftEdge > 0 && line[ leftEdge - 1 ] == enemy )) && rightEdge < line_size - 3 && line[ rightEdge + 1 ] == EMPTY && line[ rightEdge + 2 ] == player && nodeStates[ rightEdge + 2 ] == UNANALYSED && line[ rightEdge + 3 ] == EMPTY)
                         || ( ( rightEdge == line_size - 1 || ( rightEdge < line_size - 1 && line[ rightEdge + 1 ] == enemy )) && leftEdge > 2 && line[ leftEdge - 1 ] == EMPTY && line[ leftEdge - 2 ] == player && nodeStates[ leftEdge - 2 ] == UNANALYSED && line[ leftEdge - 3 ] == EMPTY ) )
                {
                    numOfState[ current_player ][ SLEEP_THREE ] ++ ;
                }
                //如果是眠三 oxx__x或x__xxo
                else if ( ( (leftEdge == 0 || (leftEdge > 0 && line[ leftEdge - 1 ] == enemy )) && rightEdge < line_size - 3 && line[ rightEdge + 1 ] == EMPTY && line[ rightEdge + 2 ] == EMPTY && line[ rightEdge + 3 ] == player && nodeStates[ rightEdge + 3 ] == UNANALYSED )
                         || ( ( rightEdge == line_size - 1 || ( rightEdge < line_size - 1 && line[ rightEdge + 1 ] == enemy )) && leftEdge > 2 && line[ leftEdge - 1 ] == EMPTY && line[ leftEdge - 2 ] == EMPTY && line[ leftEdge - 3 ] == player && nodeStates[ leftEdge - 3 ] == UNANALYSED ) )
                {
                    numOfState[ current_player ][ SLEEP_THREE ] ++ ;
                }
                //如果是眠三 ox__xx或xx__xo
                else if ( (leftEdge > 2 && line[ leftEdge - 1 ] == EMPTY && line[ leftEdge - 2 ] == EMPTY && line[ leftEdge - 3 ] == player  && ( leftEdge == 3 || ( leftEdge > 3 && line[ leftEdge - 4 ] == enemy )) )
                         || (rightEdge < line_size - 3 && line[ rightEdge + 1 ] == EMPTY && line[ rightEdge + 2 ] == EMPTY && line[ rightEdge + 3 ] == player && ( rightEdge == line_size - 4 || ( rightEdge < line_size - 4 && line[ rightEdge + 4 ] == enemy ))))
                {
                    numOfState[ current_player ][ SLEEP_THREE ] ++ ;
                }
                //如果是活二 __xx__
                else if ( leftEdge > 1 && rightEdge < line_size - 2 && line[ leftEdge - 1 ] == EMPTY && line[ leftEdge - 2 ] == EMPTY && line[ rightEdge + 1 ] == EMPTY && line[ rightEdge + 2 ] == EMPTY )
                {
                    numOfState[ current_player ][ TWO ] ++ ;
                }
                //如果是眠二 oxx___或___xxo
                else if ( ( (leftEdge == 0 || (leftEdge > 0 && line[ leftEdge - 1 ] == enemy ) ) && rightEdge < line_size - 3 && line[ rightEdge + 1 ] == EMPTY && line[ rightEdge + 2 ] == EMPTY && line[ rightEdge + 3 ] == EMPTY ) ||
                         ( ( rightEdge == line_size - 1 || ( rightEdge < line_size - 1 && line[ rightEdge + 1 ] == enemy )) && leftEdge > 2 && line[ leftEdge - 1 ] == EMPTY && line[ leftEdge - 2 ] == EMPTY && line[ leftEdge - 3 ] == EMPTY))
                {
                    numOfState[ current_player ][ SLEEP_TWO ] ++ ;
                }
            }
        }
    }
}

//寻找各个状态的个数
void Evaluate::findStateNum( char board[ MAX_LINE ][ MAX_LINE ] )
{
    //在水平和垂直方向搜索
    for( int i = 0 ; i < MAX_LINE ; ++ i )
    {
        string src_row = "" , src_col = "" ;
        for( int j = 0 ; j < MAX_LINE ; ++ j )
        {
            src_row += board[ i ][ j ] ;
            src_col += board[ j ][ i ] ;
        }
        analyseLine( MYSELF , src_row ) ;
        analyseLine( MYSELF , src_col ) ;
        analyseLine( RIVAL , src_row ) ;
        analyseLine( RIVAL , src_col ) ;
    }
    
    //    for( int sum  = 4 ; sum <= 24 ; ++ sum )
    //    {
    //        string src = "" ;
    //        for( int i = ( sum <= 14 ) ? sum : 14 , j = sum - i ; i >= 0 && j <= 14 ; -- i , ++ j )
    //        {
    //            src += board[ i ][ j ] ;
    //        }
    //        analyseLine( RIVAL , src ) ;
    //        analyseLine( MYSELF , src ) ;
    //    }
    
    //左下-右上搜索(两部分）
    for (int i = 0; i < MAX_LINE; i++) {
        string src = "" ;
        for (int a = 0; a <= i; a++) {
            src  += board[a][i-a];
        }
        analyseLine(MYSELF, src);
        analyseLine(RIVAL, src);
    }
    
    
    for (int i = 1; i < MAX_LINE; i++) {
        string src = "" ;
        for (int a = i; a <=  MAX_LINE -1 ; a++) {
            src += board[a][MAX_LINE-1+i-a];
        }
        analyseLine(MYSELF, src);
        analyseLine(RIVAL,src);
    }
    //左上-右下搜索（两部分）
    for (int i = 0; i < MAX_LINE; i++) {
        string src = "" ;
        for (int a = 0; a<=MAX_LINE-1-i; a++) {
            src += board[0][a+i];
        }
        analyseLine(MYSELF, src);
        analyseLine(RIVAL, src);
        
    }
    for (int i = 1; i <= MAX_LINE-1; i++) {
        string src = "";
        for (int a = i; a<=MAX_LINE-1; a++) {
            src += board[a][a-i];
        }
        analyseLine(MYSELF, src);
        analyseLine(RIVAL, src);
    }
    
}

//返回评估值,whether_win表示当前选手能否赢。WIN代表赢，LOSE代表输
//注:现在计算的是我方刚走完后的棋局面
int Evaluate::getValue( char player , char board[ MAX_LINE ][ MAX_LINE ] , int *whether_win )
{
    int my_score = 0 , rival_score = 0 ;//分别记录机器和对手的分数
    
    memset( numOfState , 0 , sizeof( numOfState ) ) ;//每次计算时都需要清空
    findStateNum( board ) ;
    for ( int i = 1 ; i < 8 ; ++ i )
    {
        my_score += numOfState[ 0 ][ i ] * stateScore[ i ] ;
        rival_score += numOfState[ 1 ][ i ] * stateScore[ i ] ;
    }
    
    int current_player =  player - '1' ;//当前选手
    int other_player = 1 - current_player ;//对方选手
    //如果敌方五连，则敌方赢
    if ( numOfState[ other_player ][ FIVE ] )
    {
        *whether_win = LOSE ;
        return -200000 ;
    }
    //如果我方五连，则我方赢
    if ( numOfState[ current_player ][ FIVE ] )
    {
        *whether_win = WIN ;
        return 200000 ;
    }
    //如果敌方活四或冲四，则敌方赢
    if ( numOfState[ other_player ][ FOUR ] || numOfState[ other_player ][ SLEEP_FOUR ] )
    {
        *whether_win = LOSE ;
        return -180000 ;
    }
    //我方活四，则我方赢
    if ( numOfState[ current_player ][ FOUR ] )
    {
        *whether_win = WIN ;
        return 180000 ;
    }
    //如果我方的眠四和活三之和大于等于2，则我方赢
    if ( ( numOfState[ current_player ][ SLEEP_FOUR ] + numOfState[ current_player ][ THREE ] > 1 ) && ( numOfState[ other_player ][ THREE ] == 0 ) && ( numOfState[ other_player ][ FOUR ] == 0 ) && ( numOfState[ other_player ][ SLEEP_FOUR ] == 0 ) )
    {
        *whether_win = WIN ;
        return 100000 ;
    }
    
    //最后加上每个位置的分值
    for ( int i = 0 ; i < MAX_LINE ; ++ i )
    {
        for ( int j = 0 ; j < MAX_LINE ; ++ j )
        {
            if ( board[ i ][ j ] != EMPTY )
            {
                ( board[ i ][ j ] == MYSELF ) ? my_score : rival_score += nodeValue[ i ][ j ] ;
            }
        }
    }
    return ( player == MYSELF ) ? (my_score - rival_score) : ( rival_score - my_score ) ;
}