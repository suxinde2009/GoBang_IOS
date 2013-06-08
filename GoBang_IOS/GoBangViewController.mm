//
//  GoBangViewController.m
//  GoBang_IOS
//
//  Created by su xinde on 13-3-11.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#import "GoBangViewController.h"

@interface GoBangViewController ()
- (void)restartButtonAction:(id)sender;
- (void)regretChessAction:(id)sender;
@end

@implementation GoBangViewController

@synthesize chessboardView;

- (void)viewDidLoad
{

   
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorWithRed:0.64 green:0.52 blue:0.38 alpha:1.0];
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake((self.view.bounds.size.width-300.0f)/2.0f,
                                                               20.0f,
                                                               300.0f,
                                                               60.0f)];
    label.backgroundColor = [UIColor clearColor];
    label.font = [UIFont systemFontOfSize:20.f];
    label.numberOfLines = 0;
    label.lineBreakMode = NSLineBreakByWordWrapping;
    label.textAlignment = NSTextAlignmentCenter;
    label.text = @"SuXinDe 面试作品\n Email: suxinde2009@126.com";
    label.textColor = [UIColor whiteColor];
    
    //[self.view addSubview:label];
    [label release];
    
	ChessBoardView *chessboard = [[ChessBoardView alloc] initWithFrame:CGRectMake(34, 124, 700, 700)];
    [self.view addSubview:chessboard];
    self.chessboardView = chessboard;
    [chessboard release];
    
    UIButton *restartButton = [UIButton buttonWithType: UIButtonTypeRoundedRect];
    restartButton.frame = CGRectMake(60,CGRectGetMaxY(chessboard.frame)+60, 140, 80) ;
    [restartButton setTitle:@"新局" forState:UIControlStateNormal];
    [restartButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [restartButton addTarget:self action:@selector(restartButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:restartButton];
    
    UIButton *regretChessButton = [UIButton buttonWithType: UIButtonTypeRoundedRect];
    regretChessButton.frame = CGRectMake(768-60-140,CGRectGetMaxY(chessboard.frame)+60, 140, 80);
    [regretChessButton setTitle:@"悔棋" forState:UIControlStateNormal];
    [regretChessButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [regretChessButton addTarget:self action:@selector(regretChessAction:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:regretChessButton];
    
    //[chessboardView restartChess];
}

- (void)dealloc
{
    [chessboardView release];
    [super dealloc];
}
#pragma mark - ButtonAction
- (void)restartButtonAction:(id)sender{
    [chessboardView restartChess];
}
- (void)regretChessAction:(id)sender{
    [chessboardView regretChess];
}



@end
