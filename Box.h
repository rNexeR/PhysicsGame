#ifndef BOX_H
#define BOX_H


class Box
{
    public:
        float x, y, height, width, scale;
        Box(float x, float y, float width, float height, float scale);
        virtual ~Box();
    protected:
    private:
};

#endif // BOX_H
