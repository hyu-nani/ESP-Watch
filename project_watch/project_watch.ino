
/*********************************
 ESP-32
 *********************************/
#define TFT_DC	17
#define TFT_RST	5
#define TFT_CS	18
#define TFT_LIGHT 19

#define LCD_W 240
#define LCD_H 240
 
#define SW_L 23
#define SW_S 22
#define SW_R 21

#include <SPI.h>
#include <EEPROM.h>
#include "image.h"
#include "GC9A01A.h"
#include "LCD_basic.h"
#include "LCD_action.h"
//#include "WIFI.h"
#include <math.h>

int page = 0;
char sw_check();

#include "mode.h"

void setup() {
	EEPROM.begin(512);
	lcd_light = EEPROM.read(1);
	if(lcd_light < 1||lcd_light>1000){lcd_light = 1000;}
	pinMode(SW_L,INPUT);
	pinMode(SW_S,INPUT);
	pinMode(SW_R,INPUT);
	Serial.begin(9600);
	//wifi_init();
	LCD_portset();
	SPI.begin();
	mySPISettings = SPISettings(80000000, MSBFIRST, SPI_MODE0); //ESP max speed 80MHz
	LCD_Init();
	LCD_image(0,0,LCD_W,LCD_H,rogo);
	LCD_smooth_on(2);
	delay(500);
	LCD_smooth_off(2);
	LCD_Fill(BLACK);
	//now = time(nullptr);
	//configTime(GMT_SEC,DST_SEC,"kr.pool.ntp.org");
}
void loop() {
	while(page == 0){ //intro
		LCD_Fill(BLACK);
		initialize();
		LCD_smooth_on(1);
		while (1)
		{
			page_set();
			initialize();
			if(page != 0){
				LCD_smooth_off(1);
				break;
			}
		}
	}
	while(page == 1){ //clock
		/*
		LCD_Fill(BG_Clock_Color);
		clock(now);
		LCD_smooth_on(1);
		//configTime(GMT_SEC,DST_SEC,"pool.ntp.org");
		while(1){
			now_ms = millis();
			if(now_ms-prev_ms>1000){
				clock(now);
				now = time(nullptr);
				prev_ms = now_ms;
			}
			page_set();
			if(page != 1){
				LCD_smooth_off(1);
				break;
			}
		}
	}
	while (page == 2) //display image
	{
		LCD_Fill(BG_Set_Color);
		LCD_smooth_on(1);
		while(1){
			setting();
			if(page != 2){
				LCD_smooth_off(1);
				break;
			}
		}*/
	}
}
