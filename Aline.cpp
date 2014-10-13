#include "Aline.hpp"
#include <curses.h>
void AFigure::MoveDraw(int dx, int dy, char symb)
{
    Draw(' ');
    Move(dx,dy);
    Draw(symb);
}
Line::Line(int inx1, int iny1, int inx2, int iny2):
    x1(inx1), y1(iny1), x2(inx2), y2(iny2),
    k(0), b (0), //Тільки щоб зникло попередження, викликане -Weffc++
    is_horizontal( !(x1-x2) )
{
    set_k_b();
}

void Line::set_k_b()
{
    is_horizontal = x1 == x2;
    if( !is_horizontal )
    {
        k = static_cast<double>(y1-y2)/(x1-x2);
        b = y1 - k*x1;
    }else
    {
        k = 0;
        b = 0;
    }

}

void Line::Draw(char symb) const
{
        if(is_horizontal)
        {
            int ymin = y1<y2 ? y1 : y2;
            int ymax = y1>y2 ? y1 : y2;
            for(int i=ymin; i<=ymax; ++i)
            {
                mvaddch( x1, i, symb);
            }
        }
        else
        {
            int xmin =x1<x2?x1:x2;
            int xmax = x1>x2?x1:x2;
            int ymin = y1<y2?y1:y2;
            int ymax = y1>y2?y1:y2;
            if( xmin-xmax > ymin-ymax )
            {
                for(int i=xmin; i<=xmax; ++i )
                {
                    mvaddch( i, (i*k + b),symb);
                }
            }else
            {
                for(int i=ymin; i<=ymax; ++i )
                {
                    mvaddch(  ((i - b)/k ), i, symb);
                }

            }
        }
        refresh();
}



Line& Line::Move(int dx, int dy)
{
    x1 += dx;
    x2 += dx;
    y1 += dy;
    y2 += dy;
    set_k_b();
    return *this;
}
