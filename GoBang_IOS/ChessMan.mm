//
//  ChessMan.m
//  GoBang_IOS
//
//  Created by su xinde on 13-1-22.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#import "ChessMan.h"

@implementation ChessMan

@synthesize type= _type,x=_x,y=_y;

- (id)initWithType:(char)type x:(int)x y:(int)y
{
    
    if(self = [super init])
    {
        self.frame = CGRectMake(y,x,40,40);
        self.backgroundColor = [UIColor clearColor];
        _type = type;
        _x = x;
        _y = y;
    }
    return self;
}
- (void)drawRect:(CGRect)rect{
    CGContextRef context = UIGraphicsGetCurrentContext();
    if (_type==WHITE_CHESS) {
        [[UIColor grayColor] setStroke];
        [[UIColor whiteColor] setFill];
        CGContextStrokeEllipseInRect(context, CGRectMake(0, 0, 40, 40));
        CGContextFillEllipseInRect(context, CGRectMake(0, 0, 40, 40));
    }else if(_type==BLACK_CHESS){
        [[UIColor blackColor] set];
        CGContextFillEllipseInRect(context, CGRectMake(0, 0, 40, 40));
    }
}
@end
