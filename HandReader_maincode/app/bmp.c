#include "window_includes.h"

const unsigned char gImage_LOGO[282] = { //0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF8,0XF8,0XF8,0XF8,0XF8,0XF8,
0XF8,0X78,0X78,0X38,0X18,0X18,0X08,0X00,0X00,0XF8,0XF8,0X78,0X78,0X38,0X38,0X18,
0X18,0X18,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0X81,0X80,0XC0,0XC0,
0XE0,0XE0,0XF0,0XF8,0XF8,0X7C,0X04,0X01,0X80,0XC0,0XE0,0XE0,0XF0,0XF8,0XF8,0XFC,
0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0X1F,0X0F,0X0F,0X07,0X03,0X03,
0X01,0X01,0X80,0XC0,0XC0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X1F,0X1F,0X1F,0X1F,0X18,0X18,0X18,0X1C,0X1E,0X1E,0X1F,0X1F,
0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFC,0XFC,
0X1C,0X38,0X70,0XE0,0XC0,0X00,0XFC,0XFC,0X00,0X00,0X0C,0X1C,0X78,0XE0,0XC0,0XE0,
0X70,0X38,0X1C,0X04,0X00,0XFC,0XFC,0X38,0XF8,0XF0,0XC0,0X80,0X00,0XFC,0XFC,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0X1F,0X00,0X00,
0X00,0X01,0X03,0X0F,0X1F,0X1F,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0X1F,0X00,0X00,
0X00,0X00,0X00,0X1F,0X1F,0X00,0X00,0X01,0X03,0X07,0X0E,0X1F,0X1F,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,};

const unsigned char gImage_yunengyibiao[405] = { /* 0X22,0X01,0X51,0X00,0X26,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X0F,0X1E,0X3C,0X78,0XF0,0XE0,0XE0,0XF0,0XFC,0X7E,0X1F,0X07,0X00,0XE0,
0XE0,0XE0,0X00,0X00,0X00,0X00,0X00,0XE0,0XE0,0XE0,0X00,0X00,0XFC,0XFC,0XFC,0XFC,
0XF0,0XC0,0X00,0X00,0X00,0XFC,0XFC,0XFC,0X00,0X00,0XC0,0XE0,0XE0,0XF0,0X70,0X70,
0X70,0X70,0XE0,0XE0,0XC0,0X80,0X00,0X00,0XC0,0XE0,0XE0,0XE0,0X60,0X60,0X60,0XE0,
0XE0,0XE0,0XC0,0X00,0X00,0XC0,0XE0,0XF0,0XF0,0XF0,0XF0,0XF0,0XF0,0XF0,0XE0,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,
0XFF,0XFF,0XFF,0X80,0X80,0X80,0X80,0X80,0XFF,0XFF,0XFF,0X00,0X00,0XFF,0XFF,0XFF,
0X01,0X03,0X0F,0X3F,0XFE,0XFC,0XFF,0XFF,0XFF,0X00,0X00,0XFF,0XFF,0XFF,0X8C,0X0C,
0X0C,0X0C,0X0C,0X8C,0XEF,0XEF,0XEF,0X00,0X00,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,
0X00,0XFF,0XFF,0XFF,0X00,0X00,0X3F,0XFF,0XFF,0XE1,0XC0,0XC0,0XC1,0XE1,0XFF,0XFF,
0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0X03,0X03,0X00,0X00,0X00,0X00,
0X00,0X01,0X01,0X03,0X03,0X03,0X03,0X03,0X03,0X03,0X01,0X01,0X00,0X00,0X03,0X03,
0X03,0X00,0X00,0X00,0X00,0X00,0X03,0X03,0X03,0X03,0X00,0X00,0X01,0X03,0X03,0X07,
0X07,0X07,0X07,0X07,0X07,0X07,0X03,0X01,0X00,0X00,0X03,0X03,0X03,0X00,0X00,0X00,
0X00,0X00,0X03,0X03,0X03,0X00,0X00,0X3C,0X7C,0X71,0X71,0X71,0X71,0X71,0X71,0X7F,
0X7F,0X3F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,};

const unsigned char gImage_nanjynybkjyxgs[363] = { /* 0X22,0X01,0X79,0X00,0X12,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XE0,0XE0,0X00,0X00,0XE0,
0XE0,0X00,0X00,0XE0,0XE0,0X00,0XE0,0XE0,0X00,0X00,0XE0,0XE0,0X00,0X00,0XE0,0XE0,
0X00,0XE0,0XE0,0X00,0X00,0XE0,0XE0,0X00,0X00,0XE0,0XE0,0X00,0X00,0X00,0X00,0XE0,
0XE0,0X60,0X60,0XE0,0XE0,0X00,0XE0,0XE0,0X00,0X00,0X00,0XE0,0XE0,0X00,0XE0,0XE0,
0X60,0X60,0XE0,0XE0,0X00,0XF0,0XF8,0X98,0X98,0X98,0XF8,0XF0,0X00,0X00,0X70,0XF8,
0X98,0X98,0XF8,0X70,0X00,0X00,0X00,0X80,0XC0,0XE0,0X60,0X60,0X60,0X00,0XC0,0XE0,
0X60,0X60,0XE0,0XC0,0X00,0X00,0XE0,0XE0,0X60,0X60,0XE0,0XE0,0X60,0X60,0XE0,0XE0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X07,0X0F,0X0E,0X0C,0X0F,0X0F,0X0C,0X0E,0X0F,0X07,0X00,0X07,
0X0F,0X0E,0X0C,0X0F,0X0F,0X0C,0X0E,0X0F,0X07,0X00,0X07,0X0F,0X0E,0X0C,0X0F,0X0F,
0X0C,0X0E,0X0F,0X07,0X00,0X0C,0X0C,0X00,0X0F,0X0F,0X00,0X00,0X0F,0X0F,0X00,0X03,
0X07,0X3F,0X3E,0X0F,0X07,0X03,0X00,0X0F,0X0F,0X00,0X00,0X0F,0X0F,0X00,0X0C,0X0D,
0X0D,0X0D,0X0D,0X0F,0X07,0X00,0X00,0X0F,0X1F,0X19,0X19,0X1F,0X0F,0X00,0X0C,0X0C,
0X03,0X07,0X0E,0X0C,0X0C,0X0C,0X00,0X07,0X0F,0X0C,0X0C,0X0F,0X07,0X00,0X00,0X0F,
0X0F,0X00,0X00,0X0F,0X0F,0X00,0X00,0X0F,0X0F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};



const unsigned char gImage_TIME[66] = { /* 0X22,0X01,0X21,0X00,0X10,0X00, */
0XFE,0X02,0X62,0X62,0XE2,0XE2,0X62,0X62,0X02,0X62,0XE2,0XE2,0X62,0X02,0XE2,0XE2,
0XC2,0X82,0X02,0X02,0X02,0X82,0XC2,0XE2,0XE2,0X02,0XE2,0XE2,0X62,0X62,0X62,0X02,
0XFE,0XFF,0X80,0X80,0X80,0XBF,0XBF,0X80,0X80,0X80,0XB0,0XBF,0XBF,0XB0,0X80,0XBF,
0XBF,0X83,0X87,0XBE,0XBC,0XBE,0X87,0X83,0XBF,0XBF,0X80,0XBF,0XBF,0XB3,0XB3,0XB3,
0X80,0XFF,};

/********************************������************************************/
const unsigned char gImage_now_msg[128] = { /* 0X22,0X01,0X20,0X00,0X20,0X00, */
0X00,0X00,0XF8,0X08,0X08,0X48,0X08,0XC8,0X48,0X08,0X08,0XC8,0XE8,0X68,0X38,0X38,
0X78,0XA8,0X68,0XE8,0XC8,0X08,0X08,0X48,0XC8,0X08,0X48,0X08,0X08,0XF8,0X00,0X00,
0X00,0X00,0XFF,0X00,0X00,0X00,0X03,0XF1,0XF0,0X00,0XFF,0X9F,0X9F,0X9D,0X98,0X98,
0X95,0X8A,0X95,0X9F,0X9F,0XFF,0X20,0XF0,0XF1,0X03,0X00,0X00,0X00,0XFF,0X00,0X00,
0X00,0X00,0XFF,0X00,0XF1,0XF9,0X19,0X19,0X19,0X19,0X19,0X01,0XF9,0XF9,0X01,0X01,
0X01,0X01,0XF9,0XF9,0X01,0XF9,0XF9,0X99,0X99,0X99,0XF9,0X71,0X00,0XFF,0X00,0X00,
0X00,0X00,0X7F,0X40,0X47,0X4F,0X4C,0X4C,0X4C,0X4C,0X4C,0X40,0X47,0X47,0X4E,0X4C,
0X4C,0X4E,0X47,0X47,0X40,0X4F,0X4F,0X41,0X43,0X47,0X4E,0X4C,0X40,0X7F,0X00,0X00,
};


const unsigned char gImage_stor_msg[128] = { /* 0X22,0X01,0X20,0X00,0X20,0X00, */
0X00,0X00,0XF8,0X08,0XA8,0XE8,0XA8,0XE8,0XE8,0XE8,0X68,0X68,0X68,0X68,0X68,0X68,
0X68,0X68,0X68,0XE8,0XA8,0XE8,0XE8,0X68,0X68,0XE8,0X28,0XE8,0X08,0XF8,0X00,0X00,
0X00,0X00,0XFF,0X00,0XAA,0XFF,0XAA,0XFF,0XFF,0XFF,0X00,0X1C,0X3E,0X36,0X3E,0X36,
0X3E,0X3E,0X1C,0XFF,0XFF,0XF4,0XFF,0X00,0X00,0XFF,0XAC,0XFF,0X00,0XFF,0X00,0X00,
0X00,0X00,0XFF,0X00,0XFA,0XFB,0XC2,0XC3,0XC3,0XC3,0XFA,0XFA,0X02,0X1A,0X1A,0XFA,
0XFA,0X1A,0X1A,0X03,0XFB,0XFA,0XFB,0X9A,0X9A,0X9B,0X9A,0X9B,0X00,0XFF,0X00,0X00,
0X00,0X00,0X7F,0X40,0X5F,0X5F,0X41,0X41,0X41,0X41,0X5F,0X5F,0X40,0X58,0X58,0X5F,
0X5F,0X58,0X58,0X40,0X59,0X59,0X59,0X59,0X59,0X59,0X5F,0X5F,0X40,0X7F,0X00,0X00,
};

const unsigned char gImage_loca_msg[128] = {/* 0X22,0X01,0X20,0X00,0X20,0X00, */
0X00,0X00,0XF8,0X08,0XE8,0X28,0X28,0X28,0X88,0XC8,0XE8,0X68,0X68,0XA8,0XA8,0XE8,
0XE8,0XE8,0XE8,0XE8,0X28,0X68,0XC8,0X88,0X28,0X28,0X28,0XE8,0X08,0XF8,0X00,0X00,
0X00,0X00,0XFF,0X00,0XF9,0X3C,0XAE,0XFF,0X7F,0X7B,0XEF,0XE7,0XF3,0XB3,0XB9,0X8D,
0X8D,0X8D,0XB9,0XB1,0XE3,0XE7,0X6F,0X7D,0XF7,0XEE,0X5C,0XFB,0X00,0XFF,0X00,0X00,
0X00,0X00,0XFF,0X00,0XF9,0XF9,0X99,0X99,0X98,0X98,0X98,0X99,0X01,0XF9,0XF9,0X81,
0X01,0X81,0XF9,0XF9,0X01,0XF8,0XF8,0X98,0X99,0X99,0X99,0X99,0X00,0XFF,0X00,0X00,
0X00,0X00,0X7F,0X40,0X59,0X59,0X59,0X59,0X59,0X59,0X5F,0X5F,0X40,0X40,0X41,0X5F,
0X5F,0X5F,0X41,0X40,0X40,0X59,0X59,0X59,0X59,0X59,0X5F,0X5F,0X40,0X7F,0X00,0X00,
};


const unsigned char gImage_cfg_msg[128] = {/* 0X22,0X01,0X20,0X00,0X20,0X00, */
0X00,0X00,0XF8,0X08,0X88,0XC8,0XC8,0XC8,0XC8,0X88,0X08,0X08,0X08,0X08,0X08,0X08,
0X88,0X88,0XC8,0XC8,0XC8,0XC8,0X88,0X88,0X08,0X08,0X08,0X08,0X08,0XF8,0X00,0X00,
0X00,0X00,0XFF,0X00,0X07,0X0F,0X1F,0X3E,0X7D,0XFB,0XF7,0XEE,0XFC,0X78,0XE0,0X80,
0X80,0X00,0XC0,0X63,0XF7,0XFE,0XFD,0X6B,0X77,0XFE,0XF8,0XF0,0X00,0XFF,0X00,0X00,
0X00,0X00,0XFF,0X00,0XE2,0XF2,0XFA,0X3A,0X1A,0X1A,0X1A,0X1A,0X03,0XFB,0XFA,0XFB,
0X9B,0X9B,0X9B,0X03,0XF3,0XFB,0X3A,0X9A,0X9A,0X9A,0XBA,0XBA,0X00,0XFF,0X00,0X00,
0X00,0X00,0X7F,0X40,0X47,0X4F,0X5F,0X5C,0X58,0X58,0X58,0X58,0X40,0X5F,0X5F,0X5F,
0X41,0X41,0X41,0X40,0X47,0X4F,0X5E,0X5C,0X59,0X59,0X5F,0X5F,0X40,0X7F,0X00,0X00,
};

const unsigned char gImage_buttonframe[44] = { /* 0X22,0X01,0X16,0X00,0X0B,0X00, */
0XFF,0X01,0X8D,0X05,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,
0X01,0X01,0X05,0X8D,0X01,0XFF,0X07,0X04,0X05,0X05,0X04,0X04,0X04,0X04,0X04,0X04,
0X04,0X04,0X04,0X04,0X04,0X04,0X04,0X04,0X05,0X05,0X04,0X07,};

const unsigned char gImage_sendmsg[128] = { /* 0X22,0X01,0X20,0X00,0X20,0X00, */
0X00,0X00,0XF8,0X08,0X68,0X28,0X08,0X08,0X08,0X08,0X08,0X28,0X28,0X68,0X68,0XE8,
0XE8,0XE8,0XC8,0XC8,0X88,0X88,0X08,0X08,0X08,0X08,0X28,0X68,0X08,0XF8,0X00,0X00,
0X00,0X00,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X1E,0X1E,0X8C,0X8C,0XCC,0XCC,0XE0,
0XE0,0XF1,0XFB,0XFF,0X7F,0X3F,0X1F,0X0E,0X04,0X00,0X00,0X00,0X00,0XFF,0X00,0X00,
0X00,0X00,0XFF,0X00,0X02,0X1A,0X1A,0XFA,0XFA,0XFA,0X1B,0X1B,0X03,0X1B,0X3B,0X7B,
0XF3,0XE3,0XC2,0XE2,0XF2,0X7A,0X3A,0X1A,0X02,0X02,0X02,0X02,0X00,0XFF,0X00,0X00,
0X00,0X00,0X7F,0X40,0X58,0X50,0X40,0X4F,0X4F,0X4F,0X40,0X40,0X40,0X48,0X4C,0X4E,
0X4F,0X47,0X43,0X47,0X4F,0X4E,0X4C,0X48,0X40,0X40,0X50,0X58,0X40,0X7F,0X00,0X00,
};


const unsigned char gImage_password[128] = { /* 0X22,0X01,0X20,0X00,0X20,0X00, */
0X00,0X00,0XF8,0X08,0X68,0X28,0X08,0X08,0X08,0XC8,0XC8,0XC8,0XC8,0X88,0X08,0X08,
0X08,0X48,0X48,0X48,0X88,0X88,0X88,0X88,0X88,0X08,0X28,0X68,0X08,0XF8,0X00,0X00,
0X00,0X00,0XFF,0X00,0X00,0X3C,0XE0,0X08,0X00,0XFF,0X80,0XFF,0XFF,0XFF,0X7F,0X1E,
0X1E,0X1E,0X1E,0X3E,0X1E,0X3E,0X1E,0X1E,0X00,0XE0,0X3C,0X00,0X00,0XFF,0X00,0X00,
0X00,0X00,0XFF,0X00,0X02,0X02,0X02,0XFA,0XFA,0XFB,0X9B,0X9B,0X9B,0XFA,0XF2,0X02,
0X82,0XF2,0XF2,0XBA,0X9A,0XBA,0XF2,0XF2,0X82,0X02,0X02,0X02,0X00,0XFF,0X00,0X00,
0X00,0X00,0X7F,0X40,0X58,0X50,0X40,0X4F,0X4F,0X4F,0X41,0X41,0X41,0X41,0X40,0X40,
0X4F,0X4F,0X4F,0X41,0X41,0X41,0X4F,0X4F,0X4F,0X40,0X50,0X58,0X40,0X7F,0X00,0X00,
};


const unsigned char gImage_usercode[128] = { /* 0X22,0X01,0X20,0X00,0X20,0X00, */
0X00,0X00,0XF8,0X08,0X68,0X28,0X08,0X08,0X08,0X08,0X08,0X08,0X08,0X08,0X88,0XC8,
0XC8,0X88,0X08,0X08,0X08,0X08,0X08,0X08,0X08,0X28,0X28,0X68,0X08,0XF8,0X00,0X00,
0X00,0X00,0XFF,0X00,0X00,0X00,0XFC,0X00,0X02,0X13,0X18,0X3C,0X7E,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X7E,0X3C,0X18,0X13,0X02,0X00,0XFE,0X00,0X00,0X00,0XFF,0X00,0X00,
0X00,0X00,0XFF,0X00,0X02,0X02,0X02,0X02,0XFA,0XFB,0X03,0X03,0X03,0XFB,0XFB,0X03,
0XFB,0XFB,0XDB,0XDB,0XDB,0XDB,0XDB,0XDA,0X02,0X02,0X02,0X02,0X00,0XFF,0X00,0X00,
0X00,0X00,0X7F,0X40,0X58,0X50,0X40,0X40,0X47,0X4F,0X4E,0X4E,0X4E,0X4F,0X47,0X40,
0X4C,0X4C,0X4C,0X4C,0X4C,0X4C,0X4F,0X4F,0X40,0X40,0X50,0X58,0X40,0X7F,0X00,0X00,
};

const unsigned char gImage_datamark[128] = { /* 0X22,0X01,0X20,0X00,0X20,0X00, */
0X00,0X00,0XF8,0X08,0X68,0X28,0X08,0X08,0X08,0X08,0X88,0X88,0X88,0X88,0X88,0X88,
0X88,0X88,0X88,0X88,0X88,0X88,0X08,0X08,0X08,0X08,0X28,0X68,0X08,0XF8,0X00,0X00,
0X00,0X00,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XBB,0XAA,0XAA,0XAA,0XAA,0XAA,
0XBB,0XBB,0XBB,0XBB,0XAA,0XBB,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0X00,0X00,
0X00,0X00,0XFF,0X00,0X02,0X02,0X02,0X02,0XFA,0XFA,0X1B,0X1A,0X1A,0XFA,0XF2,0X02,
0X03,0XC3,0XF3,0XF3,0X1A,0X1B,0XF2,0XF2,0XC2,0X02,0X02,0X02,0X00,0XFF,0X00,0X00,
0X00,0X00,0X7F,0X40,0X58,0X50,0X40,0X40,0X4F,0X4F,0X4E,0X4E,0X4E,0X4F,0X47,0X40,
0X40,0X4F,0X4F,0X4F,0X43,0X43,0X4F,0X4F,0X4F,0X40,0X50,0X58,0X40,0X7F,0X00,0X00,
};

