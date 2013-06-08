//
//  GoBangViewController.h
//  GoBang_IOS
//
//  Created by su xinde on 13-3-11.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ChessBoardView.h"

@interface GoBangViewController : UIViewController
{
    ChessBoardView *chessboardView;
}

@property (nonatomic, retain) ChessBoardView *chessboardView;

@end
