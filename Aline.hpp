#ifndef ALINE_HPP_INCLUDED
#define ALINE_HPP_INCLUDED
class AFigure
{
public:
    virtual ~AFigure(){};
    virtual void Draw(char symb='*') const = 0;
    virtual AFigure& Move(int dx, int dy) = 0;
    void MoveDraw(int dx, int dy, char symb='*');
    virtual AFigure* clone() = 0;
};
class Line : public AFigure
{
private:
    int x1,y1,x2,y2;
    double k, b;
    bool is_horizontal;
    void set_k_b();
public:
    explicit Line(int inx1=0, int iny1=0, int inx2=0, int iny2=0);
    virtual void Draw(char symb='*') const ;
    virtual Line& Move(int dx, int dy);
    virtual Line* clone()
    {
        return new Line(*this);
    }

};
#endif // ALINE_HPP_INCLUDED
