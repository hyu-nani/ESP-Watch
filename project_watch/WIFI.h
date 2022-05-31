//#include <ESP8266WiFi.h>
#include "time.h"

#define GMT		  8
#define GMT_SEC	(GMT*3600)
#define DST_SEC	0 //summer time = 3600

const char* ssid	=	"613";
const char* password =	"happy613";

time_t now;

uint32_t prev_ms,now_ms;
int hour = 0;
int minute = 0;
int dy = 0;
int prevhr = 0;

void wifi_init()
{	
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid,password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	}
	configTime(GMT_SEC,DST_SEC,"kr.pool.ntp.org");
	prev_ms = millis();
}
