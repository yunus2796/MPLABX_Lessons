// PIC18F452 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1H
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bit (Brown-out Reset enabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will cause RESET)
#pragma config LVP = ON         // Low Voltage ICSP Enable bit (Low Voltage ICSP enabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define EN PORTCbits.RC2
#define LDATA PORTD

#define _XTAL_FREQ 8000000

void LCD_CMD(unsigned char value);
void LCD_DATA(unsigned char value);

void main(void) {
unsigned char i;
unsigned char text1[]="LCD PROGRAMMINGdeneme";
unsigned char text2[]="     EEE548";

//ANSELC=0;
//ANSELD=0;
TRISC=0;
TRISD=0;
__delay_ms(15);
LCD_CMD(0X30);
__delay_us(160);
LCD_CMD(0X30);
__delay_us(160);
LCD_CMD(0X30);  // Function Set : Data transmission will be 8-bit. A two-line display will be used. 
__delay_us(160);
LCD_CMD(0X38); // Function Set : Data transmission will be 8-bit. A two-line display will be used. Pixel character size will be 5x7 pixel.
__delay_ms(2);
LCD_CMD(0X01); // Clear Display : It clears all screen and cursor and return start position.
__delay_ms(2);
LCD_CMD(0X06); // Entry Mode Set : Cursor moves left/right after every input.
__delay_ms(2);
LCD_CMD(0X0E); // Display On/Off Control : It opens a blinking character for cursor.
__delay_ms(2);
LCD_CMD(0X80); // Cursor moves to starting position on left top position.
__delay_ms(2);
for(i=0;i<15;i++){
    LCD_DATA(text1[i]);
    __delay_ms(2);
}
LCD_CMD(0XC0); // Cursor moves to new line.
__delay_ms(2);
for(i=0;i<11;i++){
    LCD_DATA(text2[i]);
    __delay_ms(2);
}
LCD_CMD(0XC0);
__delay_ms(2);
while (1);
}


void LCD_CMD(unsigned char value){
LDATA=value;
RS=0;
__delay_ms(2);
RW=0;
__delay_ms(2);
EN=1;
__delay_ms(2);
EN=0;
}

void LCD_DATA(unsigned char value){
LDATA=value;
RS=1;
__delay_ms(2);
RW=0;
__delay_ms(2);
EN=1;
__delay_ms(2);
EN=0;
}