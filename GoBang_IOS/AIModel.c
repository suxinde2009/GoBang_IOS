//
//  AIModel.c
//  GoBang_IOS
//
//  Created by su xinde on 13-3-8.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//


#include "AIModel.h"

void evaluate(int shapeChess[Size][Size][Size], int shapeSpace[Size][Size][Size], int allChess[Size][Size])
{
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
        {
            if(allChess[i][j] == 0)
            {
                if(isTo5L(i, j, shapeChess, shapeSpace))//是否实现连五1
                {
                    shapeChess[i][j][8] = 2000;
                    //System.out.println("x =" + i + "y =" + j);
                }
                else if(isTo4L(i, j, shapeChess, shapeSpace))//是否实现活四2
                {
                    shapeChess[i][j][8] = 1800;
                    //System.out.println(2);
                }
                else if(isToD4D(i, j, shapeChess, shapeSpace))//双冲四3
                {
                    shapeChess[i][j][8] = 1800;
                    //System.out.println(3);
                }
                //else if(isToDJamp4AND(i, j, shapeChess, shapeSpace))
                //    				{
                //    					shapeChess[i][j][8] = 1500;
                //    				}
                else if(isTo4D3LANDD3L(i, j, shapeChess, shapeSpace))//是否实现四活三和双活三4
                {
                    shapeChess[i][j][8] = 1200;
                    //System.out.println(4);
                }
                else if(isTo4DAnd3D(i, j, shapeChess, shapeSpace))	//实现冲四和冲三6
                {
                    shapeChess[i][j][8] = 1000;
                    //System.out.println(7);
                }
                else if(isTo4D(i, j, shapeChess, shapeSpace))//实现单四
                {
                    shapeChess[i][j][8] = 800 + shapeChess[i][j][0] + shapeChess[i][j][1]+shapeChess[i][j][2]
                    + shapeChess[i][j][3]+shapeChess[i][j][4]
                    + shapeChess[i][j][5]+shapeChess[i][j][6]+shapeChess[i][j][7];;
                }
                else if(isTo3L2L(i, j, shapeChess, shapeSpace))//活三和活二
                {
                    shapeChess[i][j][8] = 700 +shapeChess[i][j][1]+shapeChess[i][j][2]
                    +shapeChess[i][j][3]+shapeChess[i][j][4]
                    +shapeChess[i][j][5]+shapeChess[i][j][6]+shapeChess[i][j][7];
                    //System.out.println(5);
                }
                else if(isTo3L(i, j, shapeChess, shapeSpace))//实现活三7
                {
                    shapeChess[i][j][8] = 600 +shapeChess[i][j][1]+shapeChess[i][j][2]
                    +shapeChess[i][j][3]+shapeChess[i][j][4]
                    +shapeChess[i][j][5]+shapeChess[i][j][6]+shapeChess[i][j][7];
                    //System.out.println(6);
                }
                
                
                else if(isToD3D(i, j, shapeChess, shapeSpace))//实现双冲三8
                {
                    shapeChess[i][j][8] = 500 +shapeChess[i][j][1]+shapeChess[i][j][2]
                    +shapeChess[i][j][3]+shapeChess[i][j][4]
                    +shapeChess[i][j][5]+shapeChess[i][j][6]+shapeChess[i][j][7];
                    //System.out.println(8);
                }
                
                
                else if(isToD2L(i, j, shapeChess, shapeSpace))//实现双活二
                {
                    shapeChess[i][j][8] = 300 +shapeChess[i][j][1]+shapeChess[i][j][2]
                    +shapeChess[i][j][3]+shapeChess[i][j][4]
                    +shapeChess[i][j][5]+shapeChess[i][j][6]+shapeChess[i][j][7];
                    //System.out.println(9);
                }
                else if(isTo3D(i, j, shapeChess,shapeSpace))//实现冲三9
                {
                    shapeChess[i][j][8] = 200+shapeChess[i][j][1]+shapeChess[i][j][2]
                    +shapeChess[i][j][3]+shapeChess[i][j][4]
                    +shapeChess[i][j][5]+shapeChess[i][j][6]+shapeChess[i][j][7];
                    //System.out.println(9);
                }
                else
                {
                    for(int d = 0; d < 8; d++)
                    {
                        shapeChess[i][j][8] += shapeChess[i][j][d];
                        
                    }
                }
            }
        }
    max=0;
    for(int x=0;x<15;x++)
        for(int y=0;y<15;y++)
            if(max < shapeChess[x][y][8])
            {
                max = shapeChess[x][y][8];
                max_x = x; max_y = y;
            }
    //System.out.printf("shapeChess[%d][%d]=%d,%n", max_x, max_y, shapeChess[max_x][max_y][8]);
}

//单四
BOOL isTo4D(int x,
            int y,
            int shapeChess[Size][Size][Size],
            int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    
    for(int d = 0; d < 2; d++)
    {
        int nCount = shapeChess[x][y][d] + shapeChess[x][y][d+4] + 1;
        int nFree1 = shapeSpace[x][y][d] - shapeChess[x][y][d];
        int nFree2 = shapeSpace[x][y][d+4] - shapeChess[x][y][d+4];
        if(nCount >= 4 &&(nFree1>=1 || nFree2>=1))
        {
            flag = TRUE;
            //System.out.println(4);
        }
    }
    return flag;
}


//活三活二
BOOL isTo3L2L(int x,
              int y,
              int shapeChess[Size][Size][Size],
              int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    int count = 0;
    BOOL isDoubleT = TRUE;
    for(int d = 0; d < 2; d++)
    {
        int nCount = shapeChess[x][y][d] + shapeChess[x][y][d+4] + 1;
        int nFree1 = shapeSpace[x][y][d] - shapeChess[x][y][d];
        int nFree2 = shapeSpace[x][y][d+4] - shapeChess[x][y][d+4];
        if(nCount >= 3 &&(nFree1>=1 && nFree2>=1) && ((nCount+nFree1+nFree2)>=5))
        {
            count++; continue;
        }
        if((isDoubleT == TRUE) && nCount >= 2 && (nFree1>=1 && nFree2>=1)&& ((nCount+nFree1+nFree2)>=5))
        {
            count++;
            isDoubleT = FALSE;
            continue;
        }
        
    }
    if(count >= 2)
    {
        flag = TRUE;
        
    }
    return flag;
}


////双活二
BOOL isToD2L(int x,
             int y,
             int shapeChess[Size][Size][Size],
             int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    int count = 0;
    for(int d = 0; d < 4; d++)
    {
        int nCount = shapeChess[x][y][d] + shapeChess[x][y][d+4] + 1;
        int nFree1 = shapeSpace[x][y][d] - shapeChess[x][y][d];
        int nFree2 = shapeSpace[x][y][d+4] - shapeChess[x][y][d+4];
        if(nCount >= 2 &&(nFree1>=1&&nFree2>=1) && ((nCount+nFree1+nFree2)>=5))
        {
            count++;
        }
    }
    if(count >= 2)
    {
        flag = TRUE;
    }
    
    return flag;
}

////双冲三
BOOL isToD3D(int x,
             int y,
             int shapeChess[Size][Size][Size],
             int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    int count = 0;
    for(int d = 0; d < 2; d++)
    {
        int nCount = shapeChess[x][y][d] + shapeChess[x][y][d+4] + 1;
        int nFree1 = shapeSpace[x][y][d] - shapeChess[x][y][d];
        int nFree2 = shapeSpace[x][y][d+4] - shapeChess[x][y][d+4];
        if(nCount >= 3 && (nFree1>=1 || nFree2>=1) && ((nCount+nFree1+nFree2)>=5))
        {
            count++;
        }
    }
    if(count >= 2)
    {
        flag = TRUE;
        
    }
    return flag;
}
////实现冲三
BOOL isTo3D(int x,
            int y,
            int shapeChess[Size][Size][Size],
            int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    for(int d = 0; d < 2; d++)
    {
        int nCount = shapeChess[x][y][d] + shapeChess[x][y][d+4] + 1;
        int nFree1 = shapeSpace[x][y][d] - shapeChess[x][y][d];
        int nFree2 = shapeSpace[x][y][d+4] - shapeChess[x][y][d+4];
        if(nCount >= 3 && (nFree1>=1 || nFree2>=1) && ((nCount+nFree1+nFree2)>=5))
        {
            flag = TRUE;
        }
    }
    return flag;
}

////是否能实现活三7
BOOL isTo3L(int x,
            int y,
            int shapeChess[Size][Size][Size],
            int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    for(int d = 0; d < 4; d++)
    {
        int nCount = shapeChess[x][y][d] + shapeChess[x][y][d+4] + 1;
        int nFree1 = shapeSpace[x][y][d] - shapeChess[x][y][d];
        int nFree2 = shapeSpace[x][y][d+4] - shapeChess[x][y][d+4];
        if(nCount >= 3 &&(nFree1>=1 && nFree2>=1) && ((nCount+nFree1+nFree2)> 5))
        {
            flag = TRUE;
            //					System.out.printf("shapeChess[%d][%d] = %d:%n", x, y, shapeChess[x][y][d]);
            //					System.out.printf("shapeChess[%d][%d] = %d:%n", x, y, shapeChess[x][y][d+4]);
            //					System.out.println("nCount:"+nCount);
            //					System.out.println("nFree1:" + nFree1);
            //					System.out.println("nFree2:" + nFree2);
        }
    }
    return flag;
}
////四和冲三6
BOOL isTo4DAnd3D(int x,
                 int y,
                 int shapeChess[Size][Size][Size],
                 int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    int count = 0;
    BOOL flag1 = TRUE;
    for(int d = 0; d < 2; d++)
    {
        int nCount = shapeChess[x][y][d] + shapeChess[x][y][d+4] + 1;
        int nFree1 = shapeSpace[x][y][d] - shapeChess[x][y][d];
        int nFree2 = shapeSpace[x][y][d+4] - shapeChess[x][y][d+4];
        if(nCount >= 4 &&(nFree1>=1 || nFree2>=1))
        {
            count++; continue;
        }
        if((flag1 == TRUE) && nCount >= 3 &&(nFree1>=1 || nFree2>=1)&& ((nCount+nFree1+nFree2)>=5))
        {
            count++;
            flag1 = FALSE;
        }
    }
    if(count >= 2)
    {
        flag = TRUE;
    }
    return flag;
}

//双四3
BOOL isToD4D(int x,
             int y,
             int shapeChess[Size][Size][Size],
             int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    int count = 0;
    for(int d = 0; d < 2; d++)
    {
        int nCount = shapeChess[x][y][d] + shapeChess[x][y][d+4] + 1;
        int nFree1 = shapeSpace[x][y][d] - shapeChess[x][y][d];
        int nFree2 = shapeSpace[x][y][d+4] - shapeChess[x][y][d+4];
        if(nCount >= 4 &&(nFree1>=1 || nFree2>=1))
            count++;
    }
    if(count >= 2)
        flag = TRUE;
    return flag;
}

//是否连五1
BOOL isTo5L(int x,
            int y,
            int shapeChess[Size][Size][Size],
            int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    
    for(int d = 0; d < 2; d++)
    {
        if(shapeSpace[x][y][d]+shapeSpace[x][y][d+4]+1 >= 5)
        {
            int nCount = shapeChess[x][y][d]+shapeChess[x][y][d+4]+1;
            if(nCount >= 5)
            {
                //System.out.printf("shapeChess[%d][%d][%d]=%d , shapeChess[%d][%d][%d]=%d%n",x,y,d,shapeChess[x][y][d],x,y,d+4,shapeChess[x][y][d+4]);
                flag = TRUE;
            }
        }
    }
    return flag;
}

//是否成活四2
BOOL isTo4L(int x,
            int y,
            int shapeChess[Size][Size][Size],
            int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    
    for(int d = 0; d < 2; d++)
    {
        int nCount = shapeChess[x][y][d] + shapeChess[x][y][d+4] + 1;
        int nFree1 = shapeSpace[x][y][d] - shapeChess[x][y][d];
        int nFree2 = shapeSpace[x][y][d+4] - shapeChess[x][y][d+4];
        if(nCount >= 4 &&(nFree1>=1 && nFree2>=1))
        {
            flag = TRUE;
        }
        
    }
    return flag;
}

//实现四和活三或者是双活三4
BOOL isTo4D3LANDD3L(int x,
                    int y,
                    int shapeChess[Size][Size][Size],
                    int shapeSpace[Size][Size][Size])
{
    BOOL flag = FALSE;
    int count = 0;
    for(int d = 0; d < 2; d++)
    {
        int nCount = shapeChess[x][y][d] + shapeChess[x][y][d+4] + 1;
        int nFree1 = shapeSpace[x][y][d] - shapeChess[x][y][d];
        int nFree2 = shapeSpace[x][y][d+4] - shapeChess[x][y][d+4];
        if(nCount >= 4 &&(nFree1>=1 || nFree2>=1))
        {
            count++; continue;
        }
        if(nCount >= 3 && (nFree1>=1 && nFree2>=1) && ((nCount+nFree1+nFree2)> 5))
        {
            count++;
        }
    }
    if(count >= 2)
    {
        flag = TRUE;
    }
    return flag;
}