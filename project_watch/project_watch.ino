/*********************************
 ESP-12F
 *********************************/
#define TFT_DC	D1
#define TFT_RST	D2
#define TFT_CS	D6
#define TFT_LIGHT D8

#define LCD_W 240
#define LCD_H 240
 
#define SW_L D0
#define SW_S D3
#define SW_R D4

#include <SPI.h>
#include "image.h"
#include "GC9A01A.h"
#include "LCD_basic.h"
#include "LCD_action.h"
#include "WIFI.h"
#include <math.h>

int page = 0;
#define max_page 2
#define min_page 0
void sw_check();

void setup() {
	pinMode(SW_L,INPUT);
	pinMode(SW_S,INPUT);
	pinMode(SW_R,INPUT);
	Serial.begin(9600);
	wifi_init();
	LCD_portset();
	SPI.begin();
	mySPISettings = SPISettings(80000000, MSBFIRST, SPI_MODE0); //ESP max speed 80MHz
	LCD_Init();
	LCD_image(0,0,LCD_W,LCD_H,rogo);
	LCD_smooth_on(1);
	delay(500);
	LCD_smooth_off(1);
	LCD_Fill(BLACK);
	now = time(nullptr);
	configTime(GMT_SEC,DST_SEC,"kr.pool.ntp.org");
}
void loop() {
	while(page == 0){ //intro
		LCD_Fill(BLACK);
		LCD_print(90,100,"HELLO",WHITE,2);
		LCD_print(63,125,"Please press button",YELLOW,1);
		LCD_print(54,140," NEXT // HOME // PREV ",WHITE,1);
		LCD_smooth_on(1);
		while (1)
		{
			sw_check();
			LCD_print(90,100,"HELLO",WHITE,2);
			LCD_print(63,125,"Please press button",YELLOW,1);
			LCD_print(54,140," NEXT // HOME // PREV ",WHITE,1);
			if(page != 0){
				LCD_smooth_off(1);
				break;
			}
		}
	}
	while(page == 1){ //clock
		LCD_Fill(BLACK);
		clockmode(now);
		LCD_smooth_on(1);
		configTime(GMT_SEC,DST_SEC,"pool.ntp.org");
		while(1){
			now_ms = millis();
			if(now_ms-prev_ms>1000){
				clockmode(now);
				now = time(nullptr);
				prev_ms = now_ms;
			}
			sw_check();
			if(page != 1){
				LCD_smooth_off(1);
				break;
			}
		}
	}
	while (page == 2) //display image
	{
		LCD_Fill(BLACK);
		LCD_smooth_on(1);
		while(1){
			LCD_image(0,0,240,240,image1);
			delay(100);
			sw_check();
			LCD_image(0,0,240,240,image2);
			delay(100);
			sw_check();
			LCD_image(0,0,240,240,image3);
			delay(100);
			sw_check();
			LCD_image(0,0,240,240,image4);
			delay(100);
			sw_check();
			if(page != 2){
				LCD_smooth_off(1);
				break;
			}
		}
	}
}

void sw_check(){
	if(digitalRead(SW_L)>0){
		page++;
		Serial.println("+");
		while(digitalRead(SW_L)>0){delay(100);}
	}
	else if(digitalRead(SW_S)==0){
		page=0;
		Serial.println("0");
		while(digitalRead(SW_S)==0){delay(100);}
	}
	else if(digitalRead(SW_R)==0){
		page--;
		Serial.println("-");
		while(digitalRead(SW_R)==0){delay(100);}
	}
	if(page>max_page || page<min_page){page = 0;}
	delay(10);
}
