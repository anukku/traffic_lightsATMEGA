/*******************************************************
This program was created by the CodeWizardAVR V4.02 
Automatic Program Generator
© Copyright 1998-2024 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : traffic_lights
Version : 
Date    :  5/ 6/2024
Author  : 
Company : 
Comments: 


Chip type               : ATmega164A
Program type            : Application
AVR Core Clock frequency: 20.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

// I/O Registers definitions
#include <io.h>
#include <mega164a.h>
#include <delay.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Definirea functiilor pentru controlul starii semafoarelor
void cargreen_day() {
    uint16_t x = 0; 
    bool apasat = false;
    PORTB.0 = 0; // Red masini
    PORTB.1 = 0; // Yellow masini 
    PORTB.3 = 1; // Red pietoni      
    PORTB.2 = 1; // Green masini
    PORTB.4 = 0; // Green pietoni
    
    
    
    do {
        delay_ms(1);
        x++;

        if (!PIND.2 && !apasat) {
            delay_ms(200); // debounce
            x += 2200;
            apasat = true;
        }
    } while (x <= 5000);
}

void caryellow_day() {

    PORTB.0 = 0; // Red masini
    PORTB.1 = 1; // Yellow masini
    PORTB.2 = 0; // Green masini
    PORTB.3 = 1; // Red pietoni
    PORTB.4 = 0; // Green pietoni
    delay_ms(2000);
}

void carred_day() {

    uint16_t dly = 0;
    PORTB.0 = 1; // Red masini
    PORTB.1 = 0; // Yellow masini
    PORTB.2 = 0; // Green masini
    delay_ms(750);
    PORTB.3 = 0; // Red pietoni
    PORTB.4 = 1; // Green pietoni
    delay_ms(6000);
    
    while (dly <= 2000) {
        dly += 200;
        PORTB.4 = 0; // Green pietoni 
        delay_ms(200);
        PORTB.4 = 1; // Green pietoni 
        delay_ms(200);
    }
    PORTB.4 = 0; 
}

void cargreen_night() {
    uint16_t x = 0; 
    bool apasat = false;
    PORTB.0 = 0; // Red masini
    PORTB.1 = 0; // Yellow masini 
    PORTB.3 = 1; // Red pietoni  
    PORTB.2 = 1; // Green masini
    PORTB.4 = 0; // Green pietoni
    
    
    
    do {
        delay_ms(1);
        x++;

        if (!PIND.2 && !apasat) {
            delay_ms(200); // debounce
            x += 2200;
            apasat = true;
        }
    } while (x <= 3500);
}

void caryellow_night() {

    PORTB.0 = 0; // Red masini
    PORTB.1 = 1; // Yellow masini
    PORTB.2 = 0; // Green masini
    PORTB.3 = 1; // Red pietoni
    PORTB.4 = 0; // Green pietoni
    delay_ms(2000);
}

void carred_night() {

    uint16_t dly = 0;
    PORTB.0 = 1; // Red masini
    PORTB.1 = 0; // Yellow masini
    PORTB.2 = 0; // Green masini
    delay_ms(750);
    PORTB.3 = 0; // Red pietoni
    PORTB.4 = 1; // Green pietoni
    delay_ms(3500);
    
    while (dly <= 2000) {
        dly += 200;
        PORTB.4 = 0; // Green pietoni 
        delay_ms(200);
        PORTB.4 = 1; // Green pietoni 
        delay_ms(200);
    }
    PORTB.4 = 0; 
}

void main(void) {
    int k = 0;
    // Configurarea pinilor pentru LED-urile semaforului pentru ma?ini
    DDRB.0 = 1; // Configure PB0 as output (rosu masini)
    DDRB.1 = 1; // Configure PB1 as output (galben masini)
    DDRB.2 = 1; // Configure PB2 as output (verde masini)
    
    DDRB.3 = 1; // Configure PB3 as output (rosu pietoni)
    DDRB.4 = 1; // Configure PB4 as output (verde pietoni)

    // Configurarea pinilor pentru butonul de trecere a pietonilor
    DDRD.2 = 0; // Configure PD2 as input pentru butonul de trecere a pietonilor
    PORTD.2 = 1; // Activarea rezistentei pull-up pentru PD2

    while (1) {
        // Apelarea func?iilor pentru controlul starii semafoarelor
        if(k < 8){    
            cargreen_day();
            caryellow_day();
            carred_day();
            k++;
        }
        else if(k < 15){
            cargreen_night();
            caryellow_night();
            carred_night();
            k++;
        }
        else{k = 0;}  
    }
}

