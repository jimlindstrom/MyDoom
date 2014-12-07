#import "ui_background_view.h"
#import "games.h"

#define NS_SHIFT_KEY_MASK        (1 << 17)
#define NS_CONTROL_KEY_MASK      (1 << 18)
#define NS_ALTERNATE_KEY_MASK    (1 << 19)
#define NS_COMMAND_KEY_MASK      (1 << 20)

int xlate_cocoa_modifier_flag_to_doom_key(int cocoa_flag)
{
    int rc = 0;

    switch(cocoa_flag)
    {
      case NS_SHIFT_KEY_MASK:
	rc = KEY_RSHIFT;
	break;
	
      case NS_CONTROL_KEY_MASK:
	rc = KEY_RCTRL;
	break;
		
      case NS_ALTERNATE_KEY_MASK:
	rc = KEY_RALT;
	break;

      case NS_COMMAND_KEY_MASK:
	rc = KEY_RALT;
	break;
    }

    return rc;
}

int xlate_cocoa_key_to_doom_key(int cocoa_key)
{
    int rc;

    switch(rc = cocoa_key)
    {
      case 123:		rc = KEY_LEFTARROW;	break;
      case 124:		rc = KEY_RIGHTARROW;	break;
      case 125:		rc = KEY_DOWNARROW;	break;
      case 126:		rc = KEY_UPARROW;	break;

      case  53:		rc = KEY_ESCAPE;	break;
      case  36:		rc = KEY_ENTER;		break;
      case  48:		rc = KEY_TAB;		break;

      case 122:		rc = KEY_F1;		break;
      case 120:		rc = KEY_F2;		break;
      case  99:		rc = KEY_F3;		break;
      case 118:		rc = KEY_F4;		break;
      case  96:		rc = KEY_F5;		break;
      case  97:		rc = KEY_F6;		break;
      case  98:		rc = KEY_F7;		break;
      case 100:		rc = KEY_F8;		break;
      case 101:		rc = KEY_F9;		break;
      case 109:		rc = KEY_F10;		break;
      case 103:		rc = KEY_F11;		break;
      case 111:		rc = KEY_F12;		break;
	
      case 51:
      case 117:		rc = KEY_BACKSPACE;	break;


      case 81:
      case 24:		rc = KEY_EQUALS;	break;

      case 78:
      case 27:		rc = KEY_MINUS;		break;

      case  0:		rc = 'a';		break;
      case  1:		rc = 'b';		break;
      case  2:		rc = 'c';		break;
      case  3:		rc = 'd';		break;

      case  4:		rc = 'h';		break;
      case  5:		rc = 'g';		break;
      case  6:		rc = 'z';		break;
      case  7:		rc = 'x';		break;

      case  8:		rc = 'c';		break;
      case  9:		rc = 'v';		break;
      //case 10:		rc = '';		break;
      case 11:		rc = 'b';		break;

      case 12:		rc = 'q';		break;
      case 13:		rc = 'w';		break;
      case 14:		rc = 'e';		break;
      case 15:		rc = 'r';		break;

      case 16:		rc = 'y';		break;
      case 17:		rc = 't';		break;
      case 18:		rc = '1';		break;
      case 19:		rc = '2';		break;

      case 20:		rc = '3';		break;
      case 21:		rc = '4';		break;
      case 22:		rc = '6';		break;
      case 23:		rc = '5';		break;

      //case 24:		rc = '';		break; // EQUALS/PLUS
      case 25:		rc = '9';		break;
      case 26:		rc = '7';		break;
      //case 27:		rc = '';		break; // MINUS

      case 28:		rc = '8';		break;
      case 29:		rc = '0';		break;
      case 30:		rc = ']';		break;
      case 31:		rc = 'o';		break;

      case 32:		rc = 'u';		break;
      case 33:		rc = '[';		break;
      case 34:		rc = 'i';		break;
      case 35:		rc = 'p';		break;

      //case 36:		rc = '';		break; //ENTER
      case 37:		rc = 'l';		break;
      case 38:		rc = 'j';		break;
      case 39:		rc = '\'';		break;

      case 40:		rc = 'k';		break;
      case 41:		rc = ';';		break;
      case 42:		rc = '\\';		break;
      case 43:		rc = ',';		break;

      case 44:		rc = '/';		break;
      case 45:		rc = 'n';		break;
      case 46:		rc = 'm';		break;
      case 47:		rc = '.';		break;

      //case 48:		rc = '';		break; // TAB
      case 49:		rc = ' ';		break;
      case 50:		rc = '`';		break;
      //case 51:		rc = '';		break; // BACKSPACE

      default:
	/*if (rc >= XK_space && rc <= XK_asciitilde)
	    rc = rc - XK_space + ' ';
	if (rc >= 'A' && rc <= 'Z')
	    rc = rc - 'A' + 'a';*/
	break;
    }

    return rc;
}






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
  int doom_key_code = xlate_cocoa_key_to_doom_key([theEvent keyCode]);
  game_post_event_key_up(doom_key_code);
};

- (void)keyDown:(NSEvent *)theEvent
{
  int doom_key_code = xlate_cocoa_key_to_doom_key([theEvent keyCode]);
  game_post_event_key_down(doom_key_code);
};

- (void)flagsChanged:(NSEvent *)theEvent
{
  int masks[4] = {NSAlternateKeyMask, NSShiftKeyMask, NSControlKeyMask, NSCommandKeyMask};
  int curMask, i, doom_key_code;

  int flags = [theEvent modifierFlags];

  for (i=0; i<4; i++) {
    curMask = masks[i];
    if ( !(lastFlags & curMask) &&  (flags & curMask) )
    {
      doom_key_code = xlate_cocoa_modifier_flag_to_doom_key(curMask);
      game_post_event_key_down(doom_key_code);
    }
    if (  (lastFlags & curMask) && !(flags & curMask) )
    {
      doom_key_code = xlate_cocoa_modifier_flag_to_doom_key(curMask);
      game_post_event_key_up(doom_key_code);
    }
  }

  lastFlags = flags;
};
@end
