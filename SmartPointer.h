class RC
{//Reference counter class
private:
    int count;
public:
    void AddRef()
    {
        count++;
    }
    int Release()
    {
        return --count;
    }
    int getCount()const{ return count; }
};

template<typename T> class SP
{
private:
    T* pData;       //encapsulated data pointer
    RC* reference;  //Reference counter
public:
    SP(); //default constructor

    SP(T* pValue);

    SP(const T &pValue);

    SP(const SP<T> & sp); //copy constructor
    
    ~SP(); //destructor
    
    T& operator*()const{ return *pData; } //operator * overload
    
    T* operator ->() { return pData; } // operator -> overload

    SP<T> &operator = (const SP<T>&sp) //copy assignment operator=
    {
        if(this != &sp)//Avoid self assignment
        {
            if(reference->Release() == 0)
            {//Decrement the old ref counter
                delete pData;
                delete reference;
            }
            //Copy the data and ref pointer
            pData = sp.pData;
            reference = sp.reference;
            //Increment reference
            reference->AddRef();
        }
        return *this;
    }
};
