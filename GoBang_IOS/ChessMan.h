//
//  ChessMan.h
//  GoBang_IOS
//
//  Created by su xinde on 13-1-22.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define  WHITE_CHESS '2'
#define  BLACK_CHESS '1'
@interface ChessMan : UIView
{
    char  _type;
    int _x;
}

@property (nonatomic) char type;
@property (nonatomic) int x;
@property (nonatomic) int y;


- (id)initWithType:(char)_type x:(int)_x y:(int)_y;

@end

