#include <Wire.h>
#include <LiquidCrystal_I2C.h>

String s = "";
String m = "";

// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialisation des composants
void initializingComponents()
{
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();

}

void print(const char* format, ...)
{
    char buffer[512];

    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    Serial.print(buffer);
}

// Transforme ce qu'il y as dans le buffer en commande
void processingBuffer()
{
    int buff = 0;
    char readChar;
    buff = Serial.available();

    while (buff > 0)
    {
        readChar = Serial.read();
        delay(10);
        s = s + readChar;
        buff = Serial.available();
    }
}

// Traite la commande en fonction du stock
void processingOrder()
{
    if (s != "")
    {   

        m = s;
        print("Message: %s.\n", s.c_str());
      	lcd.clear();
        lcd.print(m.c_str());
        s = "";
      	
    } 
}

void setup()
{
    initializingComponents();
}

void loop()
{
    processingBuffer();
    processingOrder();
    delay (100);
}