#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int main ()
{
    DDRA |= (1 << DDA0) | (1 << DDA1);
    DDRD = 0X00;

    while(true)
    {
        PORTA = (1 << PINA0);
        _delay_ms(1000);
        PORTA = (1 << PINA1);
        _delay_ms(1000);

        int compteur = 0;
        while(compteur < 1000)
        {
        PORTA = (1 << PINA0);
        _delay_ms(1);
        PORTA = (1 << PINA1);
        _delay_ms(1);
        compteur = compteur + 1;
        }
        

    }
    
    return 0;
}