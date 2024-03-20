

#include <Wire.h>

#define SLAVE_ADDRESS_LCD 0x27  // change this according to ur setup

void lcd_send_cmd (char cmd);
void lcd_send_data (char data);
void lcd_clear (void);
void lcd_init (void);
void lcd_put_cur(int row, int col);
void lcd_send_string (char *str);


void lcd_send_cmd (char cmd)
{
    char data_u, data_l;
    uint8_t DATA;
    data_u = (cmd&0xf0);
    data_l = ((cmd<<4)&0xf0);
    Wire.beginTransmission(SLAVE_ADDRESS_LCD);
    DATA = data_u|0x0C;  //en=1, rs=0
    Wire.write(DATA);
    DATA = data_u|0x08;  //en=0, rs=0
    Wire.write(DATA);
    DATA = data_l|0x0C;  //en=1, rs=0
    Wire.write(DATA);
    DATA = data_l|0x08;  //en=0, rs=0
    Wire.write(DATA);
    Wire.endTransmission();
    delay(50);
}

void lcd_send_data (char data)
{
    char data_u, data_l;
    uint8_t DATA;
    data_u = (data&0xf0);
    data_l = ((data<<4)&0xf0);
    Wire.beginTransmission(SLAVE_ADDRESS_LCD);
    DATA = data_u|0x0D;  //en=1, rs=0
    Wire.write(DATA);
    DATA = data_u|0x09;  //en=0, rs=0
    Wire.write(DATA);
    DATA = data_l|0x0D;  //en=1, rs=0
    Wire.write(DATA);
    DATA = data_l|0x09;  //en=0, rs=0
    Wire.write(DATA);
    Wire.write(DATA);
    Wire.endTransmission();
    delay(50);
}

void lcd_clear (void)
{
    lcd_send_cmd (0x80);
    for (int i=0; i<70; i++)
    {
        lcd_send_data (' ');
    }
}

void lcd_init (void)
{
    // 4 bit initialisation
    delay(100);  // wait for >40ms
    lcd_send_cmd (0x30);
    delay(50);  // wait for >4.1ms
    lcd_send_cmd (0x30);
    delay(50);  // wait for >100us
    lcd_send_cmd (0x30);
    delay(50);
    lcd_send_cmd (0x20);  // 4bit mode
    delay(50);

    // dislay initialisation
    lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
    delay(50);
    lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
    delay(50);
    lcd_send_cmd (0x01);  // clear display
    delay(50);
    delay(50);
    lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
    delay(50);
    lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    lcd_send_cmd (col);
}


void lcd_send_string (char *str)
{
    while (*str) lcd_send_data (*str++);
}


void setup() {
    char character_1[12]="Hello RL78!";

	pinMode(7, OUTPUT);

    Wire.begin();        // join i2c bus (address optional for master)

    lcd_init();
    lcd_send_string(character_1);
}

void loop() {
    delay(1000);                       // wait for a second
}
