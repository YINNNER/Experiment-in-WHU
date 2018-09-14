//
//  DetailViewController.m
//  AddressBook
//
//  Created by yiner on 2018/6/19.
//  Copyright © 2018年 yiner. All rights reserved.
//

#import "DetailViewController.h"
#import "Address+Create.h"

@interface DetailViewController ()

@property (weak, nonatomic) IBOutlet UILabel *name;
@property (weak, nonatomic) IBOutlet UILabel *phone;
@property (weak, nonatomic) IBOutlet UILabel *email;
@property (weak, nonatomic) IBOutlet UILabel *weChat;
@property (weak, nonatomic) IBOutlet UILabel *anAddress;

@end

@implementation DetailViewController
@synthesize name = _name;
@synthesize phone = _phone;
@synthesize email = _email;
@synthesize anAddress = _anAddress;
@synthesize weChat = _weChat;
@synthesize address = _address;
@synthesize managedObjectContext = _managedObjectContext;


- (void)viewDidLoad {
	[super viewDidLoad];
}

// viewDidLoad是将视图加载到内存中
// 如果从别的页面返回不会调用viewDidLoad
// 但是会调用viewWillAppear，因此用这个
- (void)viewWillAppear:(BOOL)animated{
	[super viewWillAppear:animated];
	// Do any additional setup after loading the view, typically from a nib.
	self.name.text = self.address.name;
	self.phone.text = [NSString stringWithFormat:@"%d",self.address.phone];
	self.email.text = self.address.email;
	self.anAddress.text = self.address.address;
	self.weChat.text = self.address.weChat;
	//set image
}

- (IBAction)deleteCurrentRecord:(UIButton *)sender
{
	NSString *message = nil;
	BOOL isSuccess = YES;
	isSuccess = [Address deleteDataWithName:self.name.text inManagedObjectContext:self.managedObjectContext];
	if (isSuccess == YES) {
		message = @"删除联系人成功！";
	} else {
		message = @"删除联系人失败！";
	}

	// show alert and back
	[self showAlertView:message];
}

// 分享按钮
- (IBAction)share:(id)sender {
	//分享的标题
	NSString *nameToShare = self.name.text;
	NSString *phoneToShare = self.phone.text;
	NSString *emailToShare = self.email.text;
	
	//把要分享的东西加进去
	NSArray *activityItems = @[nameToShare,phoneToShare,emailToShare];
	UIActivityViewController *activityVC = [[UIActivityViewController alloc]initWithActivityItems:activityItems applicationActivities:nil];
	//不出现在活动项目
	activityVC.excludedActivityTypes = @[UIActivityTypePrint, UIActivityTypeCopyToPasteboard,UIActivityTypeAssignToContact,UIActivityTypeSaveToCameraRoll];
	[self presentViewController:activityVC animated:YES completion:nil];
	// 分享之后的回调
	activityVC.completionWithItemsHandler = ^(UIActivityType  _Nullable activityType, BOOL completed, NSArray * _Nullable returnedItems, NSError * _Nullable activityError) {
		if (completed) {
			NSLog(@"completed");
			//分享 成功
		} else  {
			NSLog(@"cancled");
			//分享 取消
		}
	};
}


// show alert message and segue
- (void)showAlertView:(NSString *)message
{
	// 1.创建UIAlertController
	UIAlertController *alertController = [UIAlertController alertControllerWithTitle:message message:nil preferredStyle:UIAlertControllerStyleAlert];
	
	// 2.创建并添加按钮
	UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
		// 返回上一个页面
		[self.navigationController popViewControllerAnimated:YES];
	}];
	
	[alertController addAction:okAction];
	
	// 3.呈现UIAlertContorller
	[self presentViewController:alertController animated:YES completion:nil];
}

#pragma mark - Segue

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
	if ([segue.identifier isEqualToString:@"edit contact"]) {
		// set address
		if ([segue.destinationViewController respondsToSelector:@selector(setAddress:)]) {
			[segue.destinationViewController performSelector:@selector(setAddress:) withObject:self.address];
		}
		// set source type
		if ([segue.destinationViewController respondsToSelector:@selector(setSourceType:)]) {
			[segue.destinationViewController performSelector:@selector(setSourceType:) withObject:@"edit"];
		}
		// set context
		if ([segue.destinationViewController respondsToSelector:@selector(setManagedObjectContext:)]) {
			[segue.destinationViewController performSelector:@selector(setManagedObjectContext:) withObject:self.managedObjectContext];
		}
		
	}
}

@end
