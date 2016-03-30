
/*

^                    
|    1 2 3 4 5 6 7 8 
| 16 x x x x x x x x 
| 15 x x x x x x x x 
| 14 x x x x x x x x 
| 13 x x x x x x x x 
| 12 x x x x x x x x 
| 11 x x x x x x x x 
| 10 x x x x x x x x 
| 09 x x x x x x x x 

| 08 x x x x x x x x 
| 07 x x x x x x x x 
| 06 x x x x x x x x 
| 05 x x x x x x x x 
| 04 x x x x x x x x 
| 03 x x x x x x x x 
| 02 x x x x x x x x 
Y 01 x x x x x x x x 
* X------------------>

*/
//scratch paper
void GUI_SetDrawingPaper(uint8_t *paper);

void GUI_Clear      (void);
void GUI_ClearRect  (int8_t x0, int8_t y0, int8_t x1, int8_t y1);
void GUI_DrawPoint  (int8_t x, int8_t y);
bool GUI_ReadPoint  (int8_t x, int8_t y);
void GUI_DrawHLine  (int8_t y0, int8_t x0, int8_t x1);
void GUI_DrawLine   (int8_t x0, int8_t y0, int8_t x1, int8_t y1);
void GUI_DrawRect   (int8_t x0, int8_t y0, int8_t x1, int8_t y1);

void GUI_refresh    (void);
//void GUI_DrawLineRel      (int dx, int dy);
