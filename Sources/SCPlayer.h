//
//  SCVideoPlayer.h
//  SCAudioVideoRecorder
//
//  Created by Simon CORSIN on 8/30/13.
//  Copyright (c) 2013 rFlex. All rights reserved.
//

#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
typedef NSView UIView;
#endif

#import <AVFoundation/AVFoundation.h>
#import "SCFilterGroup.h"
#import "SCImageView.h"

@class SCPlayer;

@protocol SCPlayerDelegate <NSObject>

@optional

- (void)videoPlayer:(SCPlayer*)videoPlayer didPlay:(Float64)secondsElapsed loopsCount:(NSInteger)loopsCount;
- (void)videoPlayer:(SCPlayer *)videoPlayer didStartLoadingAtItemTime:(CMTime)itemTime;
- (void)videoPlayer:(SCPlayer *)videoPlayer didEndLoadingAtItemTime:(CMTime)itemTime;
- (void)videoPlayer:(SCPlayer *)videoPlayer didChangeItem:(AVPlayerItem*)item;
- (void)player:(SCPlayer *)player didReachEndForItem:(AVPlayerItem *)item;

@end

@interface SCPlayer : AVPlayer

@property (weak, nonatomic) id<SCPlayerDelegate> delegate;
@property (assign, nonatomic) CMTime minimumBufferedTimeBeforePlaying;
@property (assign, nonatomic) BOOL shouldLoop;
@property (strong, nonatomic) SCFilterGroup *filterGroup;
@property (weak, nonatomic) UIView *outputView;
@property (readonly, nonatomic) BOOL isSendingPlayMessages;

// If a SCImageView is needed to display this SCPlayer, this property will contains it
@property (readonly, nonatomic) SCImageView *imageView;
//
@property (readonly, nonatomic) AVPlayerLayer *playerLayer;

+ (SCPlayer *)player;
+ (void)pauseCurrentPlayer;
+ (SCPlayer *)currentPlayer;

// Ask the SCPlayer to send didPlay messages during the playback
// endSendingPlayMessages must be called, otherwise the SCPlayer will never
// be deallocated
- (void)beginSendingPlayMessages;
// Ask the SCPlayer to stop sending didPlay messages during the playback
- (void)endSendingPlayMessages;

- (void)resizePlayerLayerToFitOutputView;
- (void)resizePlayerLayer:(CGSize)size;

- (void)setItemByStringPath:(NSString*)stringPath;
- (void)setItemByUrl:(NSURL*)url;
- (void)setItemByAsset:(AVAsset*)asset;
- (void)setItem:(AVPlayerItem*)item;

// These methods allow the player to add the same item "loopCount" time
// in order to have a smooth loop. The loop system provided by Apple
// has an unvoidable hiccup. Using these methods will avoid the hiccup for "loopCount" time

- (void)setSmoothLoopItemByStringPath:(NSString*)stringPath smoothLoopCount:(NSUInteger)loopCount;
- (void)setSmoothLoopItemByUrl:(NSURL*)url smoothLoopCount:(NSUInteger)loopCount;
- (void)setSmoothLoopItemByAsset:(AVAsset*)asset smoothLoopCount:(NSUInteger)loopCount;

- (CMTime)itemDuration;
- (CMTime)playableDuration;
- (BOOL)isPlaying;
- (BOOL)isLoading;

@end
