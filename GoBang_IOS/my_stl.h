//
//  my_stl.h
//  GoBang_IOS
//
//  Created by su xinde on 13-3-11.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#ifndef GoBang_IOS_my_stl_h
#define GoBang_IOS_my_stl_h

#include <String.h>

#define MAX_LINE 10 //15
#define BORAD_SIZE 10 //15

struct RenjuNode
{
    double x ;
    double y ;
    String color ;
};

struct RenjuNodeStack
{
    int top ;
    RenjuNode nodes[ 81 ];//225 ] ;
};


//判断能否赢
static bool win( char chessBoard[ BORAD_SIZE ][ BORAD_SIZE ] , int x , int y , char player )
{
    int count = 1 ; //记录相连同色个数
    //先搜索水平方向
    bool search_left = true , search_right = false ; //一开始先向左搜索
    int tmp_left_y = y , tmp_right_y = y ; //分别替换向左向右搜索
    while( search_left || search_right )
    {
        if( search_left )
        {
            if( --tmp_left_y < 0 || chessBoard[ x ][ tmp_left_y ] != player )
            {
                search_left = false ;
                search_right = true ;
            }
            else
            {
                if( ++ count == 5 )
                    return true ;
            }
        }
        else
        {
            if( ++ tmp_right_y >= MAX_LINE || chessBoard[ x ][ tmp_right_y ] != player )
                search_right = false ;
            else
            {
                if( ++ count == 5 )
                {
                    return true ;
                }
            }
        }
    }
    
    
    //然后搜索垂直方向
    count = 1 ;
    bool search_up = true , search_down = false ;//首先向上搜索
    int tmp_up_x = x , tmp_down_x = x ; //分别代替上下时的搜索
    while( search_up || search_down )
    {
        if( search_up )
        {
            if( --tmp_up_x < 0 || chessBoard[ tmp_up_x ][ y ] != player )
            {
                search_up = false ;
                search_down = true ;
            }
            else
            {
                if( ++count == 5 )
                {
                    return true ;
                }
            }
        }
        else
        {
            if( ++tmp_down_x >= MAX_LINE || chessBoard[ tmp_down_x ][ y ] != player )
            {
                search_down = false ;
            }
            else
            {
                if( ++ count == 5 )
                {
                    return true ;
                }
            }
        }
    }
    
    
    //左上-右下搜索
    count = 1 ;
    bool search_left_up = true , search_right_down = false ; //先搜索左上
    int tmp_x1 = x , tmp_y1 = y ;//左上搜索时
    int tmp_x2 = x , tmp_y2 = y ;//右下搜索时
    if( abs( x - y ) <= 10 ) //只有线上的格的个数不小于5时才进行搜索
    {
        while( search_left_up || search_right_down )
        {
            if( search_left_up )
            {
                if( --tmp_x1 < 0 || --tmp_y1 < 0 || chessBoard[ tmp_x1 ][ tmp_y1 ] != player )
                {
                    search_left_up = false ;
                    search_right_down = true ;
                }
                else
                {
                    if( ++count == 5 )
                    {
                        return true ;
                    }
                }
            }
            else
            {
                if( ++tmp_x2 >= MAX_LINE || ++tmp_y2 >= MAX_LINE || chessBoard[ tmp_x2 ][ tmp_y2 ] != player )
                {
                    search_right_down = false ;
                }
                else
                {
                    if( ++ count == 5 )
                    {
                        return true ;
                    }
                }
            }
        }
    }
    
    
    //左下-右上搜索
    count = 1 ;
    bool search_left_down = true , search_right_up = false ; //先搜索左下
    tmp_x1 = tmp_x2 = x ;
    tmp_y1 = tmp_y2 = y ;
    if( x + y >= 4 && x + y <= 24 ) //线上的格的个数不小于5才搜索
    {
        while( search_left_down || search_right_up )
        {
            if( search_left_down )
            {
                if( ++tmp_x1 >= MAX_LINE || --tmp_y1 < 0 || chessBoard[ tmp_x1 ][ tmp_y1 ] != player )
                {
                    search_left_down = false ;
                    search_right_up = true ;
                }
                else
                {
                    if( ++count == 5 )
                    {
                        return true ;
                    }
                }
            }
            else
            {
                if( --tmp_x2 < 0 || ++ tmp_y2 >= MAX_LINE || chessBoard[ tmp_x2 ][ tmp_y2 ] != player )
                {
                    search_right_up = false ;
                }
                else
                {
                    if( ++ count == 5 )
                    {
                        return true ;
                    }
                }
            }
        }
    }
    
    return false ; //当上面四种情况都不满足时，返回false
}

#endif

/*
void PeopVSComp::mousePressEvent( QMouseEvent  * e )
{
    if( game_start )
    {
        int x = e->x() ;
        int y = e->y() ;
        if( ( x - TO_LEFT ) % DISTANCE < DISTANCE / 2 )
            pos_x = TO_LEFT + ( x - TO_LEFT ) / DISTANCE * DISTANCE ;
        else
            pos_x = TO_LEFT + ( ( x - TO_LEFT ) / DISTANCE + 1 ) * DISTANCE ;
        if( ( y - TO_UP ) % DISTANCE < DISTANCE / 2 )
            pos_y = TO_UP + ( y - TO_UP ) / DISTANCE * DISTANCE ;
        else
            pos_y = TO_UP + ( ( y - TO_UP ) / DISTANCE + 1 ) * DISTANCE ;
        
        RenjuNode aNode ;
        aNode.x = pos_x - 13.5;
        aNode.y = pos_y - 14 ;
        if( !(*p_move_first) )
            aNode.color = "WHITE" ;
        else
            aNode.color = "BLACK" ;
        
        
        int chessboard_x = ( pos_x - TO_LEFT ) / DISTANCE ;
        int chessboard_y = ( pos_y - TO_UP ) / DISTANCE ;
        qDebug() << "not saved" << chessboard_x << chessboard_y ;
        if( pos_x >= 73 && pos_x <= 493 && pos_y >= 87 && pos_y <= 507 &&
           drawed[ chessboard_y ][ chessboard_x ] == 0 )
        {
            qDebug() << chessboard_x << chessboard_y ;
            nodeStack.nodes[ ++nodeStack.top ] = aNode ;
            if( *audio )
                moveSound->play() ;
            repaint() ;
            drawed[ chessboard_y ][ chessboard_x ] = 1 ;
            chessBoard[ chessboard_y ][ chessboard_x ] =  RIVAL ;
            if( win( chessBoard ,chessboard_y , chessboard_x , RIVAL ) )
            {
                winSound->play() ;
                QMessageBox::StandardButton reply ;
                reply = QMessageBox::question( this , "" , QString::fromUtf8( "你太厉害了，膜拜一下！" ) ) ;
                if ( reply == QMessageBox::Ok )
                {
                    this->close() ;
                }
            }
            computer_move();
        }
    }
}
*/

// search_depth
// search_width
// chessboard
/*
void computerMove()
{
    Search search( search_depth , search_width , chessBoard ) ;
    search.alphaBetaSearch( 1 , -INIT_MAX , INIT_MAX , MYSELF ) ;
    pos_x = TO_LEFT + search.bestMove.y * DISTANCE ;
    pos_y = TO_UP + search.bestMove.x * DISTANCE ;
    
    RenjuNode aNode ;
    aNode.x = pos_x - 13.5 ;
    aNode.y = pos_y - 14 ;
    if( !(*p_move_first) )
        aNode.color = "BLACK" ;
    else
        aNode.color = "WHITE" ;
    nodeStack.nodes[ ++nodeStack.top ] = aNode ;
    
    chessBoard[ search.bestMove.x ][ search.bestMove.y ] = MYSELF ;
    drawed[ search.bestMove.x ][ search.bestMove.y ] = 1 ;
    if( *audio )
        moveSound->play() ;
    repaint() ; //重绘
    
    if( win( chessBoard , search.bestMove.x , search.bestMove.y , MYSELF ) ) // computer 赢了
    {
        printf("残念的输给AI只有5的computer了！");
    }
}
*/
