#pragma once

template <typename T, size_t W, size_t... SW>
struct Swizzle
{
    T v[sizeof...(SW)];
    
    template <typename T2, size_t W2, size_t... SW2>
    Swizzle<T, W, SW...>& operator=(const Swizzle<T2, W2, SW2...>& lhs)
    {
        static_assert(W == W2, "error: assigning swizzle of different dimensions");
        std::vector<size_t> i1 = {SW...};
        std::vector<size_t> i2 = {SW2...};
        for(size_t x = 0; x < W; ++x)
            v[i1[x]] = lhs.v[i2[x]];
        
        return *this;
    }
    
    template <size_t N, typename T2>
    Swizzle<T, W, SW...>& operator=(const Vec<N, T2>& lhs)
    {
        static_assert(W == N, "error: assigning vector to swizzle of different dimensions");
        std::vector<size_t> i1 = {SW...};
        for(size_t x = 0; x < W; ++x)
            v[i1[x]] = lhs.v[x];
    }
    
    operator Vec<W, T> () const
    {
        Vec<W, T> vec;
        std::vector<size_t> i1 = {SW...};
        for(size_t x = 0; x < W; ++x)
            vec[x] = v[i1[x]];
        return vec;
    }
    
    template <typename T2, size_t W2, size_t... SW2>
    Vec<W, T> operator+(const Swizzle<T2, W2, SW2...>& rhs) const
    {
        static_assert(W == W2, "error: performing arithmetic on swizzles of different sizes");
        return Vec<W, T>(Vec<W, T>(*this) + Vec<W, T>(rhs));
    }
    
    template <typename T2, size_t W2, size_t... SW2>
    Vec<W, T> operator-(const Swizzle<T2, W2, SW2...>& rhs) const
    {
        static_assert(W == W2, "error: performing arithmetic on swizzles of different sizes");
        return Vec<W, T>(Vec<W, T>(*this) - Vec<W, T>(rhs));
    }
    
    template <typename T2, size_t W2, size_t... SW2>
    Vec<W, T> operator/(const Swizzle<T2, W2, SW2...>& rhs) const
    {
        static_assert(W == W2, "error: performing arithmetic on swizzles of different sizes");
        return Vec<W, T>(Vec<W, T>(*this) / Vec<W, T>(rhs));
    }
    
    template <typename T2, size_t W2, size_t... SW2>
    Vec<W, T> operator*(const Swizzle<T2, W2, SW2...>& rhs) const
    {
        static_assert(W == W2, "error: performing arithmetic on swizzles of different sizes");
        return Vec<W, T>(Vec<W, T>(*this) * Vec<W, T>(rhs));
    }
    
    template <typename T2, size_t W2, size_t... SW2>
    Vec<W, T>& operator+=(const Swizzle<T2, W2, SW2...>& rhs)
    {
        static_assert(W == W2, "error: performing arithmetic on swizzles of different sizes");
        *this = Vec<W, T>(*this) += Vec<W, T>(rhs);
        return Vec<W, T>(*this);
    }
    
    template <typename T2, size_t W2, size_t... SW2>
    Vec<W, T>& operator-=(const Swizzle<T2, W2, SW2...>& rhs)
    {
        static_assert(W == W2, "error: performing arithmetic on swizzles of different sizes");
        *this = Vec<W, T>(*this) -= Vec<W, T>(rhs);
        return Vec<W, T>(*this);
    }
    
    template <typename T2, size_t W2, size_t... SW2>
    Vec<W, T>& operator/=(const Swizzle<T2, W2, SW2...>& rhs)
    {
        static_assert(W == W2, "error: performing arithmetic on swizzles of different sizes");
        *this = Vec<W, T>(*this) /= Vec<W, T>(rhs);
        return Vec<W, T>(*this);
    }
    
    template <typename T2, size_t W2, size_t... SW2>
    Vec<W, T>& operator*=(const Swizzle<T2, W2, SW2...>& rhs)
    {
        static_assert(W == W2, "error: performing arithmetic on swizzles of different sizes");
        *this = Vec<W, T>(*this) *= Vec<W, T>(rhs);
        return Vec<W, T>(*this);
    }
};

// unary minus
template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator-(const Swizzle<T, N, SW...>& lhs)
{
    return -Vec<N, T>(lhs);
}

// add
template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator+(const Vec<N, T>& rhs, const Swizzle<T, N, SW...>& lhs)
{
    return Vec<N, T>(lhs) + Vec<N, T>(rhs);
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator+(const Swizzle<T, N, SW...>& lhs, const Vec<N, T>& rhs)
{
    return Vec<N, T>(lhs) + Vec<N, T>(rhs);
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator+(const Swizzle<T, N, SW...>& lhs, const T& rhs)
{
    return Vec<N, T>(lhs) + rhs;
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T>& operator+=(const Swizzle<T, N, SW...>& lhs, const Vec<N, T>& rhs)
{
    lhs = Vec<N, T>(lhs) + Vec<N, T>(rhs);
    return lhs;
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T>& operator+=(const Swizzle<T, N, SW...>& lhs, const T& rhs)
{
    lhs = Vec<N, T>(lhs) + rhs;
    return lhs;
}

// sub
template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator-(const Swizzle<T, N, SW...>& lhs, const Vec<N, T>& rhs)
{
    return Vec<N, T>(lhs) - Vec<N, T>(rhs);
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator-(const Vec<N, T>& rhs, const Swizzle<T, N, SW...>& lhs)
{
    return Vec<N, T>(lhs) - Vec<N, T>(rhs);
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator-(const Swizzle<T, N, SW...>& lhs, const T& rhs)
{
    return Vec<N, T>(lhs) - rhs;
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T>& operator-=(const Swizzle<T, N, SW...>& lhs, const Vec<N, T>& rhs)
{
    lhs = Vec<N, T>(lhs) - Vec<N, T>(rhs);
    return lhs;
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T>& operator-=(const Swizzle<T, N, SW...>& lhs, const T& rhs)
{
    lhs = Vec<N, T>(lhs) - rhs;
    return lhs;
}

// divide
template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator/(const Swizzle<T, N, SW...>& lhs, const Vec<N, T>& rhs)
{
    return Vec<N, T>(lhs) / Vec<N, T>(rhs);
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator/(const Vec<N, T>& rhs, const Swizzle<T, N, SW...>& lhs)
{
    return Vec<N, T>(lhs) / Vec<N, T>(rhs);
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator/(const Swizzle<T, N, SW...>& lhs, const T& rhs)
{
    return Vec<N, T>(lhs) / rhs;
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T>& operator/=(const Swizzle<T, N, SW...>& lhs, const Vec<N, T>& rhs)
{
    lhs = Vec<N, T>(lhs) / Vec<N, T>(rhs);
    return lhs;
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T>& operator/=(const Swizzle<T, N, SW...>& lhs, const T& rhs)
{
    lhs = Vec<N, T>(lhs) / rhs;
    return lhs;
}

// multiply
template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator*(const Swizzle<T, N, SW...>& lhs, const Vec<N, T>& rhs)
{
    return Vec<N, T>(lhs) * Vec<N, T>(rhs);
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator*(const Vec<N, T>& rhs, const Swizzle<T, N, SW...>& lhs)
{
    return Vec<N, T>(lhs) * Vec<N, T>(rhs);
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T> operator*(const Swizzle<T, N, SW...>& lhs, const T& rhs)
{
    return Vec<N, T>(lhs) * rhs;
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T>& operator*=(const Swizzle<T, N, SW...>& lhs, const Vec<N, T>& rhs)
{
    lhs = Vec<N, T>(lhs) * Vec<N, T>(rhs);
    return lhs;
}

template <size_t N, typename T, size_t ...SW>
Vec<N, T>& operator*=(const Swizzle<T, N, SW...>& lhs, const T& rhs)
{
    lhs = Vec<N, T>(lhs) * rhs;
    return lhs;
}

// swizzle permutations

// v2 swizzles
#define swizzle_v2      \
Swizzle<T, 2, 0, 0> xx; \
Swizzle<T, 2, 0, 1> xy; \
Swizzle<T, 2, 1, 0> yx; \
Swizzle<T, 2, 1, 1> yy;

// v3 swizzles
#define swizzle_v3                  \
Swizzle<T, 2, 0, 0, (size_t)-1> xx; \
Swizzle<T, 2, 0, 2, (size_t)-1> xz; \
Swizzle<T, 2, 0, 3, (size_t)-1> xw; \
Swizzle<T, 2, 1, 0, (size_t)-1> yx; \
Swizzle<T, 2, 1, 1, (size_t)-1> yy; \
Swizzle<T, 2, 1, 2, (size_t)-1> yz; \
Swizzle<T, 2, 1, 3, (size_t)-1> yw; \
Swizzle<T, 2, 2, 0, (size_t)-1> zx; \
Swizzle<T, 2, 2, 1, (size_t)-1> zy; \
Swizzle<T, 2, 2, 2, (size_t)-1> zz; \
Swizzle<T, 2, 2, 3, (size_t)-1> zw; \
Swizzle<T, 2, 3, 0, (size_t)-1> wx; \
Swizzle<T, 2, 3, 1, (size_t)-1> wy; \
Swizzle<T, 2, 3, 2, (size_t)-1> wz; \
Swizzle<T, 2, 3, 3, (size_t)-1> ww; \
Swizzle<T, 3, 0, 0, 0> xxx; \
Swizzle<T, 3, 0, 0, 1> xxy; \
Swizzle<T, 3, 0, 0, 2> xxz; \
Swizzle<T, 3, 0, 1, 0> xyx; \
Swizzle<T, 3, 0, 1, 1> xyy; \
Swizzle<T, 3, 0, 1, 2> xyz; \
Swizzle<T, 3, 0, 2, 0> xzx; \
Swizzle<T, 3, 0, 2, 1> xzy; \
Swizzle<T, 3, 0, 2, 2> xzz; \
Swizzle<T, 3, 1, 0, 0> yxx; \
Swizzle<T, 3, 1, 0, 1> yxy; \
Swizzle<T, 3, 1, 0, 2> yxz; \
Swizzle<T, 3, 1, 1, 0> yyx; \
Swizzle<T, 3, 1, 1, 1> yyy; \
Swizzle<T, 3, 1, 1, 2> yyz; \
Swizzle<T, 3, 1, 2, 0> yzx; \
Swizzle<T, 3, 1, 2, 1> yzy; \
Swizzle<T, 3, 1, 2, 2> yzz; \
Swizzle<T, 3, 2, 0, 0> zxx; \
Swizzle<T, 3, 2, 0, 1> zxy; \
Swizzle<T, 3, 2, 0, 2> zxz; \
Swizzle<T, 3, 2, 1, 0> zyx; \
Swizzle<T, 3, 2, 1, 1> zyy; \
Swizzle<T, 3, 2, 1, 2> zyz; \
Swizzle<T, 3, 2, 2, 0> zzx; \
Swizzle<T, 3, 2, 2, 1> zzy; \
Swizzle<T, 3, 2, 2, 2> zzz;

// v4 swizzles
#define swizzle_v4                              \
Swizzle<T, 2, 0, 0, size_t(-1), size_t(-1)> xx; \
Swizzle<T, 2, 0, 2, size_t(-1), size_t(-1)> xz; \
Swizzle<T, 2, 0, 3, size_t(-1), size_t(-1)> xw; \
Swizzle<T, 2, 1, 0, size_t(-1), size_t(-1)> yx; \
Swizzle<T, 2, 1, 1, size_t(-1), size_t(-1)> yy; \
Swizzle<T, 2, 1, 2, size_t(-1), size_t(-1)> yz; \
Swizzle<T, 2, 1, 3, size_t(-1), size_t(-1)> yw; \
Swizzle<T, 2, 2, 0, size_t(-1), size_t(-1)> zx; \
Swizzle<T, 2, 2, 1, size_t(-1), size_t(-1)> zy; \
Swizzle<T, 2, 2, 2, size_t(-1), size_t(-1)> zz; \
Swizzle<T, 2, 2, 3, size_t(-1), size_t(-1)> zw; \
Swizzle<T, 2, 3, 0, size_t(-1), size_t(-1)> wx; \
Swizzle<T, 2, 3, 1, size_t(-1), size_t(-1)> wy; \
Swizzle<T, 2, 3, 2, size_t(-1), size_t(-1)> wz; \
Swizzle<T, 2, 3, 3, size_t(-1), size_t(-1)> ww; \
Swizzle<T, 3, 0, 0, 0, size_t(-1)> xxx; \
Swizzle<T, 3, 0, 0, 1, size_t(-1)> xxy; \
Swizzle<T, 3, 0, 0, 2, size_t(-1)> xxz; \
Swizzle<T, 3, 0, 0, 3, size_t(-1)> xxw; \
Swizzle<T, 3, 0, 1, 0, size_t(-1)> xyx; \
Swizzle<T, 3, 0, 1, 1, size_t(-1)> xyy; \
Swizzle<T, 3, 0, 1, 3, size_t(-1)> xyw; \
Swizzle<T, 3, 0, 2, 0, size_t(-1)> xzx; \
Swizzle<T, 3, 0, 2, 1, size_t(-1)> xzy; \
Swizzle<T, 3, 0, 2, 2, size_t(-1)> xzz; \
Swizzle<T, 3, 0, 2, 3, size_t(-1)> xzw; \
Swizzle<T, 3, 0, 3, 0, size_t(-1)> xwx; \
Swizzle<T, 3, 0, 3, 1, size_t(-1)> xwy; \
Swizzle<T, 3, 0, 3, 2, size_t(-1)> xwz; \
Swizzle<T, 3, 0, 3, 3, size_t(-1)> xww; \
Swizzle<T, 3, 1, 0, 0, size_t(-1)> yxx; \
Swizzle<T, 3, 1, 0, 1, size_t(-1)> yxy; \
Swizzle<T, 3, 1, 0, 2, size_t(-1)> yxz; \
Swizzle<T, 3, 1, 0, 3, size_t(-1)> yxw; \
Swizzle<T, 3, 1, 1, 0, size_t(-1)> yyx; \
Swizzle<T, 3, 1, 1, 1, size_t(-1)> yyy; \
Swizzle<T, 3, 1, 1, 2, size_t(-1)> yyz; \
Swizzle<T, 3, 1, 1, 3, size_t(-1)> yyw; \
Swizzle<T, 3, 1, 2, 0, size_t(-1)> yzx; \
Swizzle<T, 3, 1, 2, 1, size_t(-1)> yzy; \
Swizzle<T, 3, 1, 2, 2, size_t(-1)> yzz; \
Swizzle<T, 3, 1, 2, 3, size_t(-1)> yzw; \
Swizzle<T, 3, 1, 3, 0, size_t(-1)> ywx; \
Swizzle<T, 3, 1, 3, 1, size_t(-1)> ywy; \
Swizzle<T, 3, 1, 3, 2, size_t(-1)> ywz; \
Swizzle<T, 3, 1, 3, 3, size_t(-1)> yww; \
Swizzle<T, 3, 2, 0, 0, size_t(-1)> zxx; \
Swizzle<T, 3, 2, 0, 1, size_t(-1)> zxy; \
Swizzle<T, 3, 2, 0, 2, size_t(-1)> zxz; \
Swizzle<T, 3, 2, 0, 3, size_t(-1)> zxw; \
Swizzle<T, 3, 2, 1, 0, size_t(-1)> zyx; \
Swizzle<T, 3, 2, 1, 1, size_t(-1)> zyy; \
Swizzle<T, 3, 2, 1, 2, size_t(-1)> zyz; \
Swizzle<T, 3, 2, 1, 3, size_t(-1)> zyw; \
Swizzle<T, 3, 2, 2, 0, size_t(-1)> zzx; \
Swizzle<T, 3, 2, 2, 1, size_t(-1)> zzy; \
Swizzle<T, 3, 2, 2, 2, size_t(-1)> zzz; \
Swizzle<T, 3, 2, 2, 3, size_t(-1)> zzw; \
Swizzle<T, 3, 2, 3, 0, size_t(-1)> zwx; \
Swizzle<T, 3, 2, 3, 1, size_t(-1)> zwy; \
Swizzle<T, 3, 2, 3, 2, size_t(-1)> zwz; \
Swizzle<T, 3, 2, 3, 3, size_t(-1)> zww; \
Swizzle<T, 3, 3, 0, 0, size_t(-1)> wxx; \
Swizzle<T, 3, 3, 0, 1, size_t(-1)> wxy; \
Swizzle<T, 3, 3, 0, 2, size_t(-1)> wxz; \
Swizzle<T, 3, 3, 0, 3, size_t(-1)> wxw; \
Swizzle<T, 3, 3, 1, 0, size_t(-1)> wyx; \
Swizzle<T, 3, 3, 1, 1, size_t(-1)> wyy; \
Swizzle<T, 3, 3, 1, 2, size_t(-1)> wyz; \
Swizzle<T, 3, 3, 1, 3, size_t(-1)> wyw; \
Swizzle<T, 3, 3, 2, 0, size_t(-1)> wzx; \
Swizzle<T, 3, 3, 2, 1, size_t(-1)> wzy; \
Swizzle<T, 3, 3, 2, 2, size_t(-1)> wzz; \
Swizzle<T, 3, 3, 2, 3, size_t(-1)> wzw; \
Swizzle<T, 3, 3, 3, 0, size_t(-1)> wwx; \
Swizzle<T, 3, 3, 3, 1, size_t(-1)> wwy; \
Swizzle<T, 3, 3, 3, 2, size_t(-1)> wwz; \
Swizzle<T, 3, 3, 3, 3, size_t(-1)> www; \
Swizzle<T, 4, 0, 0, 0, 0> xxxx; \
Swizzle<T, 4, 0, 0, 0, 1> xxxy; \
Swizzle<T, 4, 0, 0, 0, 2> xxxz; \
Swizzle<T, 4, 0, 0, 0, 3> xxxw; \
Swizzle<T, 4, 0, 0, 1, 0> xxyx; \
Swizzle<T, 4, 0, 0, 1, 1> xxyy; \
Swizzle<T, 4, 0, 0, 1, 2> xxyz; \
Swizzle<T, 4, 0, 0, 1, 3> xxyw; \
Swizzle<T, 4, 0, 0, 2, 0> xxzx; \
Swizzle<T, 4, 0, 0, 2, 1> xxzy; \
Swizzle<T, 4, 0, 0, 2, 2> xxzz; \
Swizzle<T, 4, 0, 0, 2, 3> xxzw; \
Swizzle<T, 4, 0, 0, 3, 0> xxwx; \
Swizzle<T, 4, 0, 0, 3, 1> xxwy; \
Swizzle<T, 4, 0, 0, 3, 2> xxwz; \
Swizzle<T, 4, 0, 0, 3, 3> xxww; \
Swizzle<T, 4, 0, 1, 0, 0> xyxx; \
Swizzle<T, 4, 0, 1, 0, 1> xyxy; \
Swizzle<T, 4, 0, 1, 0, 2> xyxz; \
Swizzle<T, 4, 0, 1, 0, 3> xyxw; \
Swizzle<T, 4, 0, 1, 1, 0> xyyx; \
Swizzle<T, 4, 0, 1, 1, 1> xyyy; \
Swizzle<T, 4, 0, 1, 1, 2> xyyz; \
Swizzle<T, 4, 0, 1, 1, 3> xyyw; \
Swizzle<T, 4, 0, 1, 2, 0> xyzx; \
Swizzle<T, 4, 0, 1, 2, 1> xyzy; \
Swizzle<T, 4, 0, 1, 2, 2> xyzz; \
Swizzle<T, 4, 0, 1, 2, 3> xyzw; \
Swizzle<T, 4, 0, 1, 3, 0> xywx; \
Swizzle<T, 4, 0, 1, 3, 1> xywy; \
Swizzle<T, 4, 0, 1, 3, 2> xywz; \
Swizzle<T, 4, 0, 1, 3, 3> xyww; \
Swizzle<T, 4, 0, 2, 0, 0> xzxx; \
Swizzle<T, 4, 0, 2, 0, 1> xzxy; \
Swizzle<T, 4, 0, 2, 0, 2> xzxz; \
Swizzle<T, 4, 0, 2, 0, 3> xzxw; \
Swizzle<T, 4, 0, 2, 1, 0> xzyx; \
Swizzle<T, 4, 0, 2, 1, 1> xzyy; \
Swizzle<T, 4, 0, 2, 1, 2> xzyz; \
Swizzle<T, 4, 0, 2, 1, 3> xzyw; \
Swizzle<T, 4, 0, 2, 2, 0> xzzx; \
Swizzle<T, 4, 0, 2, 2, 1> xzzy; \
Swizzle<T, 4, 0, 2, 2, 2> xzzz; \
Swizzle<T, 4, 0, 2, 2, 3> xzzw; \
Swizzle<T, 4, 0, 2, 3, 0> xzwx; \
Swizzle<T, 4, 0, 2, 3, 1> xzwy; \
Swizzle<T, 4, 0, 2, 3, 2> xzwz; \
Swizzle<T, 4, 0, 2, 3, 3> xzww; \
Swizzle<T, 4, 0, 3, 0, 0> xwxx; \
Swizzle<T, 4, 0, 3, 0, 1> xwxy; \
Swizzle<T, 4, 0, 3, 0, 2> xwxz; \
Swizzle<T, 4, 0, 3, 0, 3> xwxw; \
Swizzle<T, 4, 0, 3, 1, 0> xwyx; \
Swizzle<T, 4, 0, 3, 1, 1> xwyy; \
Swizzle<T, 4, 0, 3, 1, 2> xwyz; \
Swizzle<T, 4, 0, 3, 1, 3> xwyw; \
Swizzle<T, 4, 0, 3, 2, 0> xwzx; \
Swizzle<T, 4, 0, 3, 2, 1> xwzy; \
Swizzle<T, 4, 0, 3, 2, 2> xwzz; \
Swizzle<T, 4, 0, 3, 2, 3> xwzw; \
Swizzle<T, 4, 0, 3, 3, 0> xwwx; \
Swizzle<T, 4, 0, 3, 3, 1> xwwy; \
Swizzle<T, 4, 0, 3, 3, 2> xwwz; \
Swizzle<T, 4, 0, 3, 3, 3> xwww; \
Swizzle<T, 4, 1, 0, 0, 0> yxxx; \
Swizzle<T, 4, 1, 0, 0, 1> yxxy; \
Swizzle<T, 4, 1, 0, 0, 2> yxxz; \
Swizzle<T, 4, 1, 0, 0, 3> yxxw; \
Swizzle<T, 4, 1, 0, 1, 0> yxyx; \
Swizzle<T, 4, 1, 0, 1, 1> yxyy; \
Swizzle<T, 4, 1, 0, 1, 2> yxyz; \
Swizzle<T, 4, 1, 0, 1, 3> yxyw; \
Swizzle<T, 4, 1, 0, 2, 0> yxzx; \
Swizzle<T, 4, 1, 0, 2, 1> yxzy; \
Swizzle<T, 4, 1, 0, 2, 2> yxzz; \
Swizzle<T, 4, 1, 0, 2, 3> yxzw; \
Swizzle<T, 4, 1, 0, 3, 0> yxwx; \
Swizzle<T, 4, 1, 0, 3, 1> yxwy; \
Swizzle<T, 4, 1, 0, 3, 2> yxwz; \
Swizzle<T, 4, 1, 0, 3, 3> yxww; \
Swizzle<T, 4, 1, 1, 0, 0> yyxx; \
Swizzle<T, 4, 1, 1, 0, 1> yyxy; \
Swizzle<T, 4, 1, 1, 0, 2> yyxz; \
Swizzle<T, 4, 1, 1, 0, 3> yyxw; \
Swizzle<T, 4, 1, 1, 1, 0> yyyx; \
Swizzle<T, 4, 1, 1, 1, 1> yyyy; \
Swizzle<T, 4, 1, 1, 1, 2> yyyz; \
Swizzle<T, 4, 1, 1, 1, 3> yyyw; \
Swizzle<T, 4, 1, 1, 2, 0> yyzx; \
Swizzle<T, 4, 1, 1, 2, 1> yyzy; \
Swizzle<T, 4, 1, 1, 2, 2> yyzz; \
Swizzle<T, 4, 1, 1, 2, 3> yyzw; \
Swizzle<T, 4, 1, 1, 3, 0> yywx; \
Swizzle<T, 4, 1, 1, 3, 1> yywy; \
Swizzle<T, 4, 1, 1, 3, 2> yywz; \
Swizzle<T, 4, 1, 1, 3, 3> yyww; \
Swizzle<T, 4, 1, 2, 0, 0> yzxx; \
Swizzle<T, 4, 1, 2, 0, 1> yzxy; \
Swizzle<T, 4, 1, 2, 0, 2> yzxz; \
Swizzle<T, 4, 1, 2, 0, 3> yzxw; \
Swizzle<T, 4, 1, 2, 1, 0> yzyx; \
Swizzle<T, 4, 1, 2, 1, 1> yzyy; \
Swizzle<T, 4, 1, 2, 1, 2> yzyz; \
Swizzle<T, 4, 1, 2, 1, 3> yzyw; \
Swizzle<T, 4, 1, 2, 2, 0> yzzx; \
Swizzle<T, 4, 1, 2, 2, 1> yzzy; \
Swizzle<T, 4, 1, 2, 2, 2> yzzz; \
Swizzle<T, 4, 1, 2, 2, 3> yzzw; \
Swizzle<T, 4, 1, 2, 3, 0> yzwx; \
Swizzle<T, 4, 1, 2, 3, 1> yzwy; \
Swizzle<T, 4, 1, 2, 3, 2> yzwz; \
Swizzle<T, 4, 1, 2, 3, 3> yzww; \
Swizzle<T, 4, 1, 3, 0, 0> ywxx; \
Swizzle<T, 4, 1, 3, 0, 1> ywxy; \
Swizzle<T, 4, 1, 3, 0, 2> ywxz; \
Swizzle<T, 4, 1, 3, 0, 3> ywxw; \
Swizzle<T, 4, 1, 3, 1, 0> ywyx; \
Swizzle<T, 4, 1, 3, 1, 1> ywyy; \
Swizzle<T, 4, 1, 3, 1, 2> ywyz; \
Swizzle<T, 4, 1, 3, 1, 3> ywyw; \
Swizzle<T, 4, 1, 3, 2, 0> ywzx; \
Swizzle<T, 4, 1, 3, 2, 1> ywzy; \
Swizzle<T, 4, 1, 3, 2, 2> ywzz; \
Swizzle<T, 4, 1, 3, 2, 3> ywzw; \
Swizzle<T, 4, 1, 3, 3, 0> ywwx; \
Swizzle<T, 4, 1, 3, 3, 1> ywwy; \
Swizzle<T, 4, 1, 3, 3, 2> ywwz; \
Swizzle<T, 4, 1, 3, 3, 3> ywww; \
Swizzle<T, 4, 2, 0, 0, 0> zxxx; \
Swizzle<T, 4, 2, 0, 0, 1> zxxy; \
Swizzle<T, 4, 2, 0, 0, 2> zxxz; \
Swizzle<T, 4, 2, 0, 0, 3> zxxw; \
Swizzle<T, 4, 2, 0, 1, 0> zxyx; \
Swizzle<T, 4, 2, 0, 1, 1> zxyy; \
Swizzle<T, 4, 2, 0, 1, 2> zxyz; \
Swizzle<T, 4, 2, 0, 1, 3> zxyw; \
Swizzle<T, 4, 2, 0, 2, 0> zxzx; \
Swizzle<T, 4, 2, 0, 2, 1> zxzy; \
Swizzle<T, 4, 2, 0, 2, 2> zxzz; \
Swizzle<T, 4, 2, 0, 2, 3> zxzw; \
Swizzle<T, 4, 2, 0, 3, 0> zxwx; \
Swizzle<T, 4, 2, 0, 3, 1> zxwy; \
Swizzle<T, 4, 2, 0, 3, 2> zxwz; \
Swizzle<T, 4, 2, 0, 3, 3> zxww; \
Swizzle<T, 4, 2, 1, 0, 0> zyxx; \
Swizzle<T, 4, 2, 1, 0, 1> zyxy; \
Swizzle<T, 4, 2, 1, 0, 2> zyxz; \
Swizzle<T, 4, 2, 1, 0, 3> zyxw; \
Swizzle<T, 4, 2, 1, 1, 0> zyyx; \
Swizzle<T, 4, 2, 1, 1, 1> zyyy; \
Swizzle<T, 4, 2, 1, 1, 2> zyyz; \
Swizzle<T, 4, 2, 1, 1, 3> zyyw; \
Swizzle<T, 4, 2, 1, 2, 0> zyzx; \
Swizzle<T, 4, 2, 1, 2, 1> zyzy; \
Swizzle<T, 4, 2, 1, 2, 2> zyzz; \
Swizzle<T, 4, 2, 1, 2, 3> zyzw; \
Swizzle<T, 4, 2, 1, 3, 0> zywx; \
Swizzle<T, 4, 2, 1, 3, 1> zywy; \
Swizzle<T, 4, 2, 1, 3, 2> zywz; \
Swizzle<T, 4, 2, 1, 3, 3> zyww; \
Swizzle<T, 4, 2, 2, 0, 0> zzxx; \
Swizzle<T, 4, 2, 2, 0, 1> zzxy; \
Swizzle<T, 4, 2, 2, 0, 2> zzxz; \
Swizzle<T, 4, 2, 2, 0, 3> zzxw; \
Swizzle<T, 4, 2, 2, 1, 0> zzyx; \
Swizzle<T, 4, 2, 2, 1, 1> zzyy; \
Swizzle<T, 4, 2, 2, 1, 2> zzyz; \
Swizzle<T, 4, 2, 2, 1, 3> zzyw; \
Swizzle<T, 4, 2, 2, 2, 0> zzzx; \
Swizzle<T, 4, 2, 2, 2, 1> zzzy; \
Swizzle<T, 4, 2, 2, 2, 2> zzzz; \
Swizzle<T, 4, 2, 2, 2, 3> zzzw; \
Swizzle<T, 4, 2, 2, 3, 0> zzwx; \
Swizzle<T, 4, 2, 2, 3, 1> zzwy; \
Swizzle<T, 4, 2, 2, 3, 2> zzwz; \
Swizzle<T, 4, 2, 2, 3, 3> zzww; \
Swizzle<T, 4, 2, 3, 0, 0> zwxx; \
Swizzle<T, 4, 2, 3, 0, 1> zwxy; \
Swizzle<T, 4, 2, 3, 0, 2> zwxz; \
Swizzle<T, 4, 2, 3, 0, 3> zwxw; \
Swizzle<T, 4, 2, 3, 1, 0> zwyx; \
Swizzle<T, 4, 2, 3, 1, 1> zwyy; \
Swizzle<T, 4, 2, 3, 1, 2> zwyz; \
Swizzle<T, 4, 2, 3, 1, 3> zwyw; \
Swizzle<T, 4, 2, 3, 2, 0> zwzx; \
Swizzle<T, 4, 2, 3, 2, 1> zwzy; \
Swizzle<T, 4, 2, 3, 2, 2> zwzz; \
Swizzle<T, 4, 2, 3, 2, 3> zwzw; \
Swizzle<T, 4, 2, 3, 3, 0> zwwx; \
Swizzle<T, 4, 2, 3, 3, 1> zwwy; \
Swizzle<T, 4, 2, 3, 3, 2> zwwz; \
Swizzle<T, 4, 2, 3, 3, 3> zwww; \
Swizzle<T, 4, 3, 0, 0, 0> wxxx; \
Swizzle<T, 4, 3, 0, 0, 1> wxxy; \
Swizzle<T, 4, 3, 0, 0, 2> wxxz; \
Swizzle<T, 4, 3, 0, 0, 3> wxxw; \
Swizzle<T, 4, 3, 0, 1, 0> wxyx; \
Swizzle<T, 4, 3, 0, 1, 1> wxyy; \
Swizzle<T, 4, 3, 0, 1, 2> wxyz; \
Swizzle<T, 4, 3, 0, 1, 3> wxyw; \
Swizzle<T, 4, 3, 0, 2, 0> wxzx; \
Swizzle<T, 4, 3, 0, 2, 1> wxzy; \
Swizzle<T, 4, 3, 0, 2, 2> wxzz; \
Swizzle<T, 4, 3, 0, 2, 3> wxzw; \
Swizzle<T, 4, 3, 0, 3, 0> wxwx; \
Swizzle<T, 4, 3, 0, 3, 1> wxwy; \
Swizzle<T, 4, 3, 0, 3, 2> wxwz; \
Swizzle<T, 4, 3, 0, 3, 3> wxww; \
Swizzle<T, 4, 3, 1, 0, 0> wyxx; \
Swizzle<T, 4, 3, 1, 0, 1> wyxy; \
Swizzle<T, 4, 3, 1, 0, 2> wyxz; \
Swizzle<T, 4, 3, 1, 0, 3> wyxw; \
Swizzle<T, 4, 3, 1, 1, 0> wyyx; \
Swizzle<T, 4, 3, 1, 1, 1> wyyy; \
Swizzle<T, 4, 3, 1, 1, 2> wyyz; \
Swizzle<T, 4, 3, 1, 1, 3> wyyw; \
Swizzle<T, 4, 3, 1, 2, 0> wyzx; \
Swizzle<T, 4, 3, 1, 2, 1> wyzy; \
Swizzle<T, 4, 3, 1, 2, 2> wyzz; \
Swizzle<T, 4, 3, 1, 2, 3> wyzw; \
Swizzle<T, 4, 3, 1, 3, 0> wywx; \
Swizzle<T, 4, 3, 1, 3, 1> wywy; \
Swizzle<T, 4, 3, 1, 3, 2> wywz; \
Swizzle<T, 4, 3, 1, 3, 3> wyww; \
Swizzle<T, 4, 3, 2, 0, 0> wzxx; \
Swizzle<T, 4, 3, 2, 0, 1> wzxy; \
Swizzle<T, 4, 3, 2, 0, 2> wzxz; \
Swizzle<T, 4, 3, 2, 0, 3> wzxw; \
Swizzle<T, 4, 3, 2, 1, 0> wzyx; \
Swizzle<T, 4, 3, 2, 1, 1> wzyy; \
Swizzle<T, 4, 3, 2, 1, 2> wzyz; \
Swizzle<T, 4, 3, 2, 1, 3> wzyw; \
Swizzle<T, 4, 3, 2, 2, 0> wzzx; \
Swizzle<T, 4, 3, 2, 2, 1> wzzy; \
Swizzle<T, 4, 3, 2, 2, 2> wzzz; \
Swizzle<T, 4, 3, 2, 2, 3> wzzw; \
Swizzle<T, 4, 3, 2, 3, 0> wzwx; \
Swizzle<T, 4, 3, 2, 3, 1> wzwy; \
Swizzle<T, 4, 3, 2, 3, 2> wzwz; \
Swizzle<T, 4, 3, 2, 3, 3> wzww; \
Swizzle<T, 4, 3, 3, 0, 0> wwxx; \
Swizzle<T, 4, 3, 3, 0, 1> wwxy; \
Swizzle<T, 4, 3, 3, 0, 2> wwxz; \
Swizzle<T, 4, 3, 3, 0, 3> wwxw; \
Swizzle<T, 4, 3, 3, 1, 0> wwyx; \
Swizzle<T, 4, 3, 3, 1, 1> wwyy; \
Swizzle<T, 4, 3, 3, 1, 2> wwyz; \
Swizzle<T, 4, 3, 3, 1, 3> wwyw; \
Swizzle<T, 4, 3, 3, 2, 0> wwzx; \
Swizzle<T, 4, 3, 3, 2, 1> wwzy; \
Swizzle<T, 4, 3, 3, 2, 2> wwzz; \
Swizzle<T, 4, 3, 3, 2, 3> wwzw; \
Swizzle<T, 4, 3, 3, 3, 0> wwwx; \
Swizzle<T, 4, 3, 3, 3, 1> wwwy; \
Swizzle<T, 4, 3, 3, 3, 2> wwwz; \
Swizzle<T, 4, 3, 3, 3, 3> wwww;
