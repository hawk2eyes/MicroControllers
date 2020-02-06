/*
 * OpdrachtenWeek1.h
 *
 * Created: 30/01/2020 11:03:32
 *  Author: jelmer
 */ 
#pragma once

void wait(int);
void week1_opdracht_1();
void week1_opdracht_2();
void week1_opdracht_3();
void week1_opdracht_4();
void week1_opdracht_5();
void week1_opdracht_6();
void week2_opdracht1();
void wipe();

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void clear_screen();
void move_to_right();

void ioisrMain();