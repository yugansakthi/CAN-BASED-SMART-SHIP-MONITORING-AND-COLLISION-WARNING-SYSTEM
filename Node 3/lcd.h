 #ifndef __lcd_h__
#define __lcd_h__
void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char *);
void LCD_INTEGER(int);
void LCD_FLOAT(double);
void LCD_TITLE(void);
#endif
