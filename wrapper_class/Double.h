#ifndef DOUBLE_H
#define DOUBLE_H

class Double {


    public:

	double value;
	Double();
	Double(double val);
	Double(const Double &other);
	Double& operator+= (const Double &val);
	Double& operator* (Double &t);

};


inline
Double::Double() : value(0.0)
{}


inline
Double::Double(double val) 
{ 
    value = val;
}


inline
Double::Double (const Double &other)
{
    value = other.value;
}


inline
Double&
Double::operator+= (const Double &val)
{
    value += val.value;
    return *this;
}


inline
Double&
Double::operator* (Double &t)
{
    value *= t.value;
    return *this;
}

#endif
