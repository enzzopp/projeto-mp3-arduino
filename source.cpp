#include <LiquidCrystal.h>

LiquidCrystal lcd(11, 10, 9, 8, 7, 6);

#define B0  31
#define C1  33
#define CS1 35
#define D1  37
#define DS1 39
#define E1  41
#define F1  44
#define FS1 46
#define G1  49
#define GS1 52
#define AS1 58
#define B1  62
#define C2  65
#define CS2 69
#define D2  73
#define DS2 78
#define E2  82
#define F2  87
#define FS2 93
#define G2  98
#define GS2 104
#define A2  110
#define AS2 117
#define B2  123
#define C3  131
#define CS3 139
#define D3  147
#define DS3 156
#define E3  165
#define F3  175
#define FS3 185
#define G3  196
#define GS3 208
#define A3  220
#define AS3 233
#define B3  247
#define C4  262
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494
#define C5  523
#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880
#define AS5 932
#define B5  988
#define C6  1047
#define CS6 1109
#define D6  1175
#define DS6 1245
#define E6  1319
#define F6  1397
#define FS6 1480
#define G6  1568
#define GS6 1661
#define A6  1760
#define AS6 1865
#define B6  1976
#define C7  2093
#define CS7 2217
#define D7  2349
#define DS7 2489
#define E7  2637
#define F7  2794
#define FS7 2960
#define G7  3136
#define GS7 3322
#define A7  3520
#define AS7 3729
#define B7  3951
#define C8  4186
#define CS8 4435
#define D8  4699
#define DS8 4978
#define REST 0

// PINS
int BUZZER = 12;
int GREEN_LED = A1;
int RED_LED = A0;

int UP = 5;
int DOWN = 4;
int PLAY = 3;
int STOP = 2;

int CURRENT_LINE = 0;

int isPlaying = 0;
int isPaused = 0;

int BPM = 170;

// SET SONG LIST
String song_list[5] = {
    "Take on me",
    "Asa Branca",
    "Happy Birth",
    "Pacman",
    "Nokia"
};

void setup()
{

    // SET PINS MODE
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    pinMode(UP, INPUT);
    pinMode(DOWN, INPUT);
    pinMode(PLAY, INPUT);
    pinMode(STOP, INPUT);

    pinMode(BUZZER, OUTPUT);

    // SET SERIAL COMMUNICATION
    Serial.begin(9600);

    // SET LCD
    lcd.begin(16, 2);
    lcd.print("Loading...");
    delay(1000);
    showMenu();

    // SET ATTACH INTERRUPTS
    attachInterrupt(digitalPinToInterrupt(PLAY), togglePlayPause, FALLING);
    attachInterrupt(digitalPinToInterrupt(STOP), stopMusic, FALLING);

    // SET LEDS
    digitalWrite(GREEN_LED, 0);
    digitalWrite(RED_LED, 1);
}

void goUp()
{

    if (CURRENT_LINE <= 0)
    {
        CURRENT_LINE = 4;
        CURRENT_LINE++;
    }

    CURRENT_LINE--;
    showMenu();
}

void goDown()
{

    if (CURRENT_LINE >= 4)
    {
        CURRENT_LINE = 0;
        CURRENT_LINE--;
    }

    CURRENT_LINE++;
    showMenu();
}

void showMenu()
{
    lcd.clear();

    lcd.print("->");

    lcd.setCursor(3, 0);
    lcd.print(song_list[CURRENT_LINE]);

    lcd.setCursor(3, 1);
    (CURRENT_LINE == 4) ? 0 : lcd.print(song_list[CURRENT_LINE + 1]);

    delay(250);
}

void stopMusic()
{
    isPlaying = 0;
    isPaused = 0;

    digitalWrite(GREEN_LED, 0);
    digitalWrite(RED_LED, 1);

    noTone(BUZZER);

    lcd.clear();
    showMenu();
}

void togglePlayPause()
{
    if (isPlaying && !isPaused){

        isPaused = 1;

        digitalWrite(GREEN_LED, 0);
        digitalWrite(RED_LED, 1);

        lcd.clear();

        lcd.setCursor(3, 0);
        lcd.print("Paused");

        lcd.setCursor(3, 1);
        lcd.print(song_list[CURRENT_LINE]);

    }
    else
    {

        isPlaying = 1;
        isPaused = 0;

        digitalWrite(GREEN_LED, 1);
        digitalWrite(RED_LED, 0);

        lcd.clear();

        lcd.setCursor(3, 0);
        lcd.print("Playing");

        lcd.setCursor(3, 1);
        lcd.print(song_list[CURRENT_LINE]);
    }
}

int note_frequencies[5][130] = {
    
    // aha-take-on-me
    {66, 140, 
    FS5,8, FS5,8,D5,8, B4,8, REST,8, B4,8, REST,8, E5,8, 
    REST,8, E5,8, REST,8, E5,8, GS5,8, GS5,8, A5,8, B5,8,
    A5,8, A5,8, A5,8, E5,8, REST,8, D5,8, REST,8, FS5,8, 
    REST,8, FS5,8, REST,8, FS5,8, E5,8, E5,8, FS5,8, E5,8},

    // asa branca
    {98, 120, G4,8, A4,8, B4,4, D5,4, D5,4, B4,4, 
    C5,4, C5,2, G4,8, A4,8,
    B4,4, D5,4, D5,4, C5,4,
    B4,2, REST,8, G4,8, G4,8, A4,8,
    B4,4, D5,4, REST,8, D5,8, C5,8, B4,8,
    G4,4, C5,4, REST,8, C5,8, B4,8, A4,8,
    A4,4, B4,4, REST,8, B4,8, A4,8, G4,8,
    G4,2, REST,8, G4,8, G4,8, A4,8,
    B4,4, D5,4, REST,8, D5,8, C5,8, B4,8},

    // happy-birthday
    {52, 140,
    C4,4, C4,8, D4,-4, C4,-4, F4,-4,
    E4,-2, C4,4, C4,8, 
    D4,-4, C4,-4, G4,-4,
    F4,-2, C4,4, C4,8,
    C5,-4, A4,-4, F4,-4, 
    E4,-4, D4,-4, AS4,4, 
    AS4, 8, A4,-4, F4,-4, G4,-4,
    F4,-2},

    // pacman
    {64, 105,B4, 16, B5, 16, FS5, 16, DS5, 16,
    B5, 32, FS5, -16, DS5, 8, C5, 16,
    C6, 16, G6, 16, E6, 16, C6, 32, G6, -16, E6, 8,
    B4, 16,  B5, 16,  FS5, 16,   DS5, 16,  B5, 32,
    FS5, -16, DS5, 8,  DS5, 32, E5, 32,  F5, 32,
    F5, 32,  FS5, 32,  G5, 32,  G5, 32, GS5, 32,  A5, 16, B5, 8},

    // nokia
    {28, 190,
    E5, 8, D5, 8, FS4, 4, GS4, 4, 
    CS5, 8, B4, 8, D4, 4, E4, 4, 
    B4, 8, A4, 8, CS4, 4, E4, 4,
    A4, 2}

};

void playMusic() {
    
  int TimeToEnd = 0;
  int NoteDuration = 0;
  
  BPM = note_frequencies[CURRENT_LINE][1]; 
  
  int CompleteNote = (60000 * 4) / BPM;

  for (int i = 2; i < note_frequencies[CURRENT_LINE][0]; i += 2) {
    
    if (isPaused) {
      i -= 2;
      noTone(BUZZER);   
      continue;
    }
    if (!isPlaying) {
      noTone(BUZZER);
      break;
    }
    
    TimeToEnd = note_frequencies[CURRENT_LINE][i+1];

    NoteDuration = (TimeToEnd > 0) ? (CompleteNote / TimeToEnd) : (CompleteNote / abs(TimeToEnd) * 1.5);
    
    tone(BUZZER, note_frequencies[CURRENT_LINE][i], NoteDuration * 0.9);
    delay(NoteDuration);
    
    noTone(BUZZER);
    
  }
  delay(1500);
}


void loop()
{
    if (isPlaying)
    {
        playMusic();
    }
    else
    {
        if (digitalRead(UP))
        {
            goUp();
        }

        else if (digitalRead(DOWN))
        {
            goDown();
        }
    }
}