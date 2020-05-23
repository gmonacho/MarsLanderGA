#ifndef VEC_H
# define VEC_H
 
template <typename T>
class Vec
{
private:
    T   vx;
    T   vy;

public:
    Vec(const T& vx = 0, const T& vy = 0);

    ~Vec() = default;

    const T& getVx() const;
    const T& getVy() const;

    Vec<T>& setVx(const T& vx);
    Vec<T>& setVy(const T& vy);

    Vec<T>& operator+=(const Vec<T>& vec);
};

template<typename T>
Vec<T>::Vec(const T& vx, const T& vy)
{
	this->vx = vx;
	this->vy = vy;
}

template<typename T>
inline const T& Vec<T>::getVx() const
{
	return (this->vx);
}

template<typename T>
inline const T& Vec<T>::getVy() const
{
	return (this->vy);
}

template<typename T>
Vec<T>& Vec<T>::setVx(const T& vx)
{
	this->vx = vx;
	return (*this);
}

template<typename T>
Vec<T>& Vec<T>::setVy(const T& vy)
{
	this->vy = vy;
	return (*this);
}
template<typename T>
Vec<T>& Vec<T>::operator+=(const Vec<T>& vec)
{
	this->vx += vec.vx;
	this->vy += vec.vy;
	return (*this);
}

#endif

