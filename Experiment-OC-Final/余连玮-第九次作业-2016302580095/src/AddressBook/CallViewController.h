//
//  CallViewController.h
//  AddressBook
//
//  Created by yiner on 2018/6/24.
//  Copyright © 2018年 yiner. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CallViewController : UIViewController

@property (weak, nonatomic) IBOutlet UILabel *phoneNumber;
@property NSString *text;
- (void)setText:(NSString *)text;

@end
