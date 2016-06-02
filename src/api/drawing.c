/*

^                    
Y   0 1 2 3 4 5 6 7 
15| x x x x x x x x 
14| x x x x x x x x 
13| x x x x x x x x 
12| x x x x x x x x 
11| x x x x x x x x 
10| x x x x x x x x 
09| x x x x x x x x 
08| x x x x x x x x 

07| x x x x x x x x 
06| x x x x x x x x 
05| x x x x x x x x 
04| x x x x x x x x 
03| x x x x x x x x 
02| x x x x x x x x 
01| x x x x x x x x 
00| x x x x x x x x 
 *  ---------------->

*/


const uint8_t  bitMask[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
const uint8_t nbitMask[8] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};

uint8_t mainPaper[8];
uint8_t scratchPaper[8];
uint8_t *currentPaper;
uint8_t color;


//-----------------------------------------------------

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

//-------------------------------------------------------

inline void GUI_SetColor(int8_t col)
{
    color = col;
}

/** Draws a point.
 *  @param x: X-position of point.
 *  @param y: Y-position of point.
 */
void GUI_DrawPixel(int8_t x, int8_t y)
{
    if(x<8 || x>-1 || y<16 || y>-1)
    {
//        if(color == 0)
//            currentPaper[y] &= nbitMask[x];
//        else
            currentPaper[y] |= bitMask[x];
    }
}

/** Read a point.
 *  @param x: X-position of point.
 *  @param y: Y-position of point.
 *  @return a point value.
 */
uint8_t GUI_ReadPixel(int8_t x, int8_t y)
{
    if((currentPaper[y] & bitMask[x]) == 0)
        return 0;
    else
        return 1;
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
        currentPaper[i] |= drawMask;
}

/** Fills a rectangular area with the background color.
 *  @param x0: Upper left X-position.
 *  @param y0: Upper left Y-position.
 *  @param x1: Lower right X-position.
 *  @param y1: Lower right Y-position.
 */
void GUI_FillRect(int8_t x0, int8_t y0, int8_t x1, int8_t y1)
{
    
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


void GUI_DrawBitmap(int8_t x, int8_t y, const uint8_t *bitmap, int8_t w, int8_t h)
{
    int8_t i, j, color;
    
    for(j=0; j<h; j++) 
    {
        for(i=0; i<w; i++) 
        {
            if(bitmap[j] & bitMask[i])
                GUI_SetColor(BLACK);
            else
                GUI_SetColor(GREEN);
                
            if((x+i > 0) && (y+i > 0))    
                GUI_DrawPixel(x+i, y+i);
        }
    }
}



// void GUI_DrawBitmap(int8_t x, int8_t y, const uint8_t *bitmap)
// {
//     uint8_t i;
//     uint8_t mapsize = strlen(bitmap);
    
//     if((x > 0) && (x < 16))
//     {
//         for(i=y; i<(y+mapsize); i++)
//         {
//             currentPaper[i] |= (bitmap[i] >> x);
//         }
//     }
//     else
//     {
        
//     }
    
// }