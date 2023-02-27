#include <Adafruit_NeoPixel.h>

// Definitions
#define LED_PIN_RED 4
#define LED_PIN_BLUE 5
#define LED_COUNT 8
#define BRIGHTNESS 20
#define BUTTON_PIN 4
#define RED_IR 15
#define BLUE_IR 16

// Button INT
int LST_btn = LOW;
int CRS_btn;
// IR Blue INT
int Blue_VAL = 0;
int Blue_LST = 0;
// IR Red INT
int Red_VAL = 0;
int Red_LST = 0;

Adafruit_NeoPixel RED_led(LED_COUNT, LED_PIN_RED, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel BLUE_led(LED_COUNT, LED_PIN_BLUE, NEO_GRBW + NEO_KHZ800);

void setup() {
	RED_led.begin();
	RED_led.show();
	RED_led.setBrightness(BRIGHTNESS);

	BLUE_led.begin();
	BLUE_led.show();
	BLUE_led.setBrightness(BRIGHTNESS);

	// IR Breaker PINs
	pinMode(RED_IR, INPUT_PULLUP);
	pinMode(BLUE_IR, INPUT_PULLUP);

	// Button PIN
	pinMode(BUTTON_PIN, INPUT_PULLUP);

	// BAUD Rate
	Serial.begin(9600);
}

void loop() {
	ledconfig(RED_IR, Red_VAL, Red_LST, RED_led, 255, 0, 0, 200);
	ledconfig(BLUE_IR, Blue_VAL, Blue_LST, BLUE_led, 0, 0, 255, 200);
}

void ledconfig(int IRval, int& CLRval, int& LSTval, Adafruit_NeoPixel& led, uint8_t red, uint8_t green, uint8_t blue, int wait) {
	if (digitalRead(IRval) == LOW) {
		CLRval++;
	}
	if (LSTval != CLRval) {
		if (CLRval <= 8) {
			if (blue > 0) {
				Serial.print("BLUE count = ");
			} else if (red > 0) {
				Serial.print("RED count = ");
			}
			Serial.println(CLRval, DEC);
			for (int i = 0; i < LED_COUNT; i++) {
				led.setPixelColor(CLRval - 1, led.Color(red, green, blue));
				led.show();
				delay(wait);
			}
		} else {
			if (blue > 0) {
				Serial.println("BLUE reset");
			} else if (red > 0) {
				Serial.println("RED reset");
			}
			CLRval = 0;
			led.clear();
			led.show();
		}
		LSTval = CLRval;
	}
}
