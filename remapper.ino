#include <Keyboard.h>
#include <Mouse.h>
#include <SPI.h>
#include <hidboot.h>
#include <usbhub.h>

/* Define key mappings */
static const uint8_t keys[0xE8] PROGMEM = {
    0x00,            /* 0x00	Reserved (no event indicated) */
    0x00,            /* 0x01	Keyboard ErrorRollOver */
    0x00,            /* 0x02	Keyboard POSTFail */
    0x00,            /* 0x03	Keyboard ErrorUndefined */
    'a',             /* 0x04	Keyboard a and A */
    'b',             /* 0x05	Keyboard b and B */
    'c',             /* 0x06	Keyboard c and C */
    'd',             /* 0x07	Keyboard d and D */
    'e',             /* 0x08	Keyboard e and E */
    'f',             /* 0x09	Keyboard f and F */
    'g',             /* 0x0A	Keyboard g and G */
    'h',             /* 0x0B	Keyboard h and H */
    'i',             /* 0x0C	Keyboard i and I */
    'j',             /* 0x0D	Keyboard j and J */
    'k',             /* 0x0E	Keyboard k and K */
    'l',             /* 0x0F	Keyboard l and L */
    'm',             /* 0x10	Keyboard m and M */
    'n',             /* 0x11	Keyboard n and N */
    'o',             /* 0x12	Keyboard o and O */
    'p',             /* 0x13	Keyboard p and P */
    'q',             /* 0x14	Keyboard q and Q */
    'r',             /* 0x15	Keyboard r and R */
    's',             /* 0x16	Keyboard s and S */
    't',             /* 0x17	Keyboard t and T */
    'u',             /* 0x18	Keyboard u and U */
    'v',             /* 0x19	Keyboard v and V */
    'w',             /* 0x1A	Keyboard w and W */
    'x',             /* 0x1B	Keyboard x and X */
    'y',             /* 0x1C	Keyboard y and Y */
    'z',             /* 0x1D	Keyboard z and Z */
    '1',             /* 0x1E	Keyboard 1 and ! */
    '2',             /* 0x1F	Keyboard 2 and @ */
    '3',             /* 0x20	Keyboard 3 and # */
    '4',             /* 0x21	Keyboard 4 and $ */
    '5',             /* 0x22	Keyboard 5 and % */
    '6',             /* 0x23	Keyboard 6 and ^ */
    '7',             /* 0x24	Keyboard 7 and & */
    '8',             /* 0x25	Keyboard 8 and * */
    '9',             /* 0x26	Keyboard 9 and ( */
    '0',             /* 0x27	Keyboard 0 and ) */
    '\n',            /* 0x28	Keyboard Return (ENTER) */
    KEY_ESC,         /* 0x29	Keyboard ESCAPE */
    KEY_BACKSPACE,   /* 0x2A	Keyboard DELETE (Backspace) */
    KEY_TAB,         /* 0x2B	Keyboard Tab */
    ' ',             /* 0x2C	Keyboard Spacebar */
    '-',             /* 0x2D	Keyboard - and (underscore) */
    '=',             /* 0x2E	Keyboard = and + */
    '[',             /* 0x2F	Keyboard [ and { */
    ']',             /* 0x30	Keyboard ] and } */
    '\\',            /* 0x31	Keyboard \ and | */
    0x00,            /* 0x32	Keyboard Non - US # and~ */
    ';',             /* 0x33	Keyboard ; and : */
    '\'',            /* 0x34	Keyboard ' and " */
    '`',             /* 0x35	Keyboard Grave Accent and Tilde */
    ',',             /* 0x36	Keyboard , and < */
    '.',             /* 0x37	Keyboard . and > */
    '/',             /* 0x38	Keyboard / and ? */
    KEY_LEFT_SHIFT,  /* 0x39	Keyboard Caps Lock */
    KEY_F1,          /* 0x3A	Keyboard F1 */
    KEY_F2,          /* 0x3B	Keyboard F2 */
    KEY_F3,          /* 0x3C	Keyboard F3 */
    KEY_F4,          /* 0x3D	Keyboard F4 */
    KEY_F5,          /* 0x3E	Keyboard F5 */
    KEY_F6,          /* 0x3F	Keyboard F6 */
    KEY_F7,          /* 0x40	Keyboard F7 */
    KEY_F8,          /* 0x41	Keyboard F8 */
    KEY_F9,          /* 0x42	Keyboard F9 */
    KEY_F10,         /* 0x43	Keyboard F10 */
    KEY_F11,         /* 0x44	Keyboard F11 */
    KEY_F12,         /* 0x45	Keyboard F12 */
    0x00,            /* 0x46	Keyboard PrintScreen */
    0x00,            /* 0x47	Keyboard Scroll Lock */
    0x00,            /* 0x48	Keyboard Pause */
    0x00,            /* 0x49	Keyboard Insert */
    KEY_HOME,        /* 0x4A	Keyboard Home */
    KEY_PAGE_UP,     /* 0x4B	Keyboard PageUp */
    KEY_DELETE,      /* 0x4C	Keyboard Delete Forward */
    KEY_END,         /* 0x4D	Keyboard End */
    KEY_PAGE_DOWN,   /* 0x4E	Keyboard PageDown */
    KEY_RIGHT_ARROW, /* 0x4F	Keyboard RightArrow */
    KEY_LEFT_ARROW,  /* 0x50	Keyboard LeftArrow */
    KEY_DOWN_ARROW,  /* 0x51	Keyboard DownArrow */
    KEY_UP_ARROW,    /* 0x52	Keyboard UpArrow */
    0x00,            /* 0x53	Keypad Num Lock and Clear */
    0x00,            /* 0x54	Keypad / */
    0x00,            /* 0x55	Keypad * */
    0x00,            /* 0x56	Keypad - */
    0x00,            /* 0x57	Keypad + */
    0x00,            /* 0x58	Keypad ENTER */
    0x00,            /* 0x59	Keypad 1 and End */
    0x00,            /* 0x5A	Keypad 2 and Down Arrow */
    0x00,            /* 0x5B	Keypad 3 and PageDn */
    0x00,            /* 0x5C	Keypad 4 and Left Arrow */
    0x00,            /* 0x5D	Keypad 5 */
    0x00,            /* 0x5E	Keypad 6 and Right Arrow */
    0x00,            /* 0x5F	Keypad 7 and Home */
    0x00,            /* 0x60	Keypad 8 and Up Arrow */
    0x00,            /* 0x61	Keypad 9 and PageUp */
    0x00,            /* 0x62	Keypad 0 and Insert */
    0x00,            /* 0x63	Keypad . and Delete */
    0x00,            /* 0x64	Keyboard Non-US \ and | */
    0x00,            /* 0x65	Keyboard Application */
    0x00,            /* 0x66	Keyboard Power */
    0x00,            /* 0x67	Keypad = */
    KEY_F13,         /* 0x68	Keyboard F13 */
    KEY_F14,         /* 0x69	Keyboard F14 */
    KEY_F15,         /* 0x6A	Keyboard F15 */
    KEY_F16,         /* 0x6B	Keyboard F16 */
    KEY_F17,         /* 0x6C	Keyboard F17 */
    KEY_F18,         /* 0x6D	Keyboard F18 */
    KEY_F19,         /* 0x6E	Keyboard F19 */
    KEY_F20,         /* 0x6F	Keyboard F20 */
    KEY_F21,         /* 0x70	Keyboard F21 */
    KEY_F22,         /* 0x71	Keyboard F22 */
    KEY_F23,         /* 0x72	Keyboard F23 */
    KEY_F24,         /* 0x73	Keyboard F24 */
    0x00,            /* 0x74	Keyboard Execute */
    0x00,            /* 0x75	Keyboard Help */
    0x00,            /* 0x76	Keyboard Menu */
    0x00,            /* 0x77	Keyboard Select */
    0x00,            /* 0x78	Keyboard Stop */
    0x00,            /* 0x79	Keyboard Again */
    0x00,            /* 0x7A	Keyboard Undo */
    0x00,            /* 0x7B	Keyboard Cut */
    0x00,            /* 0x7C	Keyboard Copy */
    0x00,            /* 0x7D	Keyboard Paste */
    0x00,            /* 0x7E	Keyboard Find */
    0x00,            /* 0x7F	Keyboard Mute */
    0x00,            /* 0x80	Keyboard Volume Up */
    0x00,            /* 0x81	Keyboard Volume Down */
    0x00,            /* 0x82	Keyboard Locking Caps Lock */
    0x00,            /* 0x83	Keyboard Locking Num Lock */
    0x00,            /* 0x84	Keyboard Locking Scroll Lock */
    0x00,            /* 0x85	Keypad Comma */
    0x00,            /* 0x86	Keypad Equal Sign */
    0x00,            /* 0x87	Keyboard International1 */
    0x00,            /* 0x88	Keyboard International2 */
    0x00,            /* 0x89	Keyboard International3 */
    0x00,            /* 0x8A	Keyboard International4 */
    0x00,            /* 0x8B	Keyboard International5 */
    0x00,            /* 0x8C	Keyboard International6 */
    0x00,            /* 0x8D	Keyboard International7 */
    0x00,            /* 0x8E	Keyboard International8 */
    0x00,            /* 0x8F	Keyboard International9 */
    0x00,            /* 0x90	Keyboard LANG1 */
    0x00,            /* 0x91	Keyboard LANG2 */
    0x00,            /* 0x92	Keyboard LANG3 */
    0x00,            /* 0x93	Keyboard LANG4 */
    0x00,            /* 0x94	Keyboard LANG5 */
    0x00,            /* 0x95	Keyboard LANG6 */
    0x00,            /* 0x96	Keyboard LANG7 */
    0x00,            /* 0x97	Keyboard LANG8 */
    0x00,            /* 0x98	Keyboard LANG9 */
    0x00,            /* 0x99	Keyboard Alternate Erase */
    0x00,            /* 0x9A	Keyboard SysReq/Attention */
    0x00,            /* 0x9B	Keyboard Cancel */
    0x00,            /* 0x9C	Keyboard Clear */
    0x00,            /* 0x9D	Keyboard Prior */
    0x00,            /* 0x9E	Keyboard Return */
    0x00,            /* 0x9F	Keyboard Separator */
    0x00,            /* 0xA0	Keyboard Out */
    0x00,            /* 0xA1	Keyboard Oper */
    0x00,            /* 0xA2	Keyboard Clear/Again */
    0x00,            /* 0xA3	Keyboard CrSel/Props */
    0x00,            /* 0xA4	Keyboard ExSel */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    0x00,            /* invalid */
    KEY_LEFT_ALT,    /* 0xE0	Keyboard LeftControl (swapped with left alt)*/
    KEY_LEFT_ALT,    /* 0xE1	Keyboard LeftShift (swapped with left alt)*/
    KEY_LEFT_CTRL,   /* 0xE2	Keyboard LeftAlt (swapped with left control) */
    KEY_LEFT_GUI,    /* 0xE3	Keyboard Left GUI */
    KEY_RIGHT_SHIFT, /* 0xE4	Keyboard RightControl (swapped with right shift)
                      */
    KEY_RIGHT_ALT,   /* 0xE5	Keyboard RightShift (swapped with right alt) */
    KEY_RIGHT_CTRL,  /* 0xE6	Keyboard RightAlt (swapped with right
                        control)*/
    KEY_RIGHT_GUI,   /* 0xE7	Keyboard Right GUI */
};

class KbdRptParser : public KeyboardReportParser
{
 protected:
  void OnControlKeysChanged(uint8_t before, uint8_t after);
  void OnKeyDown(uint8_t mod, uint8_t key);
  void OnKeyUp(uint8_t mod, uint8_t key);
};

#define pressOrRelease(key, offset)                       \
  do {                                                    \
    if (bmod.key != amod.key) {                           \
      k = pgm_read_byte(keys + offset);                   \
      amod.key ? Keyboard.press(k) : Keyboard.release(k); \
    }                                                     \
  } while (0)

void
KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after)
{
  MODIFIERKEYS bmod;
  MODIFIERKEYS amod;

  *((uint8_t *)&bmod) = before;
  *((uint8_t *)&amod) = after;

  uint8_t k;

  pressOrRelease(bmLeftCtrl, 0xE0);
  pressOrRelease(bmLeftShift, 0xE1);
  pressOrRelease(bmLeftAlt, 0xE2);
  pressOrRelease(bmLeftGUI, 0xE3);
  pressOrRelease(bmRightCtrl, 0xE4);
  pressOrRelease(bmRightShift, 0xE5);
  pressOrRelease(bmRightAlt, 0xE6);
  pressOrRelease(bmRightGUI, 0xE7);
}

void
KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  uint8_t k = pgm_read_byte(keys + key);
  Keyboard.press(k);
}

void
KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  uint8_t k = pgm_read_byte(keys + key);
  Keyboard.release(k);
}

class MouseRptParser : public MouseReportParser
{
 protected:
  void OnMouseMove(MOUSEINFO *mi);
  void OnLeftButtonUp(MOUSEINFO *mi);
  void OnLeftButtonDown(MOUSEINFO *mi);
  void OnRightButtonUp(MOUSEINFO *mi);
  void OnRightButtonDown(MOUSEINFO *mi);
  void OnMiddleButtonUp(MOUSEINFO *mi);
  void OnMiddleButtonDown(MOUSEINFO *mi);
};

const uint8_t mouse_movement_scale = 3;

void
MouseRptParser::OnMouseMove(MOUSEINFO *mi)
{
  Mouse.move(mi->dX * mouse_movement_scale, mi->dY * mouse_movement_scale);
};

#define pressOrReleaseMouse(method, key)                                  \
  void MouseRptParser::method##Up(MOUSEINFO *mi) { Mouse.release(key); }; \
  void MouseRptParser::method##Down(MOUSEINFO *mi) { Mouse.press(key); };

pressOrReleaseMouse(OnLeftButton, MOUSE_LEFT);
pressOrReleaseMouse(OnRightButton, MOUSE_RIGHT);
pressOrReleaseMouse(OnMiddleButton, MOUSE_MIDDLE);

USB Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD | USB_HID_PROTOCOL_MOUSE> HidComposite(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);

KbdRptParser KbdPrs;
MouseRptParser MousePrs;

void
setup()
{
  Usb.Init();

  Keyboard.begin();

  delay(200);

  HidComposite.SetReportParser(0, &KbdPrs);
  HidComposite.SetReportParser(1, &MousePrs);
  HidKeyboard.SetReportParser(0, &KbdPrs);
  HidMouse.SetReportParser(0, &MousePrs);
}

void
loop()
{
  Usb.Task();
}
