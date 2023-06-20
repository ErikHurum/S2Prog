#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER


template <class T>
class CircularBuffer
{
public:
    CircularBuffer(int capacity)
    {
        arraySize = capacity;
        _array = new T[arraySize];
        cursor = arraySize-1;
    }
    
    
    ~CircularBuffer()
    {

    }
    

    inline void add(T item)
    {
        cursor = getNextCursor(cursor);
        _array[cursor] = item;
    }


    inline T getItem(unsigned cursor)
    {
        if (cursor >= arraySize) 
#ifdef ANWIN      
            throw out_of_range("bad cursor");
#else
            cursor = 0;        
#endif
        return _array[cursor];
    }
    

    inline unsigned getCursor(void)
    {
        return cursor;
    }
    

    inline unsigned getNextCursor(unsigned cursor)
    {
        cursor++;
        if (cursor >= arraySize)
            cursor = 0;

        return cursor;
    }


    inline unsigned getPrevCursor(unsigned cursor)
    {
        cursor--;
        if (cursor >= arraySize)
            cursor = arraySize - 1;

        return cursor;
    }

    
private:
    T* _array;
    unsigned cursor;
    unsigned arraySize;
};

#endif
