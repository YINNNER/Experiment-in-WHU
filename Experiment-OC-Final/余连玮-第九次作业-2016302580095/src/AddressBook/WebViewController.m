//
//  WebViewController.m
//  AddressBook
//
//  Created by yiner on 2018/6/24.
//  Copyright © 2018年 yiner. All rights reserved.
//

#import "WebViewController.h"

@interface WebViewController ()
@property (weak, nonatomic) IBOutlet WKWebView *webView;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *backBtn;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *forwardBtn;

@end

@implementation WebViewController


- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	[self refreshButtonState];
	[self.webView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"http://www.baidu.com"]]];
	self.webView.navigationDelegate = self;
}

- (void)webView:(WKWebView *)webView didFinishNavigation:(WKNavigation *)navigation
{
	[self refreshButtonState];
}

- (void)refreshButtonState {
	if ([self.webView canGoBack]) {
		self.backBtn.enabled = YES;
	} else {
		self.backBtn.enabled = NO;
	}
	
	if ([self.webView canGoForward]) {
		self.forwardBtn.enabled = YES;
	} else {
		self.forwardBtn.enabled = NO;
	}
}

- (IBAction)onButtonsClicked:(UIBarButtonItem *)sender {
	switch (sender.tag) {
		case 1:
		{
			[self.webView goBack];
			[self refreshButtonState];
		}
			break;
		case 2:
		{
			[self.webView goForward];
			[self refreshButtonState];
		}
			break;
		case 3:
			[self.webView reload];
			break;
		default:
			break;
	}
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	return YES;
}


@end
