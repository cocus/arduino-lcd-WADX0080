/**
 * LCD board #: WADX0080
 * LCD controller: S6A0069
 *
 * RESET 74HC164 => reset => VCC
 * connector pin 12 => A2 74HC164 => data
 * connector pin 13 => CLOCK 74HC164 => clock
 * connector pin 3 => GND
 * connector pin 1 => VCC > 5v
 * connector pin 6 => LCD RS
 * connector pin 5 => LCD E
 *
 * LCD D0 => QA
 * LCD D1 => QB
 * LCD D2 => QC
 * LCD D3 => QD
 * LCD D4 => QE
 * LCD D5 => QF
 * LCD D6 => QG
 * LCD D7 => QH
 */

#include <Arduino.h>
#include <SPI.h>

/* D2 connected to pin 6 */
#define RS 2
/* D3 connected to pin 5 */
#define E 3

/* connect MOSI (pin D11) to pin pin 12 */
/* connect SCK (pin D13) to pin pin 32 */

void lcd_pulse(void)
{
  digitalWrite(E, 1);
  delayMicroseconds(1);
  digitalWrite(E, 0);
}

void lcd_instruction(uint8_t instr)
{
  digitalWrite(RS, 0);
  SPI.transfer(instr);
  lcd_pulse();
}

void lcd_data(uint8_t instr)
{
  digitalWrite(RS, 1);
  SPI.transfer(instr);
  lcd_pulse();
}

void lcd_clear(void)
{
  lcd_instruction(0b0000001);
  delay(2);
}

void lcd_puts(const char* text)
{
  while(*text)
  {
    lcd_data(*text);
    delayMicroseconds(44);
    text++;
  }
}

void lcd_gotoxy(uint8_t x, uint8_t y)
{
    uint8_t addr;
    if (y >= 20)
        return;
    switch (x)
    {
    case 0:
        addr = 0x00;
        break;
    case 1:
        addr = 0x28;
        break;
    case 2:
        addr = 0x14;
        break;
    case 3:
        addr = 0x3C;
        break;
    default:
        return;
    }
    addr += y;
    lcd_instruction(0x80 | addr);
    delayMicroseconds(40);
}

void setup()
{
  pinMode(RS, OUTPUT);
  pinMode(E, OUTPUT);
  SPI.begin();

  lcd_instruction(0b00111100); /* function set, 2 line mode, display on */
  delayMicroseconds(40);
  lcd_instruction(0b00001100); /* display on, cursor off, blink off */
  delayMicroseconds(40);
  lcd_clear();
  delay(2);
  lcd_instruction(0b00000110); /* entry mode set, increment, shift off */

  delay(500);

  lcd_gotoxy(0, 0);
  lcd_puts("Testing the");
  lcd_gotoxy(1, 0);
  lcd_puts("thing!");
}

void loop()
{

}
