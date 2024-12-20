#pragma once

#include <climits>

#include <windows.h>

#if !defined(EGE_W64)
#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#define EGE_W64 __w64
#else
#define EGE_W64
#endif
#endif

#ifndef __int3264
#if defined(_WIN64)
typedef __int64          LONG_PTR, *PLONG_PTR;
typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;

#define __int3264 __int64

#else
typedef EGE_W64 long          LONG_PTR, *PLONG_PTR;
typedef EGE_W64 unsigned long ULONG_PTR, *PULONG_PTR;

#define __int3264 __int32

#endif
#endif

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;

typedef unsigned int uint32;

#if !defined(_MSC_VER) || _MSC_VER > 1200
typedef intptr_t POINTER_SIZE;
#else
typedef long POINTER_SIZE;
#endif


#ifndef EGE_TEMP_MIN
#define EGE_TEMP_MIN(a, b)  ((b) < (a) ? (b) : (a))
#endif

#ifndef EGE_TEMP_MAX
#define EGE_TEMP_MAX(a, b)  ((b) > (a) ? (b) : (a))
#endif

#ifndef EGE_TEMP_DIFF
#define EGE_TEMP_DIFF(a, b)  (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))
#endif

#ifndef EGE_TEMP_DIFF_UINT
#define EGE_TEMP_DIFF_UINT(a, b)  ((unsigned int)EGE_TEMP_DIFF(a, b))
#endif

#ifndef EGE_TEMP_MIDPOINT_INT
#define EGE_TEMP_MIDPOINT_INT(a, b)  \
    ((a) < (b) ? ((a) + ((unsigned)(b) - (a)) / 2) : ((a) - ((unsigned)(a) - (b)) / 2))
#endif

#ifndef EGE_TEMP_ROUND
#define EGE_TEMP_ROUND(x)  ((int)((x) > 0.0 ? ((x) + 0.5) : ((x) - 0.5)))
#endif


#include "enums.h"

namespace ege
{

#ifndef EGE_BYTE_TYPEDEF
#define EGE_BYTE_TYPEDEF
typedef unsigned char byte;
#endif


//------------------------------------------------------------------------------
//                                Point & Pointf
//------------------------------------------------------------------------------
struct Pointf;

struct Point
{
    int x;
    int y;

public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    explicit Point(Pointf point);

    void set(int x, int y);
    void set(const Point& point);
    void offset(int dx, int dy);
};  // Point

bool operator==(const Point& a, const Point& b);
bool operator!=(const Point& a, const Point& b);

Point offset(const Point& point, int dx, int dy);
//------------------------------------------------------------------------------

struct Pointf
{
    float x;
    float y;

public:
    Pointf() : x(0.0f), y(0.0f) {}
    Pointf(float x, float y) : x(x), y(y) {}
    explicit Pointf(Point point);

    void set(float x, float y);
    void set(const Pointf& point);
    void offset(float dx, float dy);

    bool nearEquals(const Pointf& point, float error = 1E-5f) const;

    Point nearestPoint() const;
};  // Pointf

bool operator==(const Pointf& a, const Pointf& b);
bool operator!=(const Pointf& a, const Pointf& b);

Pointf offset(const Pointf& point, float dx, float dy);

//------------------------------------------------------------------------------

inline Point::Point(Pointf point)  : x((int)point.x),   y((int)point.y)   {}
inline Pointf::Pointf(Point point) : x((float)point.x), y((float)point.y) {}

inline void Point::set(int x, int y)
{
    set(Point(x, y));
}

inline void Point::set(const Point& point)
{
    x = point.x;
    y = point.y;
}

inline void Point::offset(int dx, int dy)
{
    x += dx;
    y += dy;
}

inline bool operator== (const Point& a, const Point& b)
{
    return (a.x == b.x) && (a.y == b.y);
}

inline bool operator!= (const Point& a, const Point& b)
{
    return !(a == b);
}

inline void Pointf::set(float x, float y)
{
    set(Pointf(x, y));
}

inline void Pointf::set(const Pointf& point)
{
    x = point.x;
    y = point.y;
}

inline void Pointf::offset(float dx, float dy)
{
    x += dx;
    y += dy;
}

inline bool Pointf::nearEquals(const Pointf& point, float error) const
{
    return (EGE_TEMP_DIFF(x, point.x) <= error)
        && (EGE_TEMP_DIFF(y, point.y) <= error);
}

inline Point Pointf::nearestPoint() const
{
    return Point(EGE_TEMP_ROUND(x), EGE_TEMP_ROUND(y));
}

inline Pointf offset(const Pointf& point, float dx, float dy)
{
    return Pointf(point.x + dx, point.y + dy);
}

inline Point offset(const Point& point, int dx, int dy)
{
    return Point(point.x + dx, point.y + dy);
}

inline bool operator== (const Pointf& a, const Pointf& b)
{
    return (a.x == b.x) && (a.y == b.y);
}

inline bool operator!= (const Pointf& a, const Pointf& b)
{
    return !(a == b);
}


//------------------------------------------------------------------------------
//                               Size & Sizef
//------------------------------------------------------------------------------
struct Size
{
    int width;
    int height;

public:
    Size() : width(0), height(0) {}
    Size(int width, int height) : width(width), height(height) {}

    void set(int width, int height);
    void setEmpty();

    bool isNull()       const;
    bool isEmpty()      const;
    bool isValid()      const;
    bool isNormalized() const;

    void tranpose();
    void normalize();
};  // Size

bool operator== (const Size& a, const Size& b);
bool operator!= (const Size& a, const Size& b);

Size normalize(const Size& size);

//------------------------------------------------------------------------------

struct Sizef
{
    float width;
    float height;

public:
    Sizef() : width(0.0f), height(0.0f) {}
    Sizef(float width, float height) : width(width), height(height) {}

    void set(float width, float height);
    void setEmpty();

    bool isNull()       const;
    bool isEmpty()      const;
    bool isValid()      const;
    bool isNormalized() const;

    bool nearEquals(const Sizef& size, float error = 1E-5f) const;

    void tranpose();
    void normalize();
}; // Sizef

bool operator== (const Sizef& a, const Sizef& b);
bool operator!= (const Sizef& a, const Sizef& b);

Sizef normalize(const Sizef& size);

//---------------------------------- Size ----------------------------------

inline bool Size::isNull()       const { return (width == 0) && (height == 0); }
inline bool Size::isEmpty()      const { return (width == 0) || (height == 0); }
inline bool Size::isValid()      const { return (width >  0) && (height >  0); }
inline bool Size::isNormalized() const { return (width >= 0) && (height >= 0); }

inline void Size::set(int width, int height)
{
    this->width  = width;
    this->height = height;
}

inline void Size::setEmpty()
{
    set(0, 0);
}

inline bool operator== (const Size& a, const Size& b)
{
    return (a.width == b.width) && (a.height == b.height);
}

inline bool operator!= (const Size& a, const Size& b)
{
    return !(a == b);
}

inline void Size::tranpose()
{
    int temp = width;
    width = height;
    height = temp;
}

inline void Size::normalize()
{
    if (width  < 0) {
        width  = -width;
    }

    if (height < 0) {
        height = -height;
    }
}

inline Size normalize(const Size& size)
{
    Size s(size);
    s.normalize();
    return s;
}

//---------------------------------- Sizef ----------------------------------

inline bool Sizef::isNull()       const { return (width == 0.0f) && (height == 0.0f); }
inline bool Sizef::isEmpty()      const { return (width == 0.0f) || (height == 0.0f); }
inline bool Sizef::isValid()      const { return (width >  0.0f) && (height >  0.0f); }
inline bool Sizef::isNormalized() const { return (width >= 0.0f) && (height >= 0.0f); }

inline void Sizef::set(float width, float height)
{
    this->width  = width;
    this->height = height;
}

inline void Sizef::setEmpty()
{
    set(0.0f, 0.0f);
}

inline bool operator== (const Sizef& a, const Sizef& b)
{
    return (a.width == b.width) && (a.height == b.height);
}

inline bool operator!= (const Sizef& a, const Sizef& b)
{
    return !(a == b);
}

inline bool Sizef::nearEquals(const Sizef& size, float error) const
{
    return (EGE_TEMP_DIFF(width, size.width) <= error)
        && (EGE_TEMP_DIFF(height, size.height) <= error);
}

inline void Sizef::tranpose()
{
    float temp = width;
    width = height;
    height = temp;
}

inline void Sizef::normalize()
{
    if (width  < 0.0f) {
        width  = -width;
    }

    if (height < 0.0f) {
        height = -height;
    }
}

inline Sizef normalize(const Sizef& size)
{
    Sizef s(size);
    s.normalize();
    return s;
}


//------------------------------------------------------------------------------
//                                 Bound & Rect
//------------------------------------------------------------------------------
struct Rect;

struct Bound
{
    int left;
    int top;
    int right;
    int bottom;

public:
    Bound();
    Bound(int left, int top, int right, int bottom, bool normalize = true);
    Bound(const Point& topLeft, const Point& bottomRight, bool normalize = true);
    explicit Bound(const Rect& rect);

    void set(int left, int top, int right, int bottom, bool normalize = true);
    void setRect(const Rect& rect);
    void setRect(int x, int y, int width, int height, bool normalize = true);
    void setRect(Point topLeft, Size size, bool normalize = true);
    void setEmpty();

    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);

    void setXY(int x, int y);
    void setXY(Point xy);
    void setSize(const Size& size);
    void setSize(int width, int height);

    bool setLargeWidth(unsigned int width);
    bool setLargeHeight(unsigned int height);
    bool setLargeSize(unsigned int width, unsigned int height);

    void setLeft(int left);
    void setTop(int top);
    void setRight(int right);
    void setBottom(int bottom);

    void setTopLeft    (int x, int y);
    void setTopRight   (int x, int y);
    void setBottomLeft (int x, int y);
    void setBottomRight(int x, int y);

    void setTopLeft    (const Point& point);
    void setTopRight   (const Point& point);
    void setBottomLeft (const Point& point);
    void setBottomRight(const Point& point);

    void setLeftRight  (int left, int right);
    void setTopBottom  (int top,  int bottom);

    int x()      const;
    int y()      const;
    int width()  const;
    int height() const;

    Point xy()   const;
    Size size()  const;

    Point  topLeft()      const;
    Point  topRight()     const;
    Point  bottomLeft()   const;
    Point  bottomRight()  const;

    int    centerX()      const;
    int    centerY()      const;
    Point  center()       const;

    double exactCenterX() const;
    double exactCenterY() const;
    Pointf exactCenter()  const;

    bool isNull()         const;
    bool isEmpty()        const;
    bool isValid()        const;
    bool isNormalized()   const;

    bool isWidthOutOfRange()  const;
    bool isHeightOutOfRange() const;
    bool isOutOfRange()       const;

    bool isContains(int x, int y)       const;
    bool isContains(const Point& point) const;
    bool isContains(const Bound& bound) const;
    bool isContains(int left, int top, int right, int bottom) const;

    bool isOverlaps(const Bound& bound) const;
    bool isOverlaps(int left, int top, int right, int bottom) const;

    void transpose();
    void offset  (int dx, int dy);
    void offsetTo(int  x, int  y);
    void offsetTo(const Point& point);

    bool normalize();
    bool fixedNormalize();

    void flipHorizonal();
    void flipVertical();

    void inset (int margin);
    void inset (int dx, int dy);
    void inset (int leftMargin, int topMargin, int rightMargin, int bottomMargin);
    void outset(int margin);
    void outset(int dx, int dy);
    void outset(int leftMargin, int topMargin, int rightMargin, int bottomMargin);

    void leftAlign  (int left);
    void topAlign   (int top);
    void rightAlign (int right);
    void bottomAlign(int bottom);

    void horizontalAlign(int x);
    void verticalAlign  (int y);
    void centerAlign(int x, int y);
    void centerAlign(const Point& point);

    void alignTo(const Point& point, Alignment alignment);
    void alignTo(int x, int y, Alignment alignment);
    void alignTo(const Bound& bound, Alignment alignment);

    void scale(float scale);
    void scale(float xScale, float yScale);
    void scale(float xScale, float yScale, Pointf center);

    bool intersect(const Bound& bound);
    bool intersect(const Rect& rect);
    bool intersect(int left, int top, int right, int bottom);

    void unite(const Bound& bound);
    void unite(int x, int y);
    void unite(const Point& point);
    void unite(const Point points[], int length);
}; // Bound

bool operator==(const Bound& a, const Bound& b);
bool operator!=(const Bound& a, const Bound& b);

Bound offset(const Bound& bound, int dx, int dy);

Bound intersect(const Bound& a, const Bound& b);

Bound intersect(const Rect& a, const Bound& b);

Bound intersect(const Bound& a, const Rect& b);

Bound unite(const Bound& a, const Bound& b);

Bound getBounds(const Point points[], int length);

//------------------------------------------------------------------------------

struct Rect
{
    int x;
    int y;
    int width;
    int height;

public:
    Rect();
    Rect(int x, int y, int width, int height, bool normalize = true);
    Rect(const Point& topLeft, const Size& size, bool normalize = true);
    explicit Rect(const Bound& bound);

    void set(int x, int y, int width, int height, bool normalize = true);
    void set(const Point& topLeft, const Size& size, bool normalize = true);
    void setBound(const Bound& bound);
    void setBound(int left, int top, int right, int bottom, bool normalize = true);
    void setBound(const Point& topLeft, const Point& bottomRight, bool normalize = true);
    void setEmpty();

    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);

    void setXY(int x, int y);
    void setXY(Point xy);
    void setSize(const Size& size);
    void setSize(int width, int height);

    void setLeft(int left);
    void setTop(int top);
    void setRight(int right);
    void setBottom(int bottom);

    void setTopLeft    (int x, int y);
    void setTopRight   (int x, int y);
    void setBottomLeft (int x, int y);
    void setBottomRight(int x, int y);

    void setTopLeft    (const Point& point);
    void setTopRight   (const Point& point);
    void setBottomLeft (const Point& point);
    void setBottomRight(const Point& point);

    void setLeftRight  (int left, int right);
    void setTopBottom  (int top,  int bottom);

    int left()   const;
    int top()    const;
    int right()  const;
    int bottom() const;

    Point xy()   const;
    Size  size() const;

    Point  topLeft()      const;
    Point  topRight()     const;
    Point  bottomLeft()   const;
    Point  bottomRight()  const;

    int    centerX()      const;
    int    centerY()      const;
    Point  center()       const;

    double exactCenterX() const;
    double exactCenterY() const;
    Pointf exactCenter()  const;

    bool isNull()         const;
    bool isEmpty()        const;
    bool isValid()        const;
    bool isNormalized()   const;

    bool isContains(int x, int y)       const;
    bool isContains(const Point& point) const;
    bool isContains(const Rect& rect)   const;
    bool isContains(int x, int y, int width, int height) const;

    bool isOverlaps(const Rect& rect)   const;
    bool isOverlaps(int x, int y, int width, int height) const;

    void transpose();
    void offset  (int dx, int dy);
    void offsetTo(int  x, int  y);
    void offsetTo(const Point& point);

    bool normalize();
    bool fixedNormalize();

    void inset   (int margin);
    void inset   (int dx, int dy);
    void inset   (int leftMargin, int topMargin, int rightMargin, int bottomMargin);
    void outset  (int margin);
    void outset  (int dx, int dy);
    void outset  (int leftMargin, int topMargin, int rightMargin, int bottomMargin);

    void leftAlign  (int left);
    void topAlign   (int top);
    void rightAlign (int right);
    void bottomAlign(int bottom);

    void horizontalAlign(int x);
    void verticalAlign(int y);
    void centerAlign(int x, int y);
    void centerAlign(Point point);

    void alignTo(const Point& point, Alignment alignment);
    void alignTo(int x, int y, Alignment alignment);
    void alignTo(const Rect& rect, Alignment alignment);

    void scale(float scale);
    void scale(float xScale, float yScale);
    void scale(float xScale, float yScale, Pointf center);

    bool intersect(const Rect& rect);
    bool intersect(const Bound& bound);
    bool intersect(int x, int y, int width, int height);

    bool unite(const Rect& rect);
    bool unite(int x, int y);
    bool unite(const Point& point);
    bool unite(const Point points[], int length);
    bool unite(int x, int y, int width, int height);

    void clip (int xMin, int xMax, int yMin, int yMax);
    void clipX(int xMin, int xMax);
    void clipY(int yMin, int yMax);
    void clip ();
    void clipX();
    void clipY();

    bool isOutOfRange(int xMin, int xMax, int yMin, int yMax) const;
    bool isOutOfRange() const;
    bool isXOutOfRange(int xMin, int xMax) const;
    bool isYOutOfRange(int yMin, int yMax) const;
    bool isXOutOfRange() const;
    bool isYOutOfRange() const;
private:
    static bool clipByLimits(int& x,  int& length, int minval, int maxval);
}; // Rect


bool operator==(const Rect& a, const Rect& b);
bool operator!=(const Rect& a, const Rect& b);

Rect clip(const Rect& rect);

Rect offset(const Rect& rect, int dx, int dy);

Rect normalize(const Rect& rect);

Rect intersect(const Rect& a, const Rect& b);

Rect unite(const Rect& a, const Rect& b);

//------------------------------------------------------------------------------

inline Bound::Bound(): left(0), top(0), right(0), bottom(0) {}

inline Bound::Bound(int left, int top, int right, int bottom, bool normalize)
    : left(left), top(top), right(right), bottom(bottom)
{
    if (normalize)
        this->normalize();
}

inline Bound::Bound(const Point& topLeft, const Point& bottomRight, bool normalize)
    : left(topLeft.x), top(topLeft.y), right(bottomRight.x), bottom(bottomRight.y)
{
    if (normalize)
        this->normalize();
}

inline Bound::Bound(const Rect& rect)
    : left(rect.x), top(rect.y), right(rect.x + rect.width), bottom(rect.y + rect.height)
{ }

inline void Bound::setX     (int x)                   { right  += x - left;    left = x;    }
inline void Bound::setY     (int y)                   { bottom += y - top;     top  = y;    }
inline void Bound::setWidth (int width)               { right   = left + width;             }
inline void Bound::setHeight(int height)              { bottom  = top + height;             }

inline void Bound::setXY(int x, int y)                { setX(x);    setY(y);                }
inline void Bound::setXY(Point xy)                    { setXY(xy.x, xy.y);                  }
inline void Bound::setSize(const Size& size)          { setSize(size.width, size.height);   }
inline void Bound::setSize(int width, int height)     { setWidth(width); setHeight(height); }

inline void Bound::setLeft  (int left)                { this->left   = left;                }
inline void Bound::setTop   (int top)                 { this->top    = top;                 }
inline void Bound::setRight (int right)               { this->right  = right;               }
inline void Bound::setBottom(int bottom)              { this->bottom = bottom;              }

inline void Bound::setTopLeft    (int x, int y)       { setLeft(x);   setTop(y);            }
inline void Bound::setTopRight   (int x, int y)       { setRight(x);  setTop(y);            }
inline void Bound::setBottomLeft (int x, int y)       { setLeft(x);   setBottom(y);         }
inline void Bound::setBottomRight(int x, int y)       { setRight(x);  setBottom(y);         }

inline void Bound::setTopLeft    (const Point& point) { setTopLeft(point.x, point.y);       }
inline void Bound::setTopRight   (const Point& point) { setTopRight(point.x, point.y);      }
inline void Bound::setBottomLeft (const Point& point) { setBottomLeft(point.x, point.y);    }
inline void Bound::setBottomRight(const Point& point) { setBottomRight(point.x, point.y);   }

inline void Bound::setLeftRight(int left, int right)  { setLeft(left); setRight(right);     }
inline void Bound::setTopBottom(int top,  int bottom) { setTop(top);   setBottom(bottom);   }

inline int    Bound::x()            const { return left;                               }
inline int    Bound::y()            const { return top;                                }
inline int    Bound::width()        const { return right - left;                       }
inline int    Bound::height()       const { return bottom - top;                       }
inline Point  Bound::xy()           const { return Point(left, top);                   }
inline Size   Bound::size()         const { return Size(width(), height());            }

inline Point  Bound::topLeft()      const { return Point(left,  top);                  }
inline Point  Bound::topRight()     const { return Point(right, top);                  }
inline Point  Bound::bottomLeft()   const { return Point(left,  bottom);               }
inline Point  Bound::bottomRight()  const { return Point(right, bottom);               }

inline int    Bound::centerX()      const { return EGE_TEMP_MIDPOINT_INT(left, right); }
inline int    Bound::centerY()      const { return EGE_TEMP_MIDPOINT_INT(top, bottom); }
inline Point  Bound::center()       const { return Point(centerX(), centerY());        }

inline double Bound::exactCenterX() const { return 0.5 * left + 0.5 * right;           }
inline double Bound::exactCenterY() const { return 0.5 * top  + 0.5 * bottom;          }

inline Pointf Bound::exactCenter()  const
{
    return Pointf((float)exactCenterX(), (float)exactCenterY());
}

inline void Bound::leftAlign  (int left)     { setX(left);                 }
inline void Bound::topAlign   (int top)      { setY(top);                  }
inline void Bound::rightAlign (int right)    { setX(right  - width());     }
inline void Bound::bottomAlign(int bottom)   { setY(bottom - height());    }
inline void Bound::horizontalAlign(int x)    { setX(x + left - centerX()); }
inline void Bound::verticalAlign  (int y)    { setY(y - top  - centerY()); }
inline void Bound::centerAlign(int x, int y) { centerAlign(Point(x, y));   }

inline void Bound::centerAlign(const Point& point)
{
    horizontalAlign(point.x);
    verticalAlign(point.y);
}

inline bool   Bound::isNull()       const { return (left == right) && (top == bottom); }
inline bool   Bound::isEmpty()      const { return (left == right) || (top == bottom); }
inline bool   Bound::isValid()      const { return (left <  right) && (top <  bottom); }
inline bool   Bound::isNormalized() const { return (left <= right) && (top <= bottom); }

inline bool Bound::isWidthOutOfRange() const
{
    if (left < right)
        return ((unsigned)right - left) > (unsigned)INT_MAX;
    else
        return ((unsigned)left - right) > (unsigned)INT_MIN;
}

inline bool Bound::isHeightOutOfRange() const
{
    if (top < bottom)
        return (unsigned)bottom - top > (unsigned)INT_MAX;
    else
        return (unsigned)top - bottom > (unsigned)INT_MIN;
}

inline bool Bound::isOutOfRange() const
{
    return isWidthOutOfRange() || isHeightOutOfRange();
}

inline void Bound::set(int left, int top, int right, int bottom, bool normalize)
{
    this->left   = left;
    this->top    = top;
    this->right  = right;
    this->bottom = bottom;

    if (normalize)
        this->normalize();
}

inline void Bound::setRect(const Rect& rect)
{
    left   = rect.x;
    top    = rect.y;
    right  = rect.x + rect.width;
    bottom = rect.y + rect.height;
}

inline void Bound::setRect(int x, int y, int width, int height, bool normalize)
{
    setRect(Rect(x, y, width, height, normalize));
}

inline void Bound::setRect(Point topLeft, Size size, bool normalize)
{
    setRect(Rect(topLeft, size, normalize));
}

inline void Bound::setEmpty()
{
    left = top = right = bottom = 0;
}

inline bool Bound::isContains(const Point& point) const
{
    return isContains(point.x, point.y);
}

inline bool Bound::isContains(int x, int y) const
{
    return (left <= x) && (x < right)
        && (top  <= y) && (y < bottom);
}

inline bool Bound::isContains(const Bound& bound) const
{
    return (left <= bound.left) && (right  >= bound.right)
        && (top  <= bound.top)  && (bottom >= bound.bottom);
}

inline bool Bound::isContains(int left, int top, int right, int bottom) const
{
    return isContains(Bound(left, top, right, bottom));
}

inline bool Bound::isOverlaps(const Bound& bound) const
{
    return (left < bound.right)  && (right  > bound.left)
        && (top  < bound.bottom) && (bottom > bound.top);
}

inline bool Bound::isOverlaps(int left, int top, int right, int bottom) const
{
    return isOverlaps(Bound(left, top, right, bottom));
}

inline bool Bound::normalize()
{
    bool changed = false;

    if (left > right) {
        flipHorizonal();
        changed = false;
    }

    if (top > bottom) {
        flipVertical();
        changed = true;
    }

    return changed;
}

inline bool Bound::fixedNormalize()
{
    bool changed = false;

    if (left > right) {
        int temp = left;
        left = right + 1;
        right = temp + 1;
        changed = true;
    }

    if (top > bottom) {
        int temp = top;
        top = bottom + 1;
        bottom = temp + 1;
        changed = true;
    }

    return changed;
}

inline void Bound::flipHorizonal()
{
    int temp = left;
    left = right;
    right = temp;
}

inline void Bound::flipVertical()
{
    int temp = top;
    top = bottom;
    bottom = temp;
}

inline void Bound::transpose()
{
    int w = width();
    setWidth(height());
    setHeight(w);
}

inline void Bound::offset(int dx, int dy)
{
    left   += dx;
    top    += dy;
    right  += dx;
    bottom += dy;
}

inline void Bound::offsetTo(int  x, int  y)     { setTopLeft(x, y);           }
inline void Bound::offsetTo(const Point& point) { offsetTo(point.x, point.y); }

inline void Bound::inset(int margin)      { inset(margin, margin, margin, margin);  }
inline void Bound::inset(int dx, int dy)  { inset(dx, dy, dx, dy);                  }

inline void Bound::inset(int leftMargin, int topMargin, int rightMargin, int bottomMargin)
{
    left   += leftMargin;
    top    += topMargin;
    right  -= rightMargin;
    bottom -= bottomMargin;
}

inline void Bound::outset(int margin)     { outset(margin, margin, margin, margin); }
inline void Bound::outset(int dx, int dy) { outset(dx, dy, dx, dy);                 }

inline void Bound::outset(int leftMargin, int topMargin, int rightMargin, int bottomMargin)
{
    inset(-leftMargin, -topMargin, -rightMargin, -bottomMargin);
}

inline bool Bound::setLargeWidth(unsigned int width)
{
    bool overflow = left > (int)(INT_MAX - width);
    right = overflow ? INT_MAX : (int)(left + width);

    return !overflow;
}

inline bool Bound::setLargeHeight(unsigned int height)
{
    bool overflow = top > (int)(INT_MAX - height);
    bottom = overflow ? INT_MAX : (int)(top + height);

    return !overflow;
}

inline bool Bound::setLargeSize(unsigned int width, unsigned int height)
{
    return setLargeHeight(height) & setLargeWidth(width);  // Not &&
}


inline void Bound::alignTo(const Point& point, Alignment alignment)
{
    alignTo(point.x, point.y, alignment);
}

inline void Bound::alignTo(int x, int y, Alignment alignment)
{
    unsigned int horizontalAlignment = (unsigned int)alignment & ALIGNMENT_HORIZONTAL_MASK;
    if (horizontalAlignment != 0) {
        switch(horizontalAlignment & (~horizontalAlignment + 1)) {
        case Alignment_LEFT:   leftAlign(x);               break;
        case Alignment_HMID:   setX(x + left - centerX()); break;
        case Alignment_RIGHT:  rightAlign(x);              break;
        default: break; // Do nothing
        }
    }

    unsigned int verticalAlignment = (unsigned int)alignment & ALIGNMENT_VERTICAL_MASK;
    if (verticalAlignment != 0) {
        switch(verticalAlignment & (~verticalAlignment + 1)) {
        case Alignment_TOP:    topAlign(y);                break;
        case Alignment_VMID:   setY(y + top - centerY());  break;
        case Alignment_BOTTOM: bottomAlign(y);             break;
        default: break; // Do nothing
        }
    }
}

inline void Bound::alignTo(const Bound& bound, Alignment alignment)
{
    unsigned int horizontalAlignment = (unsigned int)alignment & ALIGNMENT_HORIZONTAL_MASK;
    if (horizontalAlignment != 0) {
        switch(horizontalAlignment & (~horizontalAlignment + 1)) {
        case Alignment_LEFT:   leftAlign(bound.left);                    break;
        case Alignment_HMID:   setX(bound.centerX() + left - centerX()); break;
        case Alignment_RIGHT:  rightAlign(bound.right);                  break;
        default: break; // Do nothing
        }
    }

    unsigned int verticalAlignment = (unsigned int)alignment & ALIGNMENT_VERTICAL_MASK;
    if (verticalAlignment != 0) {
        switch(verticalAlignment & (~verticalAlignment + 1)) {
        case Alignment_TOP:    topAlign(bound.top);                      break;
        case Alignment_VMID:   setY(bound.centerY() + top - centerY());  break;
        case Alignment_BOTTOM: bottomAlign(bound.bottom);                break;
        default: break; // Do nothing
        }
    }
}

inline void Bound::scale(float scale)
{
    this->scale(scale, scale);
}

inline void Bound::scale(float xScale, float yScale)
{
    right  = left + EGE_TEMP_ROUND(((double)right - left) * xScale);
    bottom = top  + EGE_TEMP_ROUND(((double)bottom - top) * yScale);
}

inline void Bound::scale(float xScale, float yScale, Pointf center)
{
    left   = EGE_TEMP_ROUND(center.x + ((double)left   - center.x) * xScale);
    top    = EGE_TEMP_ROUND(center.y + ((double)top    - center.y) * yScale);
    right  = EGE_TEMP_ROUND(center.x + ((double)right  - center.x) * xScale);
    bottom = EGE_TEMP_ROUND(center.y + ((double)bottom - center.y) * yScale);
}

inline bool Bound::intersect(const Bound& bound)
{
    /* Unlike isOverlaps(), this only checks for no overlaps at all
     * and allows edges to overlap. */
    if ((left > bound.right) || (top > bound.bottom) || (right < bound.left) || (bottom < bound.top))
    {
        setEmpty();
        return false;
    }

    int left    = EGE_TEMP_MAX(this->left,   bound.left);
    int top     = EGE_TEMP_MAX(this->top,    bound.top);
    int right   = EGE_TEMP_MIN(this->right,  bound.right);
    int bottom  = EGE_TEMP_MIN(this->bottom, bound.bottom);

    set(left, top, right, bottom);

    return !isEmpty();
}

inline bool Bound::intersect(const Rect& rect)
{
    return intersect(Bound(clip(rect)));
}

inline bool Bound::intersect(int left, int top, int right, int bottom)
{
    return intersect(Bound(left, top, right, bottom));
}

inline void Bound::unite(const Point& point)
{
    unite(point.x, point.y);
}

inline void Bound::unite(int x, int y)
{
    if (x < left) {
        setLeft(x);
    } else if (x > right) {
        setRight(x);
    }

    if (y < top) {
        setTop(y);
    } else if (y > bottom) {
        setBottom(y);
    }
}

inline void Bound::unite(const Point points[], int length)
{
    for (int i = 0; i < length; i++)
        unite(points[i]);
}

inline void Bound::unite(const Bound& bound)
{
    if (bound.isEmpty()) {
        return;
    }

    if (isEmpty()) {
        *this = bound;
        return;
    }

    int left   = EGE_TEMP_MIN(this->left,   bound.left);
    int top    = EGE_TEMP_MIN(this->top,    bound.top);
    int right  = EGE_TEMP_MAX(this->right,  bound.right);
    int bottom = EGE_TEMP_MAX(this->bottom, bound.bottom);

    set(left, top, right, bottom, false);
}

inline bool operator==(const Bound& a, const Bound& b)
{
    return (a.left == b.left) && (a.top == b.top)
        && (a.right == b.right) && (a.bottom == b.bottom);
}

inline bool operator!=(const Bound& a, const Bound& b)
{
    return !(a == b);
}

inline Bound unite(const Bound& a, const Bound& b)
{
    Bound c(a);
    c.unite(b);
    return c;
}

inline Bound getBounds(const Point points[], int length)
{
    if (length <= 0)
        return Bound();

    int left   = points[0].x;
    int top    = points[0].y;
    int right  = left;
    int bottom = top;

    for (int i = 1; i < length; i++) {
        if (points[i].x < left) {
            left = points[i].x;
        } else if (points[i].x > right) {
            right = points[i].x;
        }

        if (points[i].y < top) {
            top = points[i].y;
        } else if (points[i].y > bottom) {
            bottom = points[i].y;
        }
    }

    return Bound(left, top, right, bottom, false);
}

inline Bound intersect(const Bound& a, const Bound& b)
{
    Bound c(a);
    c.intersect(b);
    return c;
}

inline Bound intersect(const Rect& a, const Bound& b)
{
    return intersect(Bound(clip(a)), b);
}

inline Bound intersect(const Bound& a, const Rect& b)
{
    return intersect(a, Bound(clip(b)));
}

inline Bound offset(const Bound& bound, int dx, int dy)
{
    return Bound(bound.left + dx, bound.top + dy, bound.right + dx, bound.bottom + dy, false);
}

//------------------------------------------------------------------------------
//                                    Rect
//------------------------------------------------------------------------------

inline Rect::Rect(): x(0), y(0), width(0), height(0) {}

inline Rect::Rect(int x, int y, int width, int height, bool normalize)
    : x(x), y(y), width(width), height(height)
{
    if (normalize)
        this->normalize();
}

inline Rect::Rect(const Point& topLeft, const Size& size, bool normalize)
    : x(topLeft.x), y(topLeft.y), width(size.width), height(size.height)
{
    if (normalize)
        this->normalize();
}

inline Rect::Rect(const Bound& bound)
    : x(bound.x()), y(bound.y()), width(bound.width()), height(bound.height())
{ }

inline int    Rect::left()          const { return x;                            }
inline int    Rect::top()           const { return y;                            }
inline int    Rect::right()         const { return x + width;                    }
inline int    Rect::bottom()        const { return y + height;                   }
inline Point  Rect::topLeft()       const { return Point(x, y);                  }
inline Point  Rect::topRight()      const { return Point(x + width, y);          }
inline Point  Rect::bottomLeft()    const { return Point(x, y + height);         }
inline Point  Rect::bottomRight()   const { return Point(x + width, y + height); }

inline Point  Rect::xy()            const { return Point(x, y);                  }
inline Size   Rect::size()          const { return Size(width, height);          }

inline int    Rect::centerX()       const { return x + width / 2;                }
inline int    Rect::centerY()       const { return y + height / 2;               }
inline Point  Rect::center()        const { return Point(centerX(), centerY());  }
inline double Rect::exactCenterX()  const { return x + 0.5 * width;              }
inline double Rect::exactCenterY()  const { return y + 0.5 * height;             }

inline Pointf Rect::exactCenter()   const
{
    return Pointf((float)exactCenterX(), (float)exactCenterY());
}

inline void Rect::setX(int x)                        { this->x = x;                                 }
inline void Rect::setY(int y)                        { this->x = y;                                 }
inline void Rect::setWidth(int width)                { this->width  = width;                        }
inline void Rect::setHeight(int height)              { this->height = height;                       }
inline void Rect::setLeft(int left)                  { width  -= left - this->left();    x = left;  }
inline void Rect::setTop(int top)                    { height -= top  - this->top();     y = top;   }
inline void Rect::setRight(int right)                { width  = right - left();                     }
inline void Rect::setBottom(int bottom)              { height = bottom - top();                     }
inline void Rect::setXY(int x, int y)                { this->x = x;    this->y = y;                 }
inline void Rect::setXY(Point xy)                    { setXY(xy.x, xy.y);                           }
inline void Rect::setSize(const Size& size)          { setSize(size.width, size.height);            }
inline void Rect::setSize(int width, int height)     { this->width  = width; this->height = height; }
inline void Rect::setTopLeft    (const Point& point) { setTopLeft(point.x, point.y);                }
inline void Rect::setTopRight   (const Point& point) { setTopRight(point.x, point.y);               }
inline void Rect::setBottomLeft (const Point& point) { setBottomLeft(point.x, point.y);             }
inline void Rect::setBottomRight(const Point& point) { setBottomRight(point.x, point.y);            }
inline void Rect::setTopLeft    (int x, int y)       { setLeft(x);   setTop(y);                     }
inline void Rect::setTopRight   (int x, int y)       { setRight(x);  setTop(y);                     }
inline void Rect::setBottomLeft (int x, int y)       { setLeft(x);   setBottom(y);                  }
inline void Rect::setBottomRight(int x, int y)       { setRight(x);  setBottom(y);                  }
inline void Rect::setLeftRight(int left, int right)  { x = left;     width = right - left;          }
inline void Rect::setTopBottom(int top,  int bottom) { y = top;      height = bottom - top;         }

inline void Rect::set(int x, int y, int width, int height, bool normalize)
{
    this->x = x;
    this->y = y;
    this->width  = width;
    this->height = height;

    if (normalize)
        this->normalize();
}

inline void Rect::set(const Point& topLeft, const Size& size, bool normalize)
{
    setTopLeft(topLeft);
    setSize(size);

    if (normalize)
        this->normalize();
}

inline void Rect::setBound(const Bound& bound)
{
    x = bound.left;
    y = bound.top;
    width  = bound.right  - bound.left;
    height = bound.bottom - bound.top;
}

inline void Rect::setBound(int left, int top, int right, int bottom, bool normalize)
{
    setBound(Bound(left, top, right, bottom, normalize));
}

inline void Rect::setBound(const Point& topLeft, const Point& bottomRight, bool normalize)
{
    setBound(Bound(topLeft, bottomRight, normalize));
}

inline void Rect::setEmpty()
{
    x = y = width = height = 0;
}

inline void Rect::leftAlign  (int left)   { x = left;                 }
inline void Rect::topAlign   (int top)    { y = top;                  }
inline void Rect::rightAlign (int right)  { x = right - width;        }
inline void Rect::bottomAlign(int bottom) { y = bottom - height;      }

inline void Rect::horizontalAlign(int x)  { this->x = x - width / 2;  }
inline void Rect::verticalAlign  (int y)  { this->y = y - height / 2; }

inline void Rect::centerAlign(int x, int y)
{
    centerAlign(Point(x, y));
}

inline void Rect::centerAlign(Point point)
{
    horizontalAlign(point.x);
    verticalAlign(point.y);
}

inline void Rect::alignTo(const Point& point, Alignment alignment)
{
    unsigned int horizontalAlignment = (unsigned int)alignment & ALIGNMENT_HORIZONTAL_MASK;
    if (horizontalAlignment != 0) {
        switch(horizontalAlignment & (~horizontalAlignment + 1)) {
            case Alignment_LEFT:   leftAlign(point.x);       break;
            case Alignment_HMID:   horizontalAlign(point.x); break;
            case Alignment_RIGHT:  rightAlign(point.x);      break;
            default: break; // Do nothing
        }
    }

    unsigned int verticalAlignment = (unsigned int)alignment & ALIGNMENT_VERTICAL_MASK;
    if (verticalAlignment != 0) {
        switch(verticalAlignment & (~verticalAlignment + 1)) {
            case Alignment_TOP:    topAlign(point.y);        break;
            case Alignment_VMID:   verticalAlign(point.y);   break;
            case Alignment_BOTTOM: bottomAlign(point.y);     break;
            default: break; // Do nothing
        }
    }
}

inline void Rect::alignTo(const Rect& rect, Alignment alignment)
{
    unsigned int horizontalAlignment = ((unsigned int)alignment & ALIGNMENT_HORIZONTAL_MASK);
    if (horizontalAlignment != 0) {
        switch(horizontalAlignment & (~horizontalAlignment + 1)) {
            case Alignment_LEFT:   leftAlign(rect.left());          break;
            case Alignment_HMID:   horizontalAlign(rect.centerX()); break;
            case Alignment_RIGHT:  rightAlign(rect.right());        break;
            default: break; // Do nothing.
        }
    }

    unsigned int verticalAlignment = ((unsigned int)alignment & ALIGNMENT_VERTICAL_MASK);
    if (verticalAlignment != 0) {
        switch(verticalAlignment & (~horizontalAlignment + 1)) {
            case Alignment_TOP:    topAlign(rect.top());            break;
            case Alignment_VMID:   verticalAlign(rect.centerY());   break;
            case Alignment_BOTTOM: bottomAlign(rect.bottom());      break;
            default: break; // Do nothing.
        }
    }
}

inline bool Rect::normalize()
{
    bool changed = false;
    if (width < 0) {
        x += width;
        width = -width;
        changed = true;
    }

    if (height < 0) {
        y += height;
        height = -height;
        changed = true;
    }

    return changed;
}

inline bool Rect::fixedNormalize()
{
    bool changed = false;
    if (width < 0) {
        x = x + width + 1;
        width = -width;
        changed = true;
    }

    if (height < 0) {
        y = y + height + 1;
        height = -height;
        changed = true;
    }

    return changed;
}

inline void Rect::transpose()
{
    int temp = width;
    width = height;
    height = temp;
}

inline void Rect::offset(int dx, int dy)        { x += dx;  y += dy;            }
inline void Rect::offsetTo(int x, int y)        { offsetTo(Point(x, y));        }
inline void Rect::offsetTo(const Point& point)  { x = point.x;  y = point.y;    }

inline void Rect::inset(int margin)             { inset(margin, margin);        }
inline void Rect::inset(int dx, int dy)         { inset(dx, dy, dx, dy);        }

inline void Rect::inset(int leftMargin, int topMargin, int rightMargin, int bottomMargin)
{
    x += leftMargin;
    y += topMargin;
    width  -= (leftMargin  + rightMargin);
    height -= (rightMargin + bottomMargin);
}

inline void Rect::outset(int margin)     { inset(-margin);  }
inline void Rect::outset(int dx, int dy) { inset(-dx, -dy); }
inline void Rect::outset(int leftMargin, int topMargin, int rightMargin, int bottomMargin)
{
    inset(-leftMargin, -topMargin, -rightMargin, -bottomMargin);
}

inline void Rect::scale(float scale)
{
    this->scale(scale, scale);
}

inline void Rect::scale(float xScale, float yScale)
{
    double w = ((double)width * xScale);
    double h = ((double)height * yScale);
    width  = EGE_TEMP_ROUND(w);
    height = EGE_TEMP_ROUND(h);
}

inline void Rect::scale(float xScale, float yScale, Pointf center)
{
    double x1 = ((double)x - center.x) * xScale + center.x;
    double y1 = ((double)y - center.y) * xScale + center.y;
    double w  = (double)width  * xScale;
    double h  = (double)height * yScale;

    x      = EGE_TEMP_ROUND(x1);
    y      = EGE_TEMP_ROUND(y1);
    width  = EGE_TEMP_ROUND(w);
    height = EGE_TEMP_ROUND(h);
}

inline bool Rect::isNull()       const { return (width == 0) && (height == 0); }
inline bool Rect::isEmpty()      const { return (width == 0) || (height == 0); }
inline bool Rect::isValid()      const { return (width >  0) && (height >  0); }
inline bool Rect::isNormalized() const { return (width >= 0) && (height >= 0); }

inline bool Rect::isOutOfRange() const
{
    return isXOutOfRange() || isYOutOfRange();
}

/*
 * Checks if the left and right bounds of the rectangle are out of the range of int.
 */
inline bool Rect::isXOutOfRange() const
{
    return (width >= 0) ? (x > INT_MAX - width) : (x < INT_MIN - width);
}

/**
 * @brief Checks if the top and bottom bounds of the rectangle are out of the range of int.
 */
inline bool Rect::isYOutOfRange() const
{
    return (height >= 0) ? (y > INT_MAX - height) : (y < INT_MIN - height);
}

inline bool Rect::isXOutOfRange(int xMin, int xMax) const
{
    if ((xMin > xMax) || (x < xMin) || (x > xMax))
        return true;

    if (width == 0) {
        return false;
    } else if (width > 0) {
        return (unsigned)(xMax - x) < (unsigned)(width - 1);
    } else {
        return (unsigned)(x - xMin) < (unsigned)(-(width + 1));
    }
}

inline bool Rect::isYOutOfRange(int yMin, int yMax) const
{
    if ((yMin > yMax) || (y < yMin) || (y > yMax))
        return true;

    if (height == 0) {
        return false;
    } else if (height > 0) {
        return (unsigned)(yMax - y) < (unsigned)(height - 1);
    } else {
        return (unsigned)(y - yMin) < (unsigned)(-(height + 1));
    }
}

/**
 * @brief Checks if any point that is completely inside the rectangle
 * (excluding points on the right bound) is out of the range of the specified range.
 */
inline bool Rect::isOutOfRange(int xMin, int xMax, int yMin, int yMax) const
{
    return isXOutOfRange(xMin, xMax) || isYOutOfRange(yMin, yMax);
}

inline bool Rect::isContains(int x, int y) const
{
    return isContains(Point(x, y));
}

inline bool Rect::isContains(const Point& point) const
{
    return (point.x >= x) && ((unsigned)(point.x - x) < (unsigned)width)
        && (point.y >= x) && ((unsigned)(point.y - y) < (unsigned)height);
}

inline bool Rect::isContains(int x, int y, int width, int height) const
{
    return isContains(Rect(x, y, width, height));
}

/**
 * @brief Determines whether this rectangle contains another rectangle.
 * @param
 * @return {true:  This rectangle contains the specified rectangle. }
 *         {false: This rectangle does not contain the specified rectangle. }
 * @pre Both rectangles must be normalized.
 */
inline bool Rect::isContains(const Rect& rect) const
{
    if ((rect.x < x) || (rect.y < y))
         return false;

    Rect a(*this), b(rect);
    a.offset(INT_MIN - x, INT_MIN - y);
    b.offset(INT_MIN - x, INT_MIN - y);

    return (a.right() >  b.left())  && (a.bottom() >  b.top())
        && (a.right() >= b.right()) && (a.bottom() >= b.bottom());
}

/**
 * @brief Determine whether two rectangular regions overlap (i.e., the intersection is non-empty).
 * @param rect The rectangle to test for intersection with this rectangle.
 * @pre Both rectangles must be normalized.
 */
inline bool Rect::isOverlaps(const Rect& rect) const
{
    if ((EGE_TEMP_DIFF_UINT(x, rect.x) >= INT_MAX) || (EGE_TEMP_DIFF_UINT(y, rect.y) >= INT_MAX))
        return false;

    int xOffset = INT_MIN - EGE_TEMP_MIN(left(), rect.left());
    int yOffset = INT_MIN - EGE_TEMP_MIN(top(),  rect.top());

    Rect a(*this), b(rect);
    a.offset(xOffset, yOffset);
    b.offset(xOffset, yOffset);

    return (a.left() < b.right())  && (b.left() < a.right())
        && (a.top()  < b.bottom()) && (b.top()  < a.bottom());
}

inline bool Rect::isOverlaps(int x, int y, int width, int height) const
{
    return isOverlaps(Rect(x, y, width, height, false));
}

inline bool Rect::intersect(int x, int y, int width, int height)
{
    return intersect(Rect(x, y, width, height, false));
}

/**
 * @brief Update this rect to be the intersection with another rect.
 * @param rect Target rect.
 * @return Whether the intersection is empty.
 * @pre Both rect must be normalized.
 */
inline bool Rect::intersect(const Rect& rect)
{
    if ((EGE_TEMP_DIFF_UINT(x, rect.x) > INT_MAX) || (EGE_TEMP_DIFF_UINT(y, rect.y) > INT_MAX)) {
        setEmpty();
        return false;
    }

    int xOffset = INT_MIN - EGE_TEMP_MIN(left(), rect.left());
    int yOffset = INT_MIN - EGE_TEMP_MIN(top(),  rect.top());

    Rect a(*this), b(rect);
    a.offset(xOffset, yOffset);
    b.offset(xOffset, yOffset);

    /* Unlike isOverlaps(), this only checks for no overlaps at all
     * and allows edges to overlap. */
    if (   (a.left()  > b.right()) || (a.top()    > b.bottom())
        || (a.right() < b.left())  || (a.bottom() < b.top()))
    {
        setEmpty();
        return false;
    }

    int left   = EGE_TEMP_MAX(a.left(),   b.left());
    int top    = EGE_TEMP_MAX(a.top(),    b.top());
    int right  = EGE_TEMP_MIN(a.right(),  b.right());
    int bottom = EGE_TEMP_MIN(a.bottom(), b.bottom());

    set(left - xOffset, top - yOffset, right - left, bottom - top);

    return !isEmpty();
}

inline bool Rect::intersect(const Bound& bound)
{
    Bound b(bound);
    bool nonEmpty = b.intersect(*this);
    setBound(b);
    return nonEmpty;
}

/**
 * @brief update this rect to be the union with another rect.
 * @param rect target rect.
 * @return The width and height of the union are within the range([0, INT_MAX]).
 * @pre both rect must be normalized.
 */
inline bool Rect::unite(const Rect& rect)
{
    if (rect.isEmpty())
        return true;

    if (isEmpty()) {
        *this = rect;
        return true;
    }

    int xOffset = INT_MIN - EGE_TEMP_MIN(left(), rect.left());
    int yOffset = INT_MIN - EGE_TEMP_MIN(top(),  rect.top());

    Rect a(*this), b(rect);
    a.offset(xOffset, yOffset);
    b.offset(xOffset, yOffset);

    int left   = EGE_TEMP_MIN(a.left(),   b.left());
    int top    = EGE_TEMP_MIN(a.top(),    b.top());
    int right  = EGE_TEMP_MAX(a.right(),  b.right());
    int bottom = EGE_TEMP_MAX(a.bottom(), b.bottom());

    set(left - xOffset, top - yOffset, right - left, bottom - top);

    return (EGE_TEMP_DIFF_UINT(a.x, b.x) <= INT_MAX)
        && (EGE_TEMP_DIFF_UINT(a.y, b.y) <= INT_MAX)
        && ((unsigned)right - left <= INT_MAX)
        && ((unsigned)bottom - top <= INT_MAX);
}

inline bool Rect::unite(int x, int y, int width, int height)
{
    return unite(Rect(x, y, width, height));
}

inline bool Rect::unite(int x, int y)
{
    return unite(Point(x, y));
}

/**
 * @brief Update the rectangle to include its own top-left corner,  bottom-right
 *    corner and the target point
 * @param point target point
 * @return The width and height of the union are within the range([0, INT_MAX]).
 * @pre The rectangle must be normalized.
 */
inline bool Rect::unite(const Point& point)
{
    int xOffset = INT_MIN - EGE_TEMP_MIN(x, point.x);
    int yOffset = INT_MIN - EGE_TEMP_MIN(y, point.y);

    Rect r(x + xOffset, y + yOffset, width, height);
    Point p(point.x + xOffset, point.y + yOffset);

    int left   = INT_MIN;
    int top    = INT_MIN;
    int right  = EGE_TEMP_MAX(this->right(), p.x);
    int bottom = EGE_TEMP_MAX(this->bottom(), p.y);

    set(left - xOffset, top - yOffset, right - left, bottom - top);

    return (INT_MAX - r.width  >= r.x)
        && (INT_MAX - r.height >= r.y)
        && ((unsigned)right - left <= INT_MAX)
        && ((unsigned)bottom - top <= INT_MAX);
}

inline bool Rect::unite(const Point points[], int length)
{
    if (length <= 0)
        return true;

    Bound bound = getBounds(points, length);

    return unite(Rect(bound)) && !bound.isOutOfRange();
}

inline void Rect::clip(int xMin, int xMax, int yMin, int yMax)
{
    clipX(xMin, xMax);
    clipY(yMin, yMax);
}

inline void Rect::clipX(int xMin, int xMax)
{
    clipByLimits(x, width, xMin, xMax);
}

inline void Rect::clipY(int yMin, int yMax)
{
    clipByLimits(y, height, yMin, yMax);
}

inline void Rect::clip()
{
    clipX();
    clipY();
}

inline void Rect::clipX()
{
    if (width >= 0) {
        if (INT_MAX - width < x)
            width = INT_MAX - x;
    } else {
        if (INT_MIN - width > x)
            width = INT_MIN - x;
    }
}

inline void Rect::clipY()
{
    if (height >= 0) {
        if (INT_MAX - height < y)
            height = INT_MAX - y;
    } else {
        if (INT_MIN - height > y)
            height = INT_MIN - y;
    }
}

inline bool Rect::clipByLimits(int& x,  int& length, int minval, int maxval)
{
    if (minval > maxval)
        return false;

    if (length == 0) {
        return (minval <= x) && (x <= maxval);
    }

    int left, right;

    if (length > 0) {
        left  = x;
        right = (INT_MAX - (length - 1) < x) ? INT_MAX : (x + length - 1);
    } else {
        left  = (INT_MIN - (length + 1) > x) ? INT_MIN : (x + length + 1);
        right = x;
    }

    if ((left > maxval) || (right < maxval))
        return false;

    int clipLeft  = EGE_TEMP_MAX(left,  minval);
    int clipRight = EGE_TEMP_MIN(right, maxval);

    if (length > 0) {
        x = clipLeft;
        length = clipRight - clipLeft + 1;
    } else {
        x = clipRight;
        length = clipLeft - clipRight - 1;
    }

    return true;
}

//------------------------------------------------------------------------------

inline bool operator== (const Rect& a, const Rect& b)
{
    return (a.x == b.x) && (a.y == b.y) && (a.width == b.width) && (a.height == b.height);
}

inline bool operator!= (const Rect& a, const Rect& b)
{
    return !(a == b);
}

inline Rect clip(const Rect& rect)
{
    Rect r(rect);
    r.clip();
    return r;
}

inline Rect offset(const Rect& rect, int dx, int dy)
{
    return Rect(rect.x + dx, rect.y + dy, rect.width, rect.height, false);
}

inline Rect normalize(const Rect& rect)
{
    Rect r(rect);
    r.normalize();
    return r;
}


inline Rect intersect(const Rect& a, const Rect& b)
{
    Rect c(a);
    c.intersect(b);
    return c;
}

inline Rect unite(const Rect& a, const Rect& b)
{
    Rect c(a);
    c.unite(b);
    return c;
}

inline Bound getBounds(const Point& a, const Point& b)
{
    int left, top, right, bottom;
    if (a.x <= b.x) {
        left  = a.x;
        right = b.x;
    } else {
        left  = b.x;
        right = a.x;
    }

    if (a.y <= b.y) {
        top = a.y;
        bottom = b.y;
    } else {
        top = b.y;
        bottom = a.y;
    }

    return Bound(left, top, right, bottom, false);
}

//------------------------------------------------------------------------------

}

#undef EGE_TEMP_MIN
#undef EGE_TEMP_MAX
#undef EGE_TEMP_MIDPOINT_INT
#undef EGE_TEMP_DIFF_UINT
#undef EGE_TEMP_ROUND
