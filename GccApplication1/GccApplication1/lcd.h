/*
 * lcd.h
 *
 * Created: 12/02/2020 15:03:48
 *  Author: jelme
 */ 

#pragma once

void init();
void lcd_strobe_lcd_e(void);
void display_text(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_command(unsigned char byte);
void clear_screen();
void move_to_right();
void set_cursor(int position);
long long convert(int n);