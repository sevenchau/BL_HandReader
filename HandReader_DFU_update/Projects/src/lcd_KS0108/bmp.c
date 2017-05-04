#include "bmp.h"

const unsigned char gImage_UpGrade[288] = { /* 0X22,0X01,0X30,0X00,0X30,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X80,0X40,0X40,
0X40,0X20,0X20,0XFE,0X02,0X02,0XFA,0X02,0X02,0X02,0XFA,0X02,0XFE,0X00,0X00,0X80,
0X40,0X20,0X20,0X40,0X40,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X0C,0X34,0XC2,0X02,0X82,0X81,0X81,0X81,0XC0,0XC0,0XC0,0XE0,
0XE0,0XE0,0XE0,0XFF,0X00,0X00,0XF7,0X94,0X94,0X94,0XF7,0X00,0XFF,0XF2,0XF1,0XE0,
0XC0,0XC0,0X80,0X80,0X00,0X00,0X01,0X01,0X02,0X04,0X04,0X08,0X90,0X50,0X20,0X00,
0X00,0X30,0X48,0X84,0X84,0X02,0X01,0X03,0X07,0X07,0X0F,0X1F,0X1F,0X3F,0X7F,0XFD,
0XF9,0XF1,0XA1,0X41,0X80,0X00,0X1F,0X00,0X00,0X00,0X80,0X40,0X21,0XA1,0XF1,0XF9,
0XFD,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFE,0XFC,0XFA,0XE1,0X01,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X02,0XFC,0XF8,0XF8,0XF0,0XE0,0XE0,0XE0,0XF0,0XF0,
0XF0,0XF9,0XFB,0XFB,0XFE,0XFD,0XFE,0XFC,0XFE,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X23,0X20,0X13,0X1C,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0X0F,0X1F,0X1F,0X3F,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X7F,0X7F,0X7F,0X3F,0X3F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X03,
0X03,0X07,0X0F,0X1F,0X1F,0X1F,0X1F,0X0F,0X0F,0X0F,0X07,0X07,0X03,0X03,0X03,0X01,
0X01,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_MOBILE[288] = { /* 0X22,0X01,0X30,0X00,0X30,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X0F,0XE7,0X23,0XA3,
0XA3,0XA3,0XA3,0XA3,0XA3,0XA3,0XAB,0XAB,0XAB,0XAB,0XAB,0XAB,0XA3,0XA3,0XA3,0XA3,
0XA3,0XA3,0X23,0XE7,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0XFF,0X00,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X00,0XFF,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X07,0X04,0X05,
0X05,0X85,0XC5,0X05,0XC5,0X65,0X25,0XA5,0XA5,0XA5,0X25,0X65,0XC5,0X05,0XC5,0X85,
0X05,0X05,0X04,0X07,0XC0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,
0X60,0X63,0X66,0X00,0X07,0X0C,0X08,0X6B,0X6B,0X6B,0X08,0X0C,0X07,0X00,0X66,0X63,
0X60,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,
0X66,0X66,0X66,0X00,0X00,0X00,0X00,0X66,0X66,0X66,0X00,0X00,0X00,0X00,0X66,0X66,
0X66,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X80,
0X86,0X86,0X86,0XA0,0XA0,0XA0,0XA0,0XA6,0XA6,0XA6,0XA0,0XA0,0XA0,0XA0,0X86,0X86,
0X86,0X80,0XC0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

const unsigned char gImage_Computer[288] = { /* 0X22,0X01,0X30,0X00,0X30,0X00, */
0X00,0XE0,0XE0,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,
0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,
0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0X60,0XE0,0XE0,0X00,
0X00,0XFF,0XFF,0X00,0XFF,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,
0XC1,0XC1,0XC1,0XC1,0XC1,0XC1,0XC1,0X01,0XC1,0XC1,0XC1,0XC1,0XC1,0XC1,0XC1,0X01,
0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0XFF,0X00,0XFF,0XFF,0X00,
0X00,0XFF,0XFF,0X00,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XEF,0XEF,0XEF,0XEF,0XEF,0XEF,0XEF,0X00,0XEF,0XEF,0XEF,0XEF,0XEF,0XEF,0XEF,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0X00,0XFF,0XFF,0X00,
0X00,0XFF,0XFF,0X00,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X07,0X07,0X07,0X07,0X07,0X07,0X07,0X00,0X07,0X07,0X07,0X07,0X07,0X07,0X07,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0X00,0XFF,0XFF,0X00,
0X00,0X0F,0X0F,0X0C,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,
0X0D,0X0D,0XFD,0XFD,0XFD,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0XFD,0XFD,0XFD,0X0D,0X0D,
0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0C,0X0F,0X0F,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,
0X0C,0X0C,0X0F,0X0F,0X0F,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0F,0X0F,0X0F,0X0C,0X0C,
0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,
};

