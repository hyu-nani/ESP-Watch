char sw_check(){
  char val='n';
  if(digitalRead(SW_L)==0){
    val='l';
    while(digitalRead(SW_L)==0){delay(100);}
  }
  else if(digitalRead(SW_S)==0){
    val='s';
    while(digitalRead(SW_S)==0){delay(100);}
  }
  else if(digitalRead(SW_R)==0){
    val='r';
    while(digitalRead(SW_R)==0){delay(100);}
  }
  delay(10);
  return val;
}
void page_set(){
	char val = sw_check();
	if(val=='l'){page++;}
	else if(val=='r'){page--;}
}
void initialize()
{
	LCD_print(90,100,"HELLO",WHITE,2);
	LCD_print(63,125,"Please press button",YELLOW,1);
	LCD_print(54,140," NEXT // HOME // PREV ",WHITE,1);
}


int lcd_h=0;
int lcd_m=0;
int lcd_s=0;
int lcd_d=0;
uint16_t BG_Clock_Color = BLACK;
void clock(int timer)
{
	//timer : 0 - 84400
	//LCD_Circle(120,120,117,3,LGRAYBLUE);
	LCD_dot(120,120,116,3,LGRAYBLUE);
	LCD_dot(120,120,115,3,LGRAYBLUE);
	LCD_needle(120,120,105,1,lcd_s,BG_Clock_Color);
	LCD_needle(120,120,80,2,lcd_m,BG_Clock_Color);
	LCD_needle(120,120,60,3,lcd_h*5,BG_Clock_Color);
	lcd_h = int((timer%86400)/3600)-3;
	lcd_m = int((timer%3600)/60);
	lcd_s = int(timer%3600);
	lcd_d = int((timer/86400)%7);
	LCD_needle(120,120,105,1,lcd_s,CYAN);
	LCD_needle(120,120,80,2,lcd_m,GREEN);
	LCD_needle(120,120,60,3,lcd_h*5,MAGENTA);
	LCD_fill_Circle(120,120,5,CYAN);
	LCD_print(110,10,"12",WHITE,2);
	LCD_print(220,115,"3",WHITE,2);
	LCD_print(116,216,"6",WHITE,2);
	LCD_print(12,115,"9",WHITE,2);
	int x=104,y=90;
	if(lcd_d == 2)
	LCD_print_background(x,y,"SAT",CYAN,BG_Clock_Color,2);
	else if(lcd_d == 3)
	LCD_print_background(x,y,"SUN",BLUE,BG_Clock_Color,2);
	else if(lcd_d == 4)
	LCD_print_background(x,y,"MON",RED,BG_Clock_Color,2);
	else if(lcd_d == 5)
	LCD_print_background(x,y,"TUE",RED,BG_Clock_Color,2);
	else if(lcd_d == 6)
	LCD_print_background(x,y,"WED",YELLOW,BG_Clock_Color,2);
	else if(lcd_d == 7)
	LCD_print_background(x,y,"THU",YELLOW,BG_Clock_Color,2);
	else if(lcd_d == 1)
	LCD_print_background(x,y,"FRI",RED,BG_Clock_Color,2);	
}



uint16_t BG_Set_Color = BLACK;
int mode_x = 0;
int cursor_y = 80;
void setting()
{	
	
	while(1){
		
		char i = sw_check();
		if (i == 'n'){}
		else if(i=='l'){
			LCD_print(50,cursor_y,"->",BG_Set_Color,1);
			cursor_y += 20;
			LCD_print_background(50,cursor_y,"->",YELLOW,BG_Set_Color,1);	
		}
		else if(i=='r'){
			LCD_print(50,cursor_y,"->",BG_Set_Color,1);
			cursor_y -= 20;
			LCD_print_background(50,cursor_y,"->",YELLOW,BG_Set_Color,1);	
		}
		else if(i=='s'){
			if (cursor_y == 200)
			{
				page--;
				break;
			}
			else{mode_x ++;}
		}
		if (mode_x==0)
		{
			LCD_print_background(50,cursor_y,"->",YELLOW,BG_Set_Color,1);
			LCD_print(60,20,"Setting",WHITE,3);
			LCD_print(80,80,"Brightness",WHITE,1);
			LCD_print(80,100,"set1",WHITE,1);
			LCD_print(80,120,"set2",WHITE,1);
			LCD_print(80,200,"Back",WHITE,1);
		}
		else if(mode_x==1){
			LCD_Fill(BG_Set_Color);
			if (cursor_y == 80){
				LCD_print(70,40,"Brightness",WHITE,2);
				while(1){
					LCD_fill_Rect(10,110,220,5,YELLOW);
					LCD_fill_Rect(11,111,218,3,BG_Set_Color);
					int bar = map(lcd_light,0,1000,0,210);
					LCD_fill_Rect(10+bar,111,5,3,WHITE);
					LCD_fill_Rect(70,70,30,8,BG_Set_Color);
					LCD_print(70,70,lcd_light,WHITE,1);
					delay(50);
					if(digitalRead(SW_L)==0){
						if(lcd_light<980)
							lcd_light+=20;
						//analogWrite(TFT_LIGHT,lcd_light);
					}
					else if(digitalRead(SW_R)==0){
						if(lcd_light>20)
							lcd_light-=20;
						//analogWrite(TFT_LIGHT,lcd_light);
					}
					else if(digitalRead(SW_S)==0){
						mode_x--;
						delay(1000);
						EEPROM.write(1,lcd_light);
						EEPROM.commit(); //store
						LCD_Fill(BG_Set_Color);
						break;
					}
				}
			}
			if (cursor_y == 100){
				while(1){
					
				}
			}
			if (cursor_y == 120){
				while(1){
					
				}
			}
				
		}
		else if(mode_x==2){
			
		}
	}
}
