
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
void LCD_print(u16 x,u16 y, int c,u16 color ,uint8_t size)
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

int output_light=0;
void LCD_smooth_on(int val)
{
	delay(100);
	
	for(;output_light<lcd_light;output_light+=5){
		//analogWrite(TFT_LIGHT,output_light);
		delay(val);
	}
}
void LCD_smooth_off(int val)
{
	for(;output_light>0;output_light-=5){
		//analogWrite(TFT_LIGHT,output_light);
		delay(val);
	}
	delay(100);
}
