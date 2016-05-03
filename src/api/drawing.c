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


const uint8_t  bitMask[9] = {0, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
const uint8_t nbitMask[9] = {0, 0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};

uint8_t mainPaper[8];
uint8_t scratchPaper[8];
uint8_t *currentPaper;


/** Set the targe point drawing paper.
 *  @param *paper: The targer draw paper.
 */
void GUI_SetDrawingPaper(uint8_t *paper)
{
    *currentPaper = *paper;
}

/** Merge the exPaper drawing to the current paper.
 *  @param *exPaper: To merge paper.
 */
void GUI_MergePaper(uint8_t *exPaper)
{
    uint8_t i;
    
    for(i=0; i<16; i++)
        currentPaper[i] |= exPaper[i];
}

/** Merge the exPaper drawing to the current paper.
 *  @param *exPaper: To merge paper.
 */
void GUI_MergePaperRectMask(uint8_t *exPaper, int8_t x0, int8_t y0, int8_t x1, int8_t y1)
{
    uint8_t i;
    
    for(i=0; i<16; i++)
        currentPaper[i] |= exPaper[i];
}

/** Fills the display / the active window with the background color.
 *  @param 
 */
void GUI_Clear(void)
{
    uint8_t i;
    for(i=0; i<16; i++)
        currentPaper[i] = 0;
}

/** GUI_ClearPoint.
 *  @param x:
 *  @param y:
 */
void GUI_ClearPoint(int8_t x, int8_t y)
{
    currentPaper[y-1] &= nbitMask[x];
}

/** Fills a rectangular area with the background color.
 *  @param x0: Upper left X-position.
 *  @param y0: Upper left Y-position.
 *  @param x1: Lower right X-position.
 *  @param y1: Lower right Y-position.
 */
void GUI_ClearRect(int8_t x0, int8_t y0, int8_t x1, int8_t y1)
{
    int8_t i;
    uint8_t clearMask = 0;
    
    for(i=x0; i<=x1; i++)
        clearMask |= bitMask[i];
        
    clearMask = ~clearMask;
    
    for(i=y0; i<=y1; i++)
        currentPaper[i-1] &= clearMask;
}

/** Draws a point.
 *  @param x: X-position of point.
 *  @param y: Y-position of point.
 */
void GUI_DrawPoint(int8_t x, int8_t y)
{
    currentPaper[y-1] |= bitMask[x];
}

/** Read a point.
 *  @param x: X-position of point.
 *  @param y: Y-position of point.
 *  @return a point value.
 */
bool GUI_ReadPoint(int8_t x, int8_t y)
{
    if((currentPaper[y-1] & bitMask[x]) == 0)
        return 0;
    else
        return 1;
}

/** Draws a rectangle at a specified position in the current window.
 *  @param x0: Upper left X-position.
 *  @param y0: Upper left Y-position.
 *  @param x1: Lower right X-position.
 *  @param y1: Lower right Y-position.
 */
void GUI_DrawRect(int8_t x0, int8_t y0, int8_t x1, int8_t y1)
{
    uint8_t i;
    uint8_t drawMask = 0;
    
    for(i=x0; i<=x1; i++)
        drawMask |= bitMask[i];
        
    
    for(i=y0; i<=y1; i++)
        currentPaper[i-1] |= drawMask;
}

/** Draws a line from a specified starting point to a specified endpoint in the current window (absolute coordinates).
 *  @param x0: X-starting position.
 *  @param y0: Y-starting position.
 *  @param x1: X-end position.
 *  @param y1: Y-end position.
 */
void GUI_DrawLine(int8_t x0, int8_t y0, int8_t x1, int8_t y1)
{
    int8_t i, k, a;
    k = (y0 - y1) / (x0 - x1);
    a = y0 - k*x0;
    
    for(i=x0; i<=x1; i++)
    {
        GUI_DrawPoint(i, (k*i+a));
    }
}

/** GUI_DrawingMoving.
 *  @param mvX: X-starting position.
 *  @param mvY: Y-end position.
 */
void GUI_DrawingMoving(int8_t mvX, int8_t mvY)
{
    int8_t i;
    
    //lengthways moving
    if(mvY > 0)
    {
        for(i=15; i>=0; i--)
        {
            if(i-mv > 0)
                currentPaper[i] = currentPaper[i-mvY];
            else
                currentPaper[i] = 0;
        }
        
    }
    else if(mvY < 0)
    {
        for(i=0; i>=15; i++)
        {
            if(i-mv < 15)
                currentPaper[i] = currentPaper[i-mvY];
            else
                currentPaper[i] = 0;
        }
    }
    
    //crosswise moving
    if(mvX > 0)
    {
        for(i=0; i<=15; i++)
            currentPaper[i] >>= mvX;
    }
    else if(mvX < 0)
    {
        for(i=0; i<=15; i++)
            currentPaper[i] <<= (-mvX);
    }
    
}

void GUI_DrawBitmap(int8_t x, int8_t y, const uint8_t *bitmap)
{
    uint8_t i;
    uint8_t mapsize = strlen(bitmap);
    
    if((x > 0) && (x < 16))
    {
        for(i=y; i<(y+mapsize); i++)
        {
            currentPaper[i] |= (bitmap[i] >> x);
        }
    }
    else
    {
        
    }
    
}
