#ifndef _LIBRARY_DISPLAY_H
#define _LIBRARY_DISPLAY_H

void Display_Init();
void Send_char_SPI(unsigned char carac);
void Display_4char(unsigned char buffer[4]);
void Display_Clear();
void Display_SetLuminosity(unsigned char lum);
void Display_Points(unsigned char code);
void Display_1char( unsigned char num, unsigned char code);
void affiche_Vitesse( int vitesse );

#endif
