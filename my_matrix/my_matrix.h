#include <iostream>
#include <stdexcept>

template <typename T>
class MyMatrix
{
    template <typename U>
    friend std::ostream & operator<<(std::ostream &out, const MyMatrix<U> &matrix);
public:
    MyMatrix(int row,int col);
    MyMatrix(const MyMatrix<T> &my_matrix);
    ~MyMatrix();
    T & operator()(int x,int y) const;

    MyMatrix<T> operator+(const MyMatrix<T> &matrix) const;
    MyMatrix<T> & operator+=(const MyMatrix<T> &matrix);
    MyMatrix<T> operator+(const T &t) const;
    MyMatrix<T> & operator+=(const T &t) ;

    MyMatrix<T> operator-(const MyMatrix<T> &matrix) const;
    MyMatrix<T> & operator-=(const MyMatrix<T> &matrix);
    MyMatrix<T> operator-(const T &t) const;
    MyMatrix<T> &operator-=(const T &t);

    MyMatrix<T> operator*(const MyMatrix<T> &matrix) const;
    MyMatrix<T> &operator*=(const MyMatrix<T> &matrix);
    MyMatrix<T> operator*(const T &t) const;
    MyMatrix<T> &operator*=(const T &t);

    MyMatrix<T> Transpose() const;

    MyMatrix<T>& operator=(const MyMatrix<T> &matrix);

//    bool operator==(const MyMatrix<T> &matrix);
//    bool operator!=(const MyMatrix<T> &matrix);
private:
    int col_;
    int row_;
    T* ptr_;
};

template <typename T>
std::ostream & operator<<(std::ostream &out,const MyMatrix<T> &matrix);

template <typename T>
std::ostream & operator<<(std::ostream &out,const MyMatrix<T> &matrix)
{
    for(int i = 0; i < matrix.row_;++i)
    {
        for(int j = 0;j < matrix.col_;++j)
        {
            out << matrix.ptr_[i*matrix.col_+j] << "  ";
        }
        out << std::endl;
    }
    return out;
}
template<typename T>
MyMatrix<T>::MyMatrix(int row,int col)
{
    if(row <=0 || col <= 0)
        throw std::invalid_argument("参数非法");
    col_ = col;
    row_ = row;
    ptr_ = new T[col_*row_];
}

template<typename T>
MyMatrix<T>::MyMatrix(const MyMatrix<T> &my_matrix)
{
    col_ = my_matrix.col_;
    row_ = my_matrix.row_;
    ptr_ = new T[col_*row_];
    std::copy(my_matrix.ptr_,my_matrix.ptr_+col_*row_,ptr_);
}

template<typename T>
MyMatrix<T>::~MyMatrix()
{
    delete [] ptr_;
}

template<typename T>
T &MyMatrix<T>::operator()(int x,int y) const
{
    if(x < 1 || y < 1 || x > row_ || y > col_)
        throw std::invalid_argument("参数不合法");
    return ptr_[(x-1)*col_ +(y-1)];
}

template<typename T>
MyMatrix<T> MyMatrix<T>::operator+(const MyMatrix<T>& matrix) const
{
    if(matrix.row_ != row_ || matrix.col_ != col_)
        throw std::invalid_argument("矩阵大小不一致 无法相加");
    MyMatrix<T> temp_matrix(row_,col_);
    for(int i = 0; i < row_*col_;++i)
    {
        temp_matrix.ptr_[i] = this->ptr_[i] + matrix.ptr_[i];
    }
    return temp_matrix;
}

template<typename T>
MyMatrix<T> & MyMatrix<T>::operator+=(const MyMatrix<T> &matrix)
{
    if(matrix.row_ != row_ || matrix.col_ != col_)
        throw std::invalid_argument("矩阵大小不一致 无法相加");
    for(int i = 0;i < row_*col_;++i)
        ptr_[i] += matrix.ptr_[i];
    return *this;    
}

template<typename T>
MyMatrix<T> MyMatrix<T>::operator+(const T &t) const
{
    MyMatrix<T> temp_matrix(row_,col_);
    for(int i = 0;i < row_*col_;++i)
        temp_matrix.ptr_[i] = ptr_[i] + t;
    return temp_matrix;
}

template<typename T>
MyMatrix<T> & MyMatrix<T>::operator+=(const T &t)
{
    for(int i = 0;i < row_*col_;++i)
        ptr_[i] += t;
    return *this;
}
template<typename T>
MyMatrix<T> MyMatrix<T>::operator-(const MyMatrix<T> &matrix) const
{
    if(matrix.row_ != row_ || matrix.col_ != col_)
        throw std::invalid_argument("矩阵大小不一致 无法相减");
    MyMatrix<T> temp_matrix(row_,col_);
    for(int i = 0;i < row_*col_;++i)
        temp_matrix.ptr_[i] = this->ptr_[i] + matrix.ptr_[i];
    return temp_matrix;
}

template<typename T>
MyMatrix<T> &  MyMatrix<T>::operator-=(const MyMatrix<T> &matrix)
{
    MyMatrix<T> temp_matrix(*this);
    *this = temp_matrix-matrix;
    return *this;
}

template<typename T>    
MyMatrix<T> MyMatrix<T>::operator-(const T &t) const
{
    t = -t;
    MyMatrix<T> temp_matrix(row_,col_);
    temp_matrix += t;
    return temp_matrix;    
}

template<typename T>
MyMatrix<T> & MyMatrix<T>::operator-=(const T &t)
{
    t = -t;
    *this += t;
    return *this;
}
template<typename T>
MyMatrix<T> MyMatrix<T>::operator*(const MyMatrix<T> &matrix) const
{
    if( col_ != matrix.row_)
        throw std::invalid_argument("不符合乘法条件");
    MyMatrix<T> temp_matrix(row_,matrix.col_);

    int ct = 0,cm = 0,cw = 0;

    for(int i = 0;i < row_;++i)
    {
        for(int j = 0;j < matrix.col_;++j)
        {
            T sum = ptr_[ct]*matrix.ptr_[cm];
            for(int k = 1;k < col_;++k)
            {
                ct++;
                cm += matrix.col_;
                sum += ptr_[ct] * matrix.ptr_[cm];
            }
            temp_matrix.ptr_[cw++] = sum;

            ct -= col_-1;
            cm = j;
        }
        ct += col_;
        cm = 0;
    }
    return temp_matrix;
}

template<typename T>
MyMatrix<T> & MyMatrix<T>::operator*=(const MyMatrix<T> &matrix)
{
    MyMatrix<T> temp_matrix(*this);
    *this = temp_matrix * matrix;
    return *this;
}

template<typename T>
MyMatrix<T> MyMatrix<T>::operator*(const T &t) const
{
    MyMatrix<T> temp_matrix(row_,col_);
    for(int i = 0; i < row_*col_;++i)
        temp_matrix.ptr_[i] = ptr_[i] * t;
    return temp_matrix;
}

template<typename T>
MyMatrix<T> &MyMatrix<T>::operator*=(const T &t)
{
    for(int i = 0;i < row_*col_;++i)
        ptr_[i] *= t;
    return *this;
}

template<typename T>
MyMatrix<T> MyMatrix<T>::Transpose() const
{
    MyMatrix<T> temp_matrix(col_,row_);
    for(int i =1;i <=row_;++i)
    {
        for(int j = 1;j <= col_;++j)
            temp_matrix(j,i) = (*this)(i,j);
    }
    std::cout << "111" <<std::endl;
    return temp_matrix;
}

template<typename T>
MyMatrix<T>& MyMatrix<T>::operator=(const MyMatrix<T>& matrix)
{
    if(this != &matrix)
    {
        delete [] ptr_;
        row_ = matrix.row_;
        col_ = matrix.col_;
        ptr_ = new T[row_*col_];
        std::copy(matrix.ptr_,matrix.ptr_+matrix.row_*matrix.col_,ptr_);
    }
    return *this;
}


