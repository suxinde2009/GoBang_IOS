//
//  Search.h
//  GoBang_IOS
//
//  Created by su xinde on 13-3-8.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#ifndef __GoBang_IOS__Search__
#define __GoBang_IOS__Search__

#include <iostream>
#include <algorithm>
#include "evaluate.h"

#define BORAD_SIZE 15 //15

using namespace std ;
//在一个棋位上的信息
struct Node
{
    int x ;//行坐标
    int y ;//列坐标
    int value ;//在此节点下完后的估计值
    int win ;//走了这一步棋后是否能赢，1代表赢，0即不输也不赢，-1输了
    bool operator < ( const Node aNode ) const
    {
        return this->value > aNode.value ;
    }
} ;

class Search
{
public:
    Search( int depth , int numOfGoodNodes , char chessBoard[ BORAD_SIZE ][ BORAD_SIZE ] ) ;
    void search_several_good_nodes( char player , char board[ MAX_LINE ][ MAX_LINE ] , Node* goodNodeArray  , int numGoodNodes  ) ;//贪心法先找出几个比较好的点
    int alphaBetaSearch( int depth , int alpha , int beta , char player ) ; //alpha-beta减枝搜索算法
    bool win( int x , int y , char player ) ;//判断能否赢
    Node bestMove ; //记录下一步要走的地方
private:
    int depth ; //搜索的深度
    int numOfGoodNodes ; //几个比较好的点的个数，以减小收缩的复杂度
    Evaluate evaluator ;
    char chessBoard[ MAX_LINE ][ MAX_LINE ] ;//棋盘状态
};

#endif /* defined(__GoBang_IOS__Search__) */
