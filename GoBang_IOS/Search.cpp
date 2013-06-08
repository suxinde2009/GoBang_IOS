//
//  Search.cpp
//  GoBang_IOS
//
//  Created by su xinde on 13-3-8.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#include "Search.h"
#include "search.h"
#include <iostream>

//构造函数。depth：搜索深度；numOfGoodNodes：每一步搜寻多少个节点，即搜索宽度；board：棋盘
Search::Search( int depth , int numOfGoodNodes , char chessBoard[ BORAD_SIZE ][ BORAD_SIZE ] )
{
    evaluator = Evaluate() ;
    this->depth = depth ;
    this->numOfGoodNodes = numOfGoodNodes ;
    //初始化bestMove
    bestMove.x = bestMove.y = - 1 ;
    bestMove.value = 0 ;
    bestMove.win = TIE ;
    
    //给棋盘赋值
    for( int i = 0 ; i < MAX_LINE ; i ++ )
    {
        for ( int j = 0 ; j < MAX_LINE ; j ++ )
        {
            this->chessBoard[ i ][ j ] = chessBoard[ i ][ j ] ;
        }
    }
}

//贪心法先找出numGoodNodes个比较好的点
void Search::search_several_good_nodes( char player , char board[ MAX_LINE ][ MAX_LINE ] , Node* goodNodeArray  , int numGoodNodes )
{
    int countGood = 0 ; //记录goodNodeArray数组里边已经存了多少个
    
    Node tmpNode ; //临时变量
    for( int i = 0 ; i < MAX_LINE ; i ++ )
    {
        for ( int j = 0 ; j < MAX_LINE ; j ++ )
        {
            if ( board[ i ][ j ] == EMPTY )
            {
                int whether_win  = TIE ;
                board[ i ][ j ] = player ;
                int value = evaluator.getValue( player , board , &whether_win ) ;
                board[ i ][ j ] = EMPTY ;
                if (i == 6 & j == 8) {
                    // printf("[%d][%d]=%d",6,8,value);
                }
               if (i == 7 & j == 7) {
                   // printf("[%d][%d]=%d",7,7,value);
                }
                tmpNode.x = i ;
                tmpNode.y = j ;
                tmpNode.value = value ;
                tmpNode.win = whether_win ;
                
                //按估值由大至小的顺序找出最好的numGoodNodes个节点
                if ( ++countGood <= numGoodNodes )
                {
                    goodNodeArray[ countGood - 1 ] = tmpNode ;
                    if ( countGood == numGoodNodes )
                    {
                        sort( goodNodeArray , goodNodeArray + numGoodNodes ) ;
                    }
                }
                else
                {
                    if ( value > goodNodeArray[ numGoodNodes - 1 ].value )
                    {
                        for ( int k = 0 ; k < numGoodNodes ; ++ k )
                        {
                            if ( value > goodNodeArray[ k ].value )
                            {
                                for (int i = numGoodNodes -1; i > k; i --) {
                                    goodNodeArray[i] = goodNodeArray[i-1];
                                }
                                goodNodeArray[ k ] = tmpNode ;
                                break ;
                            }
                        } //end-for
                    } //end-if
                }//end-else
            }//end-if
        }//end-for-j
    }//end-for-i
}//end-func

//alpha-beta减枝搜索算法
int Search::alphaBetaSearch( int search_depth , int alpha , int beta , char player )
{

    int score ;//估值结果
    Node *goodNodes = new Node[ numOfGoodNodes ] ;
    Node *badNodes = new Node[ 1 ] ;
    badNodes[ 0 ].x = badNodes[ 0 ].y = badNodes[ 0 ].win = TIE ;
    search_several_good_nodes( player , chessBoard , goodNodes , numOfGoodNodes  ) ;
    search_several_good_nodes( ( player == MYSELF ) ? RIVAL : MYSELF , chessBoard , badNodes , 1 ) ;
    //如果赢了，不可能再在此基础上下下去
    if ( goodNodes[ 0 ].win == WIN )
    {
        if ( search_depth == 1)
        {
            bestMove.x = goodNodes[ 0 ].x ;
            bestMove.y = goodNodes[ 0 ].y ;
        }
        
        return ( search_depth % 2 ) ? goodNodes[ 0 ].value :  (- goodNodes[ 0 ].value ) ;
    }
    //自己不赢，敌方赢了，这下一步得走在敌方的一步上
    if ( badNodes[ 0 ].win == WIN )
    {
        if ( search_depth == 1 )
        {
            bestMove.x = badNodes[ 0 ].x ;
            bestMove.y = badNodes[ 0 ].y ;
        }
        
        return ( search_depth % 2 ) ? badNodes[ 0 ].value :  (- badNodes[ 0 ].value ) ;
    }
    
    //搜索到了最后一层，则返回
    if ( search_depth == this->depth )
    {
        
        return ( search_depth % 2 ) ? goodNodes[ 0 ].value :  (- goodNodes[ 0 ].value ) ;
    }
    
    for ( int i = 0 ; i < numOfGoodNodes ; ++ i )
    {
        chessBoard[ goodNodes[ i ].x ][ goodNodes[ i ].y ] = player ;
        if (search_depth == 1) {
            score = alphaBetaSearch( search_depth + 1 , alpha , beta , (player == MYSELF) ? MYSELF : RIVAL ) ;
        }
        else{
            score = -alphaBetaSearch( search_depth + 1 , -beta , -alpha , (player == MYSELF) ? RIVAL : MYSELF ) ;
        }
//        if (search_depth == 1) {
//            int a = score;
//        }
        chessBoard[ goodNodes[ i ].x ][ goodNodes[ i ].y ] = EMPTY ;
        
        if ( score >= beta )
        {
            return beta ;
        }
        
        if ( score > alpha )
        {
            alpha = score ;
            if ( search_depth == 1 )
            {
                bestMove.x = goodNodes[ i ].x ;
                bestMove.y = goodNodes[ i ].y ;
            }
        }
    }
    
    return alpha ;
}






