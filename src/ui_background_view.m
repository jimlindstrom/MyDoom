#import "ui_background_view.h"

@implementation BackgroundView
- (id)initWithFrame:(NSRect)frame {
  if (! (self = [super initWithFrame:frame] ) ) {
    return self;
  } // end if

  return self;
}  // end initWithFrame

- (BOOL)acceptsFirstResponder
{
  return YES;
};

- (void)keyUp:(NSEvent *)theEvent
{
#if 0
  event_t event;
  event.type = ev_keyup;
  event.data1 = I_XlateCocoaKeyToDoomKey([theEvent keyCode]);
  D_PostEvent(&event);
#endif
};

- (void)keyDown:(NSEvent *)theEvent
{
#if 0
  event_t event;
  event.type = ev_keydown;
  event.data1 = I_XlateCocoaKeyToDoomKey([theEvent keyCode]);
  D_PostEvent(&event);
#endif
};

- (void)flagsChanged:(NSEvent *)theEvent
{
#if 0
  int masks[4] = {NSAlternateKeyMask, NSShiftKeyMask, NSControlKeyMask, NSCommandKeyMask};
  int curMask, i;
  event_t event;

  int flags = [theEvent modifierFlags];

  for (i=0; i<4; i++) {
    curMask = masks[i];
    if ( !(lastFlags & curMask) &&  (flags & curMask) )
    {
      event.type = ev_keydown;
      event.data1 = I_XlateCocoaModifierFlagToDoomKey(curMask);
      D_PostEvent(&event);
    }
    if (  (lastFlags & curMask) && !(flags & curMask) )
    {
      event.type = ev_keyup;
      event.data1 = I_XlateCocoaModifierFlagToDoomKey(curMask);
      D_PostEvent(&event);
    }
  }

  lastFlags = flags;
#endif
};
@end
