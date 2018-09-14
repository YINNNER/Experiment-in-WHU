//
//  DialViewController.m/Users/yiner/XcodeProjects/AddressBook/AddressBook/DialViewController.h
//  AddressBook
//
//  Created by yiner on 2018/6/24.
//  Copyright © 2018年 yiner. All rights reserved.
//

#import "DialViewController.h"
#import "CallViewController.h"

@implementation DialViewController
@synthesize phoneNumber = _phoneNumber;

- (void)viewWillAppear:(BOOL)animated
{
	self.phoneNumber.text = @"";
}




- (IBAction)pressBtn:(UIButton *)sender {
	NSString * text = sender.currentTitle;
	self.phoneNumber.text = [self.phoneNumber.text stringByAppendingString: text];
}

- (IBAction)pressDelete:(id)sender {
	NSString *num = self.phoneNumber.text;
	if (num.length != 0){
		self.phoneNumber.text = [num substringToIndex:num.length-1];
	}
	
}

#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
	if ([segue.identifier isEqualToString:@"dialing"]) {
		[segue.destinationViewController setText:self.phoneNumber.text];
	}
	
}

@end
