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

const uint8_t bitman_OR[9] {0, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
const uint8_t bitman_AND[9]{0, 0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};


/** Fills the display / the active window with the background color.
 *  @param 
 */
void GUI_Clear(void)
{
    uint8_t i;
    for(i=0; i<16; i++)
        _buff[i] = 0;
}


/** GUI_ClearPoint.
 *  @param x
 *  @param y
 */
void GUI_ClearPoint(int x, int y)
{
    _buff[y-1] &= bitman_AND[x];
}


/** Fills a rectangular area with the background color.
 *  @param x0 Upper left X-position.
 *  @param y0 Upper left Y-position.
 *  @param x1 Lower right X-position.
 *  @param y1 Lower right Y-position.
 */
void GUI_ClearRect(int x0, int y0, int x1, int y1)
{
    uint8_t i;
    uint8_t clearMask = 0;
    
    for(i=x0; i<=x1; i++)
        clearMask |= bitman_OR[i];
        
    clearMask = ~clearMask;
    
    for(i=y0; i<=y1; i++)
        _buff[i-1] &= clearMask;
}


/** Draws a point.
 *  @param x X-position of point.
 *  @param y Y-position of point.
 */
void GUI_DrawPoint(int x, int y)
{
    _buff[y-1] |= bitman_OR[x];
}


/** Draws a rectangle at a specified position in the current window.
 *  @param x0 Upper left X-position.
 *  @param y0 Upper left Y-position.
 *  @param x1 Lower right X-position.
 *  @param y1 Lower right Y-position.
 */
void GUI_DrawRect(int x0, int y0, int x1, int y1)
{
    uint8_t i;
    uint8_t drawMask = 0;
    
    for(i=x0; i<=x1; i++)
        drawMask |= bitman_OR[i];
        
    
    for(i=y0; i<=y1; i++)
        _buff[i-1] |= drawMask;
}