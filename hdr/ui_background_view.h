#ifndef __UI_BACKGROUND_VIEW_H
#define __UI_BACKGROUND_VIEW_H

#import <Cocoa/Cocoa.h>

@interface BackgroundView : NSView {
  int lastFlags;
}

- (BOOL)acceptsFirstResponder;
- (void)keyDown:(NSEvent *)theEvent;
- (void)keyUp:(NSEvent *)theEvent;
- (void)flagsChanged:(NSEvent *)theEvent;
@end

#endif
