//
//  UITextField+LCWordLimit.h
//  VerifyDemo
//
//  Created by 伯明利 on 2017/6/26.
//  Copyright © 2017年 伯明利. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UITextField (LCWordLimit)

- (void)lc_wordLimit:(NSInteger)count;

@property (nonatomic, copy, readonly) NSString *lc_count;//限制字数

@end
