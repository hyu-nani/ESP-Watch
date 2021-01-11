
void LCD_needle(u16 x,u16 y, u16 w,u16 thin, int value ,u16 color)
{
	int separate = 60;
	int S = w*sin(2*PI*value/separate);
	int C = w*cos(2*PI*value/separate);
	LCD_Line(x,y,x+S,y-C,thin,color);
}
void LCD_dot(u16 x,u16 y, u16 r,u16 thin ,u16 color)
{
	int separate = 60;
	for(int a=0;a<separate;a++){
		int S = r*sin(2*PI*a/separate);
		int C = r*cos(2*PI*a/separate);
		LCD_Pixel(x+S,y-C,thin,color);
	}
}
void LCD_dot_needle(u16 x,u16 y, u16 w,u16 thin, int value ,u16 color)
{
	int separate = 60;
	int S = w*sin(2*PI*value/separate);
	int C = w*cos(2*PI*value/separate);
	LCD_Line(x,y,x+S,y-C,thin,color);
	if(value >= (separate*0/4)&&value < (separate*1/4))
		LCD_Pixel(x+S+thin,y-C-thin,thin,color);
	if(value >= (separate*1/4)&&value < (separate*2/4))
		LCD_Pixel(x+S+thin,y-C+thin,thin,color);
	if(value >= (separate*2/4)&&value < (separate*3/4))
		LCD_Pixel(x+S-thin,y-C+thin,thin,color);
	if(value >= (separate*3/4)&&value < (separate*4/4))
		LCD_Pixel(x+S-thin,y-C-thin,thin,color);
}


void LCD_print_background(u16 x,u16 y, const char c[],u16 color ,u16 bgcolor ,uint8_t size)
{
  
	int i = 0;
	while(c[i] != '\0'){
		if (c[i] == '\n') {
			y += size*8;
			x  = 0;
		} 
		else {
			LCD_Char_bg(x, y, c[i], color, bgcolor, size);
			x += 6*size;
			i++;
			if (x > (LCD_W - size*6)) {
				y += size*8;
				x = 0;
			}
		}
		
	}
}
void LCD_print(u16 x,u16 y, const char c[],u16 color ,uint8_t size)
{
  
  int i = 0;
  while(c[i] != '\0'){
    if (c[i] == '\n') {
      y += size*8;
      x  = 0;
    } 
    else {
      LCD_Char(x, y, c[i], color, size);
      x += 6*size;
      i++;
      if (x > (LCD_W - size*6)) {
        y += size*8;
        x = 0;
      }
    }
    
  }
}
void LCD_print_background(u16 x,u16 y, int c,u16 color ,u16 bgcolor ,uint8_t size)
{
		char A[10];
		int i =0;
		sprintf(A, "%d", c);
		while(A[i] != '\0'){
			if (A[i] == '\n') {
				y += size*8;
				x  = 0;
			}
			else {
				LCD_Char_bg(x, y, A[i], color, bgcolor, size);
				x += 6*size;
				if (x > (LCD_W - size*6)) {
					y += size*8;
					x = 0;
				}
			}
		i++;
		}
		
}
void LCD_print_(u16 x,u16 y, int c,u16 color ,uint8_t size)
{
	char A[10];
	int i =0;
	sprintf(A, "%d", c);
	while(A[i] != '\0'){
		if (A[i] == '\n') {
			y += size*8;
			x  = 0;
		}
		else {
			LCD_Char(x, y, A[i], color, size);
			x += 6*size;
			if (x > (LCD_W - size*6)) {
				y += size*8;
				x = 0;
			}
		}
		i++;
	}
	
}


int lcd_h=0;
int lcd_m=0;
int lcd_s=0;
int lcd_d=0;
void clockmode(int timer)
{
	//timer : 0 - 84400 
	LCD_Circle(120,120,117,3,LGRAYBLUE);
	LCD_dot(120,120,116,3,LGRAYBLUE);
	LCD_dot(120,120,115,3,LGRAYBLUE);
	LCD_needle(120,120,100,1,lcd_s,BLACK);
	LCD_needle(120,120,80,2,lcd_m,BLACK);
	LCD_needle(120,120,60,3,lcd_h*5,BLACK);
	lcd_h = int((timer%86400)/3600)-3;
	lcd_m = int((timer%3600)/60);
	lcd_s = int(timer%3600);
	lcd_d = int((timer/86400)%7);
	LCD_needle(120,120,100,1,lcd_s,CYAN);
	LCD_needle(120,120,80,2,lcd_m,RED);
	LCD_needle(120,120,60,3,lcd_h*5,MAGENTA);
  LCD_fill_Circle(120,120,5,CYAN);
	LCD_print(90,80,"Clock",WHITE,2);
	if(lcd_d == 2)
		LCD_print_background(100,180,"SAT",CYAN,BLACK,2);
	else if(lcd_d == 3)
		LCD_print_background(100,180,"SUN",BLUE,BLACK,2);
	else if(lcd_d == 4)
		LCD_print_background(100,180,"MON",RED,BLACK,2);
	else if(lcd_d == 5)
		LCD_print_background(100,180,"TUS",RED,BLACK,2);
	else if(lcd_d == 6)
		LCD_print_background(100,180,"WED",YELLOW,BLACK,2);
	else if(lcd_d == 7)
		LCD_print_background(100,180,"THU",YELLOW,BLACK,2);
	else if(lcd_d == 1)
		LCD_print_background(100,180,"FRI",RED,BLACK,2);
}
void LCD_smooth_on(int val)
{
	for(;lcd_light<1024;lcd_light++){
		analogWrite(TFT_LIGHT,lcd_light);
		delay(val);
	}
}
void LCD_smooth_off(int val)
{
	for(;lcd_light>0;lcd_light--){
		analogWrite(TFT_LIGHT,lcd_light);
		delay(val);
	}
}
