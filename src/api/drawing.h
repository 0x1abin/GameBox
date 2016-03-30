
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

void GUI_Clear            (void);
void GUI_ClearRect        (int x0, int y0, int x1, int y1);
void GUI_DrawPoint        (int x, int y);
void GUI_DrawHLine        (int y0, int x0, int x1);
void GUI_DrawLine         (int x0, int y0, int x1, int y1);
void GUI_DrawRect         (int x0, int y0, int x1, int y1);
//void GUI_DrawLineRel      (int dx, int dy);
//void GUI_DrawLineTo       (int x, int y);