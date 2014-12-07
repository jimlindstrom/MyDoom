#import "ui_background_view.h"
#import <Cocoa/Cocoa.h>

id window;
int window_width, window_height;
CGContextRef window_context;

void ui_run_cocoa_app(void) // doesn't return until window is closed
{
  id menubar;
  id appMenuItem;
  id appMenu;
  id appName;
  id quitTitle;
  id quitMenuItem;

  [NSAutoreleasePool new];
  [NSApplication sharedApplication];
  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
  menubar = [[NSMenu new] autorelease];
  appMenuItem = [[NSMenuItem new] autorelease];
  [menubar addItem:appMenuItem];
  [NSApp setMainMenu:menubar];
  appMenu = [[NSMenu new] autorelease];
  appName = [[NSProcessInfo processInfo] processName];
  quitTitle = [@"Quit " stringByAppendingString:appName];
  quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
    action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
  [appMenu addItem:quitMenuItem];
  [appMenuItem setSubmenu:appMenu];
  window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 200, 200)
    styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO]
      autorelease];
  window_context = [[window graphicsContext] graphicsPort];
  [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
  [window setTitle:appName];
  [window makeKeyAndOrderFront:nil];
  [NSApp activateIgnoringOtherApps:YES];

  BackgroundView *view = [[BackgroundView alloc] initWithFrame:NSMakeRect(1, 1, 1, 1)];
  [view setWantsLayer:YES];
  [[window contentView] addSubview:view];
  [window makeFirstResponder:view];

  printf("Running app\n");
  [NSApp run];
}

void ui_resize_window(int new_width, int new_height)
{
  printf("resizing to %dx%d\n", new_width, new_height);
  window_width  = new_width;
  window_height = new_height;
  [window setContentSize:NSMakeSize(window_width, window_height)];
  window_context = [[window graphicsContext] graphicsPort];
}

void ui_draw_image(unsigned char *image_data, int width, int height)
{
  CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,
                                                            image_data,
                                                            width*height*4,
                                                            NULL);
  CGRect myBoundingBox = CGRectMake(0, 0, window_width, window_height);
  CGImageRef imageRef = CGImageCreate(width, height,                 /* width & height */
                                      8,                             /* bits per component */
                                      32,                            /* bits per pixel */
                                      4*width,                       /* bytes per row */
                                      CGColorSpaceCreateDeviceRGB(), /* color space */
                                      kCGBitmapByteOrderDefault,     /* bitmap info */
                                      provider,                      /* provider */
                                      NULL,                          /* decode */
                                      NO,                            /* should interpolate */
                                      kCGRenderingIntentDefault);    /* rendering intent */

  CGContextDrawImage(window_context, myBoundingBox, imageRef);
  [window flushWindow];

  CGDataProviderRelease(provider);
  CGImageRelease(imageRef);
}
