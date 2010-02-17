/*
 *  Copyright 2009-2010 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
 
#pragma once
#include "base/Defs.hpp"

#include <math.h>

namespace FW
{
//------------------------------------------------------------------------

FW_CUDA_FUNC F32    sqrt            (F32 a)         { return ::sqrtf(a); }
FW_CUDA_FUNC F64    sqrt            (F64 a)         { return ::sqrt(a); }
FW_CUDA_FUNC S32    abs             (S32 a)         { return (a >= 0) ? a : -a; }
FW_CUDA_FUNC F32    abs             (F32 a)         { return ::fabsf(a); }
FW_CUDA_FUNC F64    abs             (F64 a)         { return ::abs(a); }
FW_CUDA_FUNC F64    pow             (F64 a, F64 b)  { return ::pow(a, b); }
FW_CUDA_FUNC F64    exp             (F64 a)         { return ::exp(a); }
FW_CUDA_FUNC F64    log             (F64 a)         { return ::log(a); }
FW_CUDA_FUNC F64    sin             (F64 a)         { return ::sin(a); }
FW_CUDA_FUNC F64    cos             (F64 a)         { return ::cos(a); }
FW_CUDA_FUNC F64    tan             (F64 a)         { return ::tan(a); }
FW_CUDA_FUNC F32    asin            (F32 a)         { return ::asinf(a); }
FW_CUDA_FUNC F64    asin            (F64 a)         { return ::asin(a); }
FW_CUDA_FUNC F32    acos            (F32 a)         { return ::acosf(a); }
FW_CUDA_FUNC F64    acos            (F64 a)         { return ::acos(a); }
FW_CUDA_FUNC F32    atan            (F32 a)         { return ::atanf(a); }
FW_CUDA_FUNC F64    atan            (F64 a)         { return ::atan(a); }
FW_CUDA_FUNC F64    atan2           (F64 y, F64 x)  { return ::atan2(y, x); }
FW_CUDA_FUNC F32    atan2           (F32 y, F32 x)  { return ::atan2f(y, x); }
FW_CUDA_FUNC F32    floor           (F32 a)         { return ::floorf(a); }
FW_CUDA_FUNC F64    floor           (F64 a)         { return ::floor(a); }
FW_CUDA_FUNC F32    ceil            (F32 a)         { return ::ceilf(a); }
FW_CUDA_FUNC F64    ceil            (F64 a)         { return ::ceil(a); }
FW_CUDA_FUNC U64    doubleToBits    (F64 a)         { return *(U64*)&a; }
FW_CUDA_FUNC F64    bitsToDouble    (U64 a)         { return *(F64*)&a; }

#if FW_CUDA
FW_CUDA_FUNC F32    pow             (F32 a, F32 b)  { return ::__powf(a, b); }
FW_CUDA_FUNC F32    exp             (F32 a)         { return ::__expf(a); }
FW_CUDA_FUNC F32    exp2            (F32 a)         { return ::exp2f(a); }
FW_CUDA_FUNC F64    exp2            (F64 a)         { return ::exp2(a); }
FW_CUDA_FUNC F32    log             (F32 a)         { return ::__logf(a); }
FW_CUDA_FUNC F32    log2            (F32 a)         { return ::__log2f(a); }
FW_CUDA_FUNC F64    log2            (F64 a)         { return ::log2(a); }
FW_CUDA_FUNC F32    sin             (F32 a)         { return ::__sinf(a); }
FW_CUDA_FUNC F32    cos             (F32 a)         { return ::__cosf(a); }
FW_CUDA_FUNC F32    tan             (F32 a)         { return ::__tanf(a); }
FW_CUDA_FUNC U32    floatToBits     (F32 a)         { return ::__float_as_int(a); }
FW_CUDA_FUNC F32    bitsToFloat     (U32 a)         { return ::__int_as_float(a); }
FW_CUDA_FUNC F32    exp2            (int a)         { return ::exp2f((F32)a); }
FW_CUDA_FUNC F32    fastMin         (F32 a, F32 b)  { return ::fminf(a, b); }
FW_CUDA_FUNC F32    fastMax         (F32 a, F32 b)  { return ::fmaxf(a, b); }
FW_CUDA_FUNC F64    fastMin         (F64 a, F64 b)  { return ::fmin(a, b); }
FW_CUDA_FUNC F64    fastMax         (F64 a, F64 b)  { return ::fmax(a, b); }
#else
inline F32          pow             (F32 a, F32 b)  { return ::powf(a, b); }
inline F32          exp             (F32 a)         { return ::expf(a); }
inline F32          exp2            (F32 a)         { return ::powf(2.0f, a); }
inline F64          exp2            (F64 a)         { return ::pow(2.0, a); }
inline F32          log             (F32 a)         { return ::logf(a); }
inline F32          log2            (F32 a)         { return ::logf(a) / ::logf(2.0f); }
inline F64          log2            (F64 a)         { return ::log(a) / ::log(2.0); }
inline F32          sin             (F32 a)         { return ::sinf(a); }
inline F32          cos             (F32 a)         { return ::cosf(a); }
inline F32          tan             (F32 a)         { return ::tanf(a); }
inline U32          floatToBits     (F32 a)         { return *(U32*)&a; }
inline F32          bitsToFloat     (U32 a)         { return *(F32*)&a; }
inline F32          exp2            (int a)         { return bitsToFloat(clamp(a + 127, 1, 254) << 23); }
inline F32          fastMin         (F32 a, F32 b)  { return (a + b - abs(a - b)) * 0.5f; }
inline F32          fastMax         (F32 a, F32 b)  { return (a + b + abs(a - b)) * 0.5f; }
inline F64          fastMin         (F64 a, F64 b)  { return (a + b - abs(a - b)) * 0.5f; }
inline F64          fastMax         (F64 a, F64 b)  { return (a + b + abs(a - b)) * 0.5f; }
#endif

FW_CUDA_FUNC F32    scale           (F32 a, int b)  { return a * exp2(b); }
FW_CUDA_FUNC int    popc8           (U32 mask);
FW_CUDA_FUNC int    popc16          (U32 mask);
FW_CUDA_FUNC int    popc32          (U32 mask);

FW_CUDA_FUNC F32    fastClamp       (F32 v, F32 lo, F32 hi) { return fastMin(fastMax(v, lo), hi); }
FW_CUDA_FUNC F64    fastClamp       (F64 v, F64 lo, F64 hi) { return fastMin(fastMax(v, lo), hi); }

template <class T> FW_CUDA_FUNC T sqr(const T& a) { return a * a; }
template <class T> FW_CUDA_FUNC T rcp(const T& a) { return (a) ? (T)1 / a : (T)0; }
template <class A, class B> FW_CUDA_FUNC A lerp(const A& a, const A& b, const B& t) { return (A)(a * ((B)1 - t) + b * t); }

//------------------------------------------------------------------------

template <class T, int L> class Vector;

template <class T, int L, class S> class VectorBase
{
public:
    FW_CUDA_FUNC                    VectorBase  (void)                      {}

    FW_CUDA_FUNC    const T*        getPtr      (void) const                { return ((S*)this)->getPtr(); }
    FW_CUDA_FUNC    T*              getPtr      (void)                      { return ((S*)this)->getPtr(); }
    FW_CUDA_FUNC    const T&        get         (int idx) const             { FW_ASSERT(idx >= 0 && idx < L); return getPtr()[idx]; }
    FW_CUDA_FUNC    T&              get         (int idx)                   { FW_ASSERT(idx >= 0 && idx < L); return getPtr()[idx]; }
    FW_CUDA_FUNC    T               set         (int idx, const T& a)       { T& slot = get(idx); T old = slot; slot = a; return old; }

    FW_CUDA_FUNC    void            set         (const T& a)                { for (int i = 0; i < L; i++) get(i) = a; }
    FW_CUDA_FUNC    void            set         (const T* ptr)              { FW_ASSERT(ptr); for (int i = 0; i < L; i++) get(i) = ptr[i]; }
    FW_CUDA_FUNC    void            setZero     (void)                      { set((T)0); }

#if !FW_CUDA
                    void            print       (void) const                { for (int i = 0; i < L; i++) printf("%g\n", (F64)get(i)); }
#endif

    FW_CUDA_FUNC    bool            isZero      (void) const                { for (int i = 0; i < L; i++) if (get(i) != (T)0) return false; return true; }
    FW_CUDA_FUNC    T               lenSqr      (void) const                { T r = (T)0; for (int i = 0; i < L; i++) r += sqr(get(i)); return r; }
    FW_CUDA_FUNC    T               length      (void) const                { return sqrt(lenSqr()); }
    FW_CUDA_FUNC    S               normalize   (T len = (T)1) const        { return operator*(len * rcp(length())); }
    FW_CUDA_FUNC    T               min         (void) const                { T r = get(0); for (int i = 1; i < L; i++) r = FW::min(r, get(i)); return r; }
    FW_CUDA_FUNC    T               max         (void) const                { T r = get(0); for (int i = 1; i < L; i++) r = FW::max(r, get(i)); return r; }
    FW_CUDA_FUNC    T               sum         (void) const                { T r = get(0); for (int i = 1; i < L; i++) r += get(i); return r; }
    FW_CUDA_FUNC    S               abs         (void) const                { S r; for (int i = 0; i < L; i++) r.get(i) = FW::abs(get(i)); return r; }

    FW_CUDA_FUNC    Vector<T, L + 1> toHomogeneous(void) const              { Vector<T, L + 1> r; for (int i = 0; i < L; i++) r.get(i) = get(i); r.get(L) = (T)1; return r; }
    FW_CUDA_FUNC    Vector<T, L - 1> toCartesian(void) const                { Vector<T, L - 1> r; T c = rcp(get(L - 1)); for (int i = 0; i < L - 1; i++) r.get(i) = get(i) * c; return r; }

    FW_CUDA_FUNC    const T&        operator[]  (int idx) const             { return get(idx); }
    FW_CUDA_FUNC    T&              operator[]  (int idx)                   { return get(idx); }

    FW_CUDA_FUNC    S&              operator=   (const T& a)                { set(a); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator+=  (const T& a)                { set(operator+(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator-=  (const T& a)                { set(operator-(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator*=  (const T& a)                { set(operator*(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator/=  (const T& a)                { set(operator/(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator%=  (const T& a)                { set(operator%(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator&=  (const T& a)                { set(operator&(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator|=  (const T& a)                { set(operator|(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator^=  (const T& a)                { set(operator^(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator<<= (const T& a)                { set(operator<<(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator>>= (const T& a)                { set(operator>>(a)); return *(S*)this; }

    FW_CUDA_FUNC    S               operator+   (void) const                { return *this; }
    FW_CUDA_FUNC    S               operator-   (void) const                { S r; for (int i = 0; i < L; i++) r.get(i) = -get(i); return r; }
    FW_CUDA_FUNC    S               operator~   (void) const                { S r; for (int i = 0; i < L; i++) r.get(i) = ~get(i); return r; }

    FW_CUDA_FUNC    S               operator+   (const T& a) const          { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) + a; return r; }
    FW_CUDA_FUNC    S               operator-   (const T& a) const          { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) - a; return r; }
    FW_CUDA_FUNC    S               operator*   (const T& a) const          { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) * a; return r; }
    FW_CUDA_FUNC    S               operator/   (const T& a) const          { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) / a; return r; }
    FW_CUDA_FUNC    S               operator%   (const T& a) const          { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) % a; return r; }
    FW_CUDA_FUNC    S               operator&   (const T& a) const          { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) & a; return r; }
    FW_CUDA_FUNC    S               operator|   (const T& a) const          { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) | a; return r; }
    FW_CUDA_FUNC    S               operator^   (const T& a) const          { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) ^ a; return r; }
    FW_CUDA_FUNC    S               operator<<  (const T& a) const          { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) << a; return r; }
    FW_CUDA_FUNC    S               operator>>  (const T& a) const          { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) >> a; return r; }

    template <class V> FW_CUDA_FUNC void    set         (const VectorBase<T, L, V>& v)          { set(v.getPtr()); }
    template <class V> FW_CUDA_FUNC T       dot         (const VectorBase<T, L, V>& v) const    { T r = (T)0; for (int i = 0; i < L; i++) r += get(i) * v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       min         (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = FW::min(get(i), v.get(i)); return r; }
    template <class V> FW_CUDA_FUNC S       max         (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = FW::max(get(i), v.get(i)); return r; }
    template <class V, class W> FW_CUDA_FUNC S clamp    (const VectorBase<T, L, V>& lo, const VectorBase<T, L, W>& hi) const { S r; for (int i = 0; i < L; i++) r.get(i) = FW::clamp(get(i), lo.get(i), hi.get(i)); return r; }

    template <class V> FW_CUDA_FUNC S&      operator=   (const VectorBase<T, L, V>& v)          { set(v); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator+=  (const VectorBase<T, L, V>& v)          { set(operator+(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator-=  (const VectorBase<T, L, V>& v)          { set(operator-(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator*=  (const VectorBase<T, L, V>& v)          { set(operator*(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator/=  (const VectorBase<T, L, V>& v)          { set(operator/(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator%=  (const VectorBase<T, L, V>& v)          { set(operator%(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator&=  (const VectorBase<T, L, V>& v)          { set(operator&(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator|=  (const VectorBase<T, L, V>& v)          { set(operator|(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator^=  (const VectorBase<T, L, V>& v)          { set(operator^(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator<<= (const VectorBase<T, L, V>& v)          { set(operator<<(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator>>= (const VectorBase<T, L, V>& v)          { set(operator>>(v)); return *(S*)this; }

    template <class V> FW_CUDA_FUNC S       operator+   (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) + v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator-   (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) - v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator*   (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) * v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator/   (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) / v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator%   (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) % v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator&   (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) & v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator|   (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) | v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator^   (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) ^ v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator<<  (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) << v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator>>  (const VectorBase<T, L, V>& v) const    { S r; for (int i = 0; i < L; i++) r.get(i) = get(i) >> v.get(i); return r; }

    template <class V> FW_CUDA_FUNC bool    operator==  (const VectorBase<T, L, V>& v) const    { for (int i = 0; i < L; i++) if (get(i) != v.get(i)) return false; return true; }
    template <class V> FW_CUDA_FUNC bool    operator!=  (const VectorBase<T, L, V>& v) const    { return (!operator==(v)); }
};

//------------------------------------------------------------------------

template <class T, int L> class Vector : public VectorBase<T, L, Vector<T, L> >
{
public:
    FW_CUDA_FUNC                    Vector       (void)                     { setZero(); }
    FW_CUDA_FUNC                    Vector       (T a)                      { set(a); }

    FW_CUDA_FUNC    const T*        getPtr      (void) const                { return m_values; }
    FW_CUDA_FUNC    T*              getPtr      (void)                      { return m_values; }

    template <class V> FW_CUDA_FUNC Vector(const VectorBase<T, L, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Vector& operator=(const VectorBase<T, L, V>& v) { set(v); return *this; }

private:
    T               m_values[L];
};

//------------------------------------------------------------------------

class Vec2i : public VectorBase<S32, 2, Vec2i>
{
public:
    FW_CUDA_FUNC                    Vec2i       (void)                      { setZero(); }
    FW_CUDA_FUNC                    Vec2i       (S32 a)                     { set(a); }
    FW_CUDA_FUNC                    Vec2i       (S32 xx, S32 yy)            : x(xx), y(yy) {}

    FW_CUDA_FUNC    const S32*      getPtr      (void) const                { return &x; }
    FW_CUDA_FUNC    S32*            getPtr      (void)                      { return &x; }

    FW_CUDA_FUNC    Vec2i           perp        (void) const                { return Vec2i(-y, x); }

    template <class V> FW_CUDA_FUNC Vec2i(const VectorBase<S32, 2, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Vec2i& operator=(const VectorBase<S32, 2, V>& v) { set(v); return *this; }

public:
    S32             x;
    S32             y;
};

//------------------------------------------------------------------------

class Vec3i : public VectorBase<S32, 3, Vec3i>
{
public:
    FW_CUDA_FUNC                    Vec3i       (void)                      { setZero(); }
    FW_CUDA_FUNC                    Vec3i       (S32 a)                     { set(a); }
    FW_CUDA_FUNC                    Vec3i       (S32 xx, S32 yy, S32 zz)    : x(xx), y(yy), z(zz) {}
    FW_CUDA_FUNC                    Vec3i       (const Vec2i& xy, S32 zz)   : x(xy.x), y(xy.y), z(zz) {}

    FW_CUDA_FUNC    const S32*      getPtr      (void) const                { return &x; }
    FW_CUDA_FUNC    S32*            getPtr      (void)                      { return &x; }

    FW_CUDA_FUNC    Vec2i           getXY       (void) const                { return Vec2i(x, y); }

    template <class V> FW_CUDA_FUNC Vec3i(const VectorBase<S32, 3, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Vec3i& operator=(const VectorBase<S32, 3, V>& v) { set(v); return *this; }

public:
    S32             x;
    S32             y;
    S32             z;
};

//------------------------------------------------------------------------

class Vec4i : public VectorBase<S32, 4, Vec4i>
{
public:
    FW_CUDA_FUNC                    Vec4i       (void)                      { setZero(); }
    FW_CUDA_FUNC                    Vec4i       (S32 a)                     { set(a); }
    FW_CUDA_FUNC                    Vec4i       (S32 xx, S32 yy, S32 zz, S32 ww) : x(xx), y(yy), z(zz), w(ww) {}
    FW_CUDA_FUNC                    Vec4i       (const Vec2i& xy, S32 zz, S32 ww) : x(xy.x), y(xy.y), z(zz), w(ww) {}
    FW_CUDA_FUNC                    Vec4i       (const Vec3i& xyz, S32 ww)  : x(xyz.x), y(xyz.y), z(xyz.z), w(ww) {}

    FW_CUDA_FUNC    const S32*      getPtr      (void) const                { return &x; }
    FW_CUDA_FUNC    S32*            getPtr      (void)                      { return &x; }

    FW_CUDA_FUNC    Vec2i           getXY       (void) const                { return Vec2i(x, y); }
    FW_CUDA_FUNC    Vec3i           getXYZ      (void) const                { return Vec3i(x, y, z); }

    template <class V> FW_CUDA_FUNC Vec4i(const VectorBase<S32, 4, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Vec4i& operator=(const VectorBase<S32, 4, V>& v) { set(v); return *this; }

public:
    S32             x;
    S32             y;
    S32             z;
    S32             w;
};

//------------------------------------------------------------------------

class Vec2f : public VectorBase<F32, 2, Vec2f>
{
public:
    FW_CUDA_FUNC                    Vec2f       (void)                      { setZero(); }
    FW_CUDA_FUNC                    Vec2f       (F32 a)                     { set(a); }
    FW_CUDA_FUNC                    Vec2f       (F32 xx, F32 yy)            : x(xx), y(yy) {}
    FW_CUDA_FUNC                    Vec2f       (const Vec2i& v)            : x((F32)v.x), y((F32)v.y) {}

    FW_CUDA_FUNC    const F32*      getPtr      (void) const                { return &x; }
    FW_CUDA_FUNC    F32*            getPtr      (void)                      { return &x; }

    FW_CUDA_FUNC    operator        Vec2i       (void) const                { return Vec2i((S32)x, (S32)y); }

    FW_CUDA_FUNC    Vec2f           perp        (void) const                { return Vec2f(-y, x); }
    FW_CUDA_FUNC    F32             cross       (const Vec2f& v) const      { return x * v.y - y * v.x; }

    template <class V> FW_CUDA_FUNC Vec2f(const VectorBase<F32, 2, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Vec2f& operator=(const VectorBase<F32, 2, V>& v) { set(v); return *this; }

public:
    F32             x;
    F32             y;
};

//------------------------------------------------------------------------

class Vec3f : public VectorBase<F32, 3, Vec3f>
{
public:
    FW_CUDA_FUNC                    Vec3f       (void)                      { setZero(); }
    FW_CUDA_FUNC                    Vec3f       (F32 a)                     { set(a); }
    FW_CUDA_FUNC                    Vec3f       (F32 xx, F32 yy, F32 zz)    : x(xx), y(yy), z(zz) {}
    FW_CUDA_FUNC                    Vec3f       (const Vec2f& xy, F32 zz)   : x(xy.x), y(xy.y), z(zz) {}
    FW_CUDA_FUNC                    Vec3f       (const Vec3i& v)            : x((F32)v.x), y((F32)v.y), z((F32)v.z) {}

    FW_CUDA_FUNC    const F32*      getPtr      (void) const                { return &x; }
    FW_CUDA_FUNC    F32*            getPtr      (void)                      { return &x; }

    FW_CUDA_FUNC    operator        Vec3i       (void) const                { return Vec3i((S32)x, (S32)y, (S32)z); }
    FW_CUDA_FUNC    Vec2f           getXY       (void) const                { return Vec2f(x, y); }

    FW_CUDA_FUNC    Vec3f           cross       (const Vec3f& v) const      { return Vec3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

    template <class V> FW_CUDA_FUNC Vec3f(const VectorBase<F32, 3, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Vec3f& operator=(const VectorBase<F32, 3, V>& v) { set(v); return *this; }

public:
    F32             x;
    F32             y;
    F32             z;
};

//------------------------------------------------------------------------

class Vec4f : public VectorBase<F32, 4, Vec4f>
{
public:
    FW_CUDA_FUNC                    Vec4f       (void)                      { setZero(); }
    FW_CUDA_FUNC                    Vec4f       (F32 a)                     { set(a); }
    FW_CUDA_FUNC                    Vec4f       (F32 xx, F32 yy, F32 zz, F32 ww) : x(xx), y(yy), z(zz), w(ww) {}
    FW_CUDA_FUNC                    Vec4f       (const Vec2f& xy, F32 zz, F32 ww) : x(xy.x), y(xy.y), z(zz), w(ww) {}
    FW_CUDA_FUNC                    Vec4f       (const Vec3f& xyz, F32 ww)  : x(xyz.x), y(xyz.y), z(xyz.z), w(ww) {}
    FW_CUDA_FUNC                    Vec4f       (const Vec4i& v)            : x((F32)v.x), y((F32)v.y), z((F32)v.z), w((F32)v.w) {}

    FW_CUDA_FUNC    const F32*      getPtr      (void) const                { return &x; }
    FW_CUDA_FUNC    F32*            getPtr      (void)                      { return &x; }

    FW_CUDA_FUNC    operator        Vec4i       (void) const                { return Vec4i((S32)x, (S32)y, (S32)z, (S32)w); }
    FW_CUDA_FUNC    Vec2f           getXY       (void) const                { return Vec2f(x, y); }
    FW_CUDA_FUNC    Vec3f           getXYZ      (void) const                { return Vec3f(x, y, z); }

#if !FW_CUDA
    static Vec4f    fromABGR        (U32 abgr);
    U32             toABGR          (void) const;
#endif

    template <class V> FW_CUDA_FUNC Vec4f(const VectorBase<F32, 4, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Vec4f& operator=(const VectorBase<F32, 4, V>& v) { set(v); return *this; }

public:
    F32             x;
    F32             y;
    F32             z;
    F32             w;
};

//------------------------------------------------------------------------

class Vec2d : public VectorBase<F64, 2, Vec2d>
{
public:
    FW_CUDA_FUNC                    Vec2d       (void)                      { setZero(); }
    FW_CUDA_FUNC                    Vec2d       (F64 a)                     { set(a); }
    FW_CUDA_FUNC                    Vec2d       (F64 xx, F64 yy)            : x(xx), y(yy) {}
    FW_CUDA_FUNC                    Vec2d       (const Vec2i& v)            : x((F64)v.x), y((F64)v.y) {}
    FW_CUDA_FUNC                    Vec2d       (const Vec2f& v)            : x(v.x), y(v.y) {}

    FW_CUDA_FUNC    const F64*      getPtr      (void) const                { return &x; }
    FW_CUDA_FUNC    F64*            getPtr      (void)                      { return &x; }

    FW_CUDA_FUNC    operator        Vec2i       (void) const                { return Vec2i((S32)x, (S32)y); }
    FW_CUDA_FUNC    operator        Vec2f       (void) const                { return Vec2f((F32)x, (F32)y); }

    FW_CUDA_FUNC    Vec2d           perp        (void) const                { return Vec2d(-y, x); }
    FW_CUDA_FUNC    F64             cross       (const Vec2d& v) const      { return x * v.y - y * v.x; }

    template <class V> FW_CUDA_FUNC Vec2d(const VectorBase<F64, 2, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Vec2d& operator=(const VectorBase<F64, 2, V>& v) { set(v); return *this; }

public:
    F64             x;
    F64             y;
};

//------------------------------------------------------------------------

class Vec3d : public VectorBase<F64, 3, Vec3d>
{
public:
    FW_CUDA_FUNC                    Vec3d       (void)                      { setZero(); }
    FW_CUDA_FUNC                    Vec3d       (F64 a)                     { set(a); }
    FW_CUDA_FUNC                    Vec3d       (F64 xx, F64 yy, F64 zz)    : x(xx), y(yy), z(zz) {}
    FW_CUDA_FUNC                    Vec3d       (const Vec2d& xy, F64 zz)   : x(xy.x), y(xy.y), z(zz) {}
    FW_CUDA_FUNC                    Vec3d       (const Vec3i& v)            : x((F64)v.x), y((F64)v.y), z((F64)v.z) {}
    FW_CUDA_FUNC                    Vec3d       (const Vec3f& v)            : x(v.x), y(v.y), z(v.z) {}

    FW_CUDA_FUNC    const F64*      getPtr      (void) const                { return &x; }
    FW_CUDA_FUNC    F64*            getPtr      (void)                      { return &x; }

    FW_CUDA_FUNC    operator        Vec3i       (void) const                { return Vec3i((S32)x, (S32)y, (S32)z); }
    FW_CUDA_FUNC    operator        Vec3f       (void) const                { return Vec3f((F32)x, (F32)y, (F32)z); }
    FW_CUDA_FUNC    Vec2d           getXY       (void) const                { return Vec2d(x, y); }

    FW_CUDA_FUNC    Vec3d           cross       (const Vec3d& v) const      { return Vec3d(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

    template <class V> FW_CUDA_FUNC Vec3d(const VectorBase<F64, 3, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Vec3d& operator=(const VectorBase<F64, 3, V>& v) { set(v); return *this; }

public:
    F64             x;
    F64             y;
    F64             z;
};

//------------------------------------------------------------------------

class Vec4d : public VectorBase<F64, 4, Vec4d>
{
public:
    FW_CUDA_FUNC                    Vec4d       (void)                      { setZero(); }
    FW_CUDA_FUNC                    Vec4d       (F64 a)                     { set(a); }
    FW_CUDA_FUNC                    Vec4d       (F64 xx, F64 yy, F64 zz, F64 ww) : x(xx), y(yy), z(zz), w(ww) {}
    FW_CUDA_FUNC                    Vec4d       (const Vec2d& xy, F64 zz, F64 ww) : x(xy.x), y(xy.y), z(zz), w(ww) {}
    FW_CUDA_FUNC                    Vec4d       (const Vec3d& xyz, F64 ww)  : x(xyz.x), y(xyz.y), z(xyz.z), w(ww) {}
    FW_CUDA_FUNC                    Vec4d       (const Vec4i& v)            : x((F64)v.x), y((F64)v.y), z((F64)v.z), w((F64)v.w) {}
    FW_CUDA_FUNC                    Vec4d       (const Vec4f& v)            : x(v.x), y(v.y), z(v.z), w(v.w) {}

    FW_CUDA_FUNC    const F64*      getPtr      (void) const                { return &x; }
    FW_CUDA_FUNC    F64*            getPtr      (void)                      { return &x; }

    FW_CUDA_FUNC    operator        Vec4i       (void) const                { return Vec4i((S32)x, (S32)y, (S32)z, (S32)w); }
    FW_CUDA_FUNC    operator        Vec4f       (void) const                { return Vec4f((F32)x, (F32)y, (F32)z, (F32)w); }
    FW_CUDA_FUNC    Vec2d           getXY       (void) const                { return Vec2d(x, y); }
    FW_CUDA_FUNC    Vec3d           getXYZ      (void) const                { return Vec3d(x, y, z); }

    template <class V> FW_CUDA_FUNC Vec4d(const VectorBase<F64, 4, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Vec4d& operator=(const VectorBase<F64, 4, V>& v) { set(v); return *this; }

public:
    F64             x;
    F64             y;
    F64             z;
    F64             w;
};

//------------------------------------------------------------------------

template <class T, int L, class S> FW_CUDA_FUNC T lenSqr    (const VectorBase<T, L, S>& v)                  { return v.lenSqr(); }
template <class T, int L, class S> FW_CUDA_FUNC T length    (const VectorBase<T, L, S>& v)                  { return v.length(); }
template <class T, int L, class S> FW_CUDA_FUNC S normalize (const VectorBase<T, L, S>& v, T len = (T)1)    { return v.normalize(len); }
template <class T, int L, class S> FW_CUDA_FUNC T min       (const VectorBase<T, L, S>& v)                  { return v.min(); }
template <class T, int L, class S> FW_CUDA_FUNC T max       (const VectorBase<T, L, S>& v)                  { return v.max(); }
template <class T, int L, class S> FW_CUDA_FUNC T sum       (const VectorBase<T, L, S>& v)                  { return v.sum(); }
template <class T, int L, class S> FW_CUDA_FUNC S abs       (const VectorBase<T, L, S>& v)                  { return v.abs(); }

template <class T, int L, class S> FW_CUDA_FUNC S operator+     (const T& a, const VectorBase<T, L, S>& b)  { return b + a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator-     (const T& a, const VectorBase<T, L, S>& b)  { return -b + a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator*     (const T& a, const VectorBase<T, L, S>& b)  { return b * a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator/     (const T& a, const VectorBase<T, L, S>& b)  { S r; for (int i = 0; i < L; i++) r.get(i) = a / b.get(i); return r; }
template <class T, int L, class S> FW_CUDA_FUNC S operator%     (const T& a, const VectorBase<T, L, S>& b)  { S r; for (int i = 0; i < L; i++) r.get(i) = a % b.get(i); return r; }
template <class T, int L, class S> FW_CUDA_FUNC S operator&     (const T& a, const VectorBase<T, L, S>& b)  { return b & a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator|     (const T& a, const VectorBase<T, L, S>& b)  { return b | a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator^     (const T& a, const VectorBase<T, L, S>& b)  { return b ^ a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator<<    (const T& a, const VectorBase<T, L, S>& b)  { S r; for (int i = 0; i < L; i++) r.get(i) = a << b.get(i); return r; }
template <class T, int L, class S> FW_CUDA_FUNC S operator>>    (const T& a, const VectorBase<T, L, S>& b)  { S r; for (int i = 0; i < L; i++) r.get(i) = a >> b.get(i); return r; }

template <class T, int L, class S, class V> FW_CUDA_FUNC T dot(const VectorBase<T, L, S>& a, const VectorBase<T, L, V>& b) { return a.dot(b); }

FW_CUDA_FUNC Vec2f  perp    (const Vec2f& v)                    { return v.perp(); }
FW_CUDA_FUNC Vec2d  perp    (const Vec2d& v)                    { return v.perp(); }
FW_CUDA_FUNC F32    cross   (const Vec2f& a, const Vec2f& b)    { return a.cross(b); }
FW_CUDA_FUNC F64    cross   (const Vec2d& a, const Vec2d& b)    { return a.cross(b); }
FW_CUDA_FUNC Vec3f  cross   (const Vec3f& a, const Vec3f& b)    { return a.cross(b); }
FW_CUDA_FUNC Vec3d  cross   (const Vec3d& a, const Vec3d& b)    { return a.cross(b); }

#define MINMAX(T) \
    FW_CUDA_FUNC T min(const T& a, const T& b)                          { return a.min(b); } \
    FW_CUDA_FUNC T min(T& a, T& b)                                      { return a.min(b); } \
    FW_CUDA_FUNC T max(const T& a, const T& b)                          { return a.max(b); } \
    FW_CUDA_FUNC T max(T& a, T& b)                                      { return a.max(b); } \
    FW_CUDA_FUNC T min(const T& a, const T& b, const T& c)              { return a.min(b).min(c); } \
    FW_CUDA_FUNC T min(T& a, T& b, T& c)                                { return a.min(b).min(c); } \
    FW_CUDA_FUNC T max(const T& a, const T& b, const T& c)              { return a.max(b).max(c); } \
    FW_CUDA_FUNC T max(T& a, T& b, T& c)                                { return a.max(b).max(c); } \
    FW_CUDA_FUNC T min(const T& a, const T& b, const T& c, const T& d)  { return a.min(b).min(c).min(d); } \
    FW_CUDA_FUNC T min(T& a, T& b, T& c, T& d)                          { return a.min(b).min(c).min(d); } \
    FW_CUDA_FUNC T max(const T& a, const T& b, const T& c, const T& d)  { return a.max(b).max(c).max(d); } \
    FW_CUDA_FUNC T max(T& a, T& b, T& c, T& d)                          { return a.max(b).max(c).max(d); } \
    FW_CUDA_FUNC T clamp(const T& v, const T& lo, const T& hi)          { return v.clamp(lo, hi); } \
    FW_CUDA_FUNC T clamp(T& v, T& lo, T& hi)                            { return v.clamp(lo, hi); }

MINMAX(Vec2i) MINMAX(Vec3i) MINMAX(Vec4i)
MINMAX(Vec2f) MINMAX(Vec3f) MINMAX(Vec4f)
MINMAX(Vec2d) MINMAX(Vec3d) MINMAX(Vec4d)
#undef MINMAX

//------------------------------------------------------------------------

template <class T, int L, class S> class MatrixBase
{
public:
    FW_CUDA_FUNC                    MatrixBase  (void)                      {}

    FW_CUDA_FUNC    const T*        getPtr      (void) const                { return ((S*)this)->getPtr(); }
    FW_CUDA_FUNC    T*              getPtr      (void)                      { return ((S*)this)->getPtr(); }
    FW_CUDA_FUNC    const T&        get         (int idx) const             { FW_ASSERT(idx >= 0 && idx < L * L); return getPtr()[idx]; }
    FW_CUDA_FUNC    T&              get         (int idx)                   { FW_ASSERT(idx >= 0 && idx < L * L); return getPtr()[idx]; }
    FW_CUDA_FUNC    const T&        get         (int r, int c) const        { FW_ASSERT(r >= 0 && r < L && c >= 0 && c < L); return getPtr()[r + c * L]; }
    FW_CUDA_FUNC    T&              get         (int r, int c)              { FW_ASSERT(r >= 0 && r < L && c >= 0 && c < L); return getPtr()[r + c * L]; }
    FW_CUDA_FUNC    T               set         (int idx, const T& a)       { T& slot = get(idx); T old = slot; slot = a; return old; }
    FW_CUDA_FUNC    T               set         (int r, int c, const T& a)  { T& slot = get(r, c); T old = slot; slot = a; return old; }
    FW_CUDA_FUNC    const Vector<T, L>& col     (int c) const               { FW_ASSERT(c >= 0 && c < L); return *(const Vector<T, L>*)(getPtr() + c * L); }
    FW_CUDA_FUNC    Vector<T, L>&   col         (int c)                     { FW_ASSERT(c >= 0 && c < L); return *(Vector<T, L>*)(getPtr() + c * L); }
    FW_CUDA_FUNC    const Vector<T, L>& getCol  (int c) const               { return col(c); }
    FW_CUDA_FUNC    Vector<T, L>    getRow      (int r) const;

    FW_CUDA_FUNC    void            set         (const T& a)                { for (int i = 0; i < L * L; i++) get(i) = a; }
    FW_CUDA_FUNC    void            set         (const T* ptr)              { FW_ASSERT(ptr); for (int i = 0; i < L * L; i++) get(i) = ptr[i]; }
    FW_CUDA_FUNC    void            setZero     (void)                      { set((T)0); }
    FW_CUDA_FUNC    void            setIdentity (void)                      { setZero(); for (int i = 0; i < L; i++) get(i, i) = (T)1; }

#if !FW_CUDA
    void            print       (void) const;
#endif

    FW_CUDA_FUNC    S               transp      (void) const;
    FW_CUDA_FUNC    T               det         (void) const                { return FW::det(*this); }
    FW_CUDA_FUNC    S               inv         (void) const                { return FW::inv(*this); }

    FW_CUDA_FUNC    const T&        operator()  (int r, int c) const        { return get(r, c); }
    FW_CUDA_FUNC    T&              operator()  (int r, int c)              { return get(r, c); }

    FW_CUDA_FUNC    S&              operator=   (const T& a)                { set(a); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator+=  (const T& a)                { set(operator+(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator-=  (const T& a)                { set(operator-(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator*=  (const T& a)                { set(operator*(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator/=  (const T& a)                { set(operator/(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator%=  (const T& a)                { set(operator%(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator&=  (const T& a)                { set(operator&(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator|=  (const T& a)                { set(operator|(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator^=  (const T& a)                { set(operator^(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator<<= (const T& a)                { set(operator<<(a)); return *(S*)this; }
    FW_CUDA_FUNC    S&              operator>>= (const T& a)                { set(operator>>(a)); return *(S*)this; }

    FW_CUDA_FUNC    S               operator+   (void) const                { return *this; }
    FW_CUDA_FUNC    S               operator-   (void) const                { S r; for (int i = 0; i < L * L; i++) r.get(i) = -get(i); return r; }
    FW_CUDA_FUNC    S               operator~   (void) const                { S r; for (int i = 0; i < L * L; i++) r.get(i) = ~get(i); return r; }

    FW_CUDA_FUNC    S               operator+   (const T& a) const          { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) + a; return r; }
    FW_CUDA_FUNC    S               operator-   (const T& a) const          { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) - a; return r; }
    FW_CUDA_FUNC    S               operator*   (const T& a) const          { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) * a; return r; }
    FW_CUDA_FUNC    S               operator/   (const T& a) const          { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) / a; return r; }
    FW_CUDA_FUNC    S               operator%   (const T& a) const          { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) % a; return r; }
    FW_CUDA_FUNC    S               operator&   (const T& a) const          { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) & a; return r; }
    FW_CUDA_FUNC    S               operator|   (const T& a) const          { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) | a; return r; }
    FW_CUDA_FUNC    S               operator^   (const T& a) const          { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) ^ a; return r; }
    FW_CUDA_FUNC    S               operator<<  (const T& a) const          { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) << a; return r; }
    FW_CUDA_FUNC    S               operator>>  (const T& a) const          { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) >> a; return r; }

    template <class V> FW_CUDA_FUNC void    setCol      (int c, const VectorBase<T, L, V>& v)   { col(c) = v; }
    template <class V> FW_CUDA_FUNC void    setRow      (int r, const VectorBase<T, L, V>& v);
    template <class V> FW_CUDA_FUNC void    set         (const MatrixBase<T, L, V>& v)          { set(v.getPtr()); }

    template <class V> FW_CUDA_FUNC S       preXlate    (const VectorBase<T, L - 1, V>& v) const;
    template <class V> FW_CUDA_FUNC S       postXlate   (const VectorBase<T, L - 1, V>& v) const;
    template <class V> FW_CUDA_FUNC S       preScale    (const VectorBase<T, L - 1, V>& v) const;
    template <class V> FW_CUDA_FUNC S       postScale   (const VectorBase<T, L - 1, V>& v) const;
    template <class V> FW_CUDA_FUNC S       preScale    (const VectorBase<T, L, V>& v) const;
    template <class V> FW_CUDA_FUNC S       postScale   (const VectorBase<T, L, V>& v) const;

    template <class V> FW_CUDA_FUNC S&      operator=   (const MatrixBase<T, L, V>& v)          { set(v); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator+=  (const MatrixBase<T, L, V>& v)          { set(operator+(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator-=  (const MatrixBase<T, L, V>& v)          { set(operator-(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator*=  (const MatrixBase<T, L, V>& v)          { set(operator*(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator/=  (const MatrixBase<T, L, V>& v)          { set(operator/(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator%=  (const MatrixBase<T, L, V>& v)          { set(operator%(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator&=  (const MatrixBase<T, L, V>& v)          { set(operator&(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator|=  (const MatrixBase<T, L, V>& v)          { set(operator|(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator^=  (const MatrixBase<T, L, V>& v)          { set(operator^(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator<<= (const MatrixBase<T, L, V>& v)          { set(operator<<(v)); return *(S*)this; }
    template <class V> FW_CUDA_FUNC S&      operator>>= (const MatrixBase<T, L, V>& v)          { set(operator>>(v)); return *(S*)this; }

    template <class V> FW_CUDA_FUNC V       operator*   (const VectorBase<T, L, V>& v) const;
    template <class V> FW_CUDA_FUNC V       operator*   (const VectorBase<T, L - 1, V>& v) const;

    template <class V> FW_CUDA_FUNC S       operator+   (const MatrixBase<T, L, V>& v) const    { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) + v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator-   (const MatrixBase<T, L, V>& v) const    { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) - v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator*   (const MatrixBase<T, L, V>& v) const;
    template <class V> FW_CUDA_FUNC S       operator/   (const MatrixBase<T, L, V>& v) const    { return operator*(v.inv()); }
    template <class V> FW_CUDA_FUNC S       operator%   (const MatrixBase<T, L, V>& v) const    { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) % v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator&   (const MatrixBase<T, L, V>& v) const    { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) & v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator|   (const MatrixBase<T, L, V>& v) const    { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) | v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator^   (const MatrixBase<T, L, V>& v) const    { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) ^ v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator<<  (const MatrixBase<T, L, V>& v) const    { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) << v.get(i); return r; }
    template <class V> FW_CUDA_FUNC S       operator>>  (const MatrixBase<T, L, V>& v) const    { S r; for (int i = 0; i < L * L; i++) r.get(i) = get(i) >> v.get(i); return r; }

    template <class V> FW_CUDA_FUNC bool    operator==  (const MatrixBase<T, L, V>& v) const    { for (int i = 0; i < L * L; i++) if (get(i) != v.get(i)) return false; return true; }
    template <class V> FW_CUDA_FUNC bool    operator!=  (const MatrixBase<T, L, V>& v) const    { return (!operator==(v)); }
};

//------------------------------------------------------------------------

template <class T, int L> class Matrix : public MatrixBase<T, L, Matrix<T, L> >
{
public:
    FW_CUDA_FUNC                    Matrix      (void)                      { setIdentity(); }
    FW_CUDA_FUNC    explicit        Matrix      (T a)                       { set(a); }

    FW_CUDA_FUNC    const T*        getPtr      (void) const                { return m_values; }
    FW_CUDA_FUNC    T*              getPtr      (void)                      { return m_values; }

    template <class V> FW_CUDA_FUNC Matrix(const MatrixBase<T, L, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Matrix& operator=(const MatrixBase<T, L, V>& v) { set(v); return *this; }

private:
    T               m_values[L * L];
};

//------------------------------------------------------------------------

class Mat2f : public MatrixBase<F32, 2, Mat2f>
{
public:
    FW_CUDA_FUNC                    Mat2f       (void)                      { setIdentity(); }
    FW_CUDA_FUNC    explicit        Mat2f       (F32 a)                     { set(a); }

    FW_CUDA_FUNC    const F32*      getPtr      (void) const                { return &m00; }
    FW_CUDA_FUNC    F32*            getPtr      (void)                      { return &m00; }

    template <class V> FW_CUDA_FUNC Mat2f(const MatrixBase<F32, 2, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Mat2f& operator=(const MatrixBase<F32, 2, V>& v) { set(v); return *this; }

public:
    F32             m00, m10;
    F32             m01, m11;
};

//------------------------------------------------------------------------

class Mat3f : public MatrixBase<F32, 3, Mat3f>
{
public:
    FW_CUDA_FUNC                    Mat3f       (void)                      { setIdentity(); }
    FW_CUDA_FUNC    explicit        Mat3f       (F32 a)                     { set(a); }

    FW_CUDA_FUNC    const F32*      getPtr      (void) const                { return &m00; }
    FW_CUDA_FUNC    F32*            getPtr      (void)                      { return &m00; }

    template <class V> FW_CUDA_FUNC Mat3f(const MatrixBase<F32, 3, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Mat3f& operator=(const MatrixBase<F32, 3, V>& v) { set(v); return *this; }

public:
    F32             m00, m10, m20;
    F32             m01, m11, m21;
    F32             m02, m12, m22;
};

//------------------------------------------------------------------------

class Mat4f : public MatrixBase<F32, 4, Mat4f>
{
public:
    FW_CUDA_FUNC                    Mat4f       (void)                      { setIdentity(); }
    FW_CUDA_FUNC    explicit        Mat4f       (F32 a)                     { set(a); }

    FW_CUDA_FUNC    const F32*      getPtr      (void) const                { return &m00; }
    FW_CUDA_FUNC    F32*            getPtr      (void)                      { return &m00; }

#if !FW_CUDA
    Mat3f                           getXYZ      (void) const;
    static Mat4f                    fitToView   (const Vec2f& pos, const Vec2f& size, const Vec2f& viewSize);
    static Mat4f                    perspective (F32 fov, F32 near, F32 far);
#endif

    template <class V> FW_CUDA_FUNC Mat4f(const MatrixBase<F32, 4, V>& v) { set(v); }
    template <class V> FW_CUDA_FUNC Mat4f& operator=(const MatrixBase<F32, 4, V>& v) { set(v); return *this; }

public:
    F32             m00, m10, m20, m30;
    F32             m01, m11, m21, m31;
    F32             m02, m12, m22, m32;
    F32             m03, m13, m23, m33;
};

//------------------------------------------------------------------------

template <class T, int L, class S> FW_CUDA_FUNC Matrix<T, L> outerProduct(const VectorBase<T, L, S>& a, const VectorBase<T, L, S>& b);

template <class T, int L, class S> FW_CUDA_FUNC S transp    (const MatrixBase<T, L, S>& v)  { return v.transp(); }

template <class T, int L, class S> FW_CUDA_FUNC S operator+     (const T& a, const MatrixBase<T, L, S>& b)  { return b + a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator-     (const T& a, const MatrixBase<T, L, S>& b)  { return -b + a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator*     (const T& a, const MatrixBase<T, L, S>& b)  { return b * a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator/     (const T& a, const MatrixBase<T, L, S>& b)  { S r; for (int i = 0; i < L * L; i++) r.get(i) = a / b.get(i); return r; }
template <class T, int L, class S> FW_CUDA_FUNC S operator%     (const T& a, const MatrixBase<T, L, S>& b)  { S r; for (int i = 0; i < L * L; i++) r.get(i) = a % b.get(i); return r; }
template <class T, int L, class S> FW_CUDA_FUNC S operator&     (const T& a, const MatrixBase<T, L, S>& b)  { return b & a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator|     (const T& a, const MatrixBase<T, L, S>& b)  { return b | a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator^     (const T& a, const MatrixBase<T, L, S>& b)  { return b ^ a; }
template <class T, int L, class S> FW_CUDA_FUNC S operator<<    (const T& a, const MatrixBase<T, L, S>& b)  { S r; for (int i = 0; i < L * L; i++) r.get(i) = a << b.get(i); return r; }
template <class T, int L, class S> FW_CUDA_FUNC S operator>>    (const T& a, const MatrixBase<T, L, S>& b)  { S r; for (int i = 0; i < L * L; i++) r.get(i) = a >> b.get(i); return r; }

template <class T, int L, class S, class V> FW_CUDA_FUNC S xlate    (const VectorBase<T, L - 1, V>& v, const MatrixBase<T, L, S>& m)    { return m.preXlate(v); }
template <class T, int L, class S, class V> FW_CUDA_FUNC S xlate    (const MatrixBase<T, L, S>& m, const VectorBase<T, L - 1, V>& v)    { return m.postXlate(v); }
template <class T, int L, class S, class V> FW_CUDA_FUNC S scale    (const VectorBase<T, L - 1, V>& v, const MatrixBase<T, L, S>& m)    { return m.preScale(v); }
template <class T, int L, class S, class V> FW_CUDA_FUNC S scale    (const MatrixBase<T, L, S>& m, const VectorBase<T, L - 1, V>& v)    { return m.postScale(v); }
template <class T, int L, class S, class V> FW_CUDA_FUNC S scale    (const VectorBase<T, L, V>& v, const MatrixBase<T, L, S>& m)        { return m.preScale(v); }
template <class T, int L, class S, class V> FW_CUDA_FUNC S scale    (const MatrixBase<T, L, S>& m, const VectorBase<T, L, V>& v)        { return m.postScale(v); }

//------------------------------------------------------------------------

FW_CUDA_CONST int c_popc8LUT[] =
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};

FW_CUDA_FUNC int popc8(U32 mask)
{
    FW_ASSERT(mask < (int)FW_ARRAY_SIZE(c_popc8LUT));
    return c_popc8LUT[mask];
}

FW_CUDA_FUNC int popc16(U32 mask)
{
    FW_ASSERT(mask < 0x00010000u);
    return c_popc8LUT[mask & 0xffu] + c_popc8LUT[mask >> 8];
}

FW_CUDA_FUNC int popc32(U32 mask)
{
    int result = c_popc8LUT[mask & 0xffu];
    result += c_popc8LUT[(mask >> 8) & 0xffu];
    result += c_popc8LUT[(mask >> 16) & 0xffu];
    result += c_popc8LUT[mask >> 24];
    return result;
}

//------------------------------------------------------------------------

template <class T, int L, class S> Vector<T, L> MatrixBase<T, L, S>::getRow(int idx) const
{
    Vector<T, L> r;
    for (int i = 0; i < L; i++)
        r[i] = get(idx, i);
    return r;
}

//------------------------------------------------------------------------

#if !FW_CUDA
template <class T, int L, class S> void MatrixBase<T, L, S>::print(void) const
{
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < L; j++)
            printf("%-16g", (F64)get(i, j));
        printf("\n");
    }
}
#endif

//------------------------------------------------------------------------

template <class T, int L, class S> S MatrixBase<T, L, S>::transp(void) const
{
    S r;
    for (int i = 0; i < L; i++)
        for (int j = 0; j < L; j++)
            r(i, j) = get(j, i);
    return r;
}

//------------------------------------------------------------------------

template <class T, int L, class V> T det(const MatrixBase<T, L, V>& v)
{
    T r = (T)0;
    T s = (T)1;
    for (int i = 0; i < L; i++)
    {
        Matrix<T, L - 1> sub;
        for (int j = 0; j < L - 1; j++)
            for (int k = 0; k < L - 1; k++)
                sub(j, k) = v((j < i) ? j : j + 1, k + 1);
        r += det(sub) * v(i, 0) * s;
        s = -s;
    }
    return r;
}

//------------------------------------------------------------------------

template <class T, class V> T det(const MatrixBase<T, 1, V>& v)
{
    return v(0, 0);
}

//------------------------------------------------------------------------

template <class T, class V> T det(const MatrixBase<T, 2, V>& v)
{
    return v(0, 0) * v(1, 1) - v(0, 1) * v(1, 0);
}

//------------------------------------------------------------------------

template <class T, class V> T det(const MatrixBase<T, 3, V>& v)
{
    return v(0, 0) * v(1, 1) * v(2, 2) - v(0, 0) * v(1, 2) * v(2, 1) +
           v(1, 0) * v(2, 1) * v(0, 2) - v(1, 0) * v(2, 2) * v(0, 1) +
           v(2, 0) * v(0, 1) * v(1, 2) - v(2, 0) * v(0, 2) * v(1, 1);
}

//------------------------------------------------------------------------

template <class T, int L, class V> V inv(const MatrixBase<T, L, V>& v)
{
    V r;
    T d = (T)0;
    T si = (T)1;
    for (int i = 0; i < L; i++)
    {
        T sj = si;
        for (int j = 0; j < L; j++)
        {
            Matrix<T, L - 1> sub;
            for (int k = 0; k < L - 1; k++)
                for (int l = 0; l < L - 1; l++)
                    sub(k, l) = v((k < j) ? k : k + 1, (l < i) ? l : l + 1);
            T dd = det(sub) * sj;
            r(i, j) = dd;
            d += dd * v(j, i);
            sj = -sj;
        }
        si = -si;
    }
    return r * rcp(d) * L;
}

//------------------------------------------------------------------------

template <class T, int L, class S> template <class V> void MatrixBase<T, L, S>::setRow(int idx, const VectorBase<T, L, V>& v)
{
    for (int i = 0; i < L; i++)
        get(idx, i) = v[i];
}

//------------------------------------------------------------------------

template <class T, int L, class S> template <class V> S MatrixBase<T, L, S>::preXlate(const VectorBase<T, L - 1, V>& v) const
{
    S r(*this);
    for (int i = 0; i < L - 1; i++)
        for (int j = 0; j < L; j++)
            r(i, j) += v[i] * get(L - 1, j);
    return r;
}

//------------------------------------------------------------------------

template <class T, int L, class S> template <class V> S MatrixBase<T, L, S>::postXlate(const VectorBase<T, L - 1, V>& v) const
{
    S r(*this);
    for (int i = 0; i < L; i++)
        for (int j = 0; j < L - 1; j++)
            r(i, L - 1) += r(i, j) * v[j];
    return r;
}

//------------------------------------------------------------------------

template <class T, int L, class S> template <class V> S MatrixBase<T, L, S>::preScale(const VectorBase<T, L - 1, V>& v) const
{
    S r(*this);
    for (int i = 0; i < L - 1; i++)
        for (int j = 0; j < L; j++)
            r(i, j) *= v[i];
    return r;
}

//------------------------------------------------------------------------

template <class T, int L, class S> template <class V> S MatrixBase<T, L, S>::postScale(const VectorBase<T, L - 1, V>& v) const
{
    S r(*this);
    for (int i = 0; i < L; i++)
        for (int j = 0; j < L - 1; j++)
            r(i, j) *= v[j];
    return r;
}

//------------------------------------------------------------------------

template <class T, int L, class S> template <class V> S MatrixBase<T, L, S>::preScale(const VectorBase<T, L, V>& v) const
{
    S r(*this);
    for (int i = 0; i < L; i++)
        for (int j = 0; j < L; j++)
            r(i, j) *= v[i];
    return r;
}

//------------------------------------------------------------------------

template <class T, int L, class S> template <class V> S MatrixBase<T, L, S>::postScale(const VectorBase<T, L, V>& v) const
{
    S r(*this);
    for (int i = 0; i < L; i++)
        for (int j = 0; j < L; j++)
            r(i, j) *= v[j];
    return r;
}

//------------------------------------------------------------------------

template <class T, int L, class S> template<class V> V MatrixBase<T, L, S>::operator*(const VectorBase<T, L, V>& v) const
{
    V r;
    for (int i = 0; i < L; i++)
    {
        T rr = (T)0;
        for (int j = 0; j < L; j++)
            rr += get(i, j) * v[j];
        r[i] = rr;
    }
    return r;
}

//------------------------------------------------------------------------

template <class T, int L, class S> template<class V> V MatrixBase<T, L, S>::operator*(const VectorBase<T, L - 1, V>& v) const
{
    V r;
    for (int i = 0; i < L - 1; i++)
    {
        T rr = get(i, L - 1);
        for (int j = 0; j < L - 1; j++)
            rr += get(i, j) * v[j];
        r[i] = rr;
    }
    return r;
}

//------------------------------------------------------------------------

template <class T, int L, class S> template <class V> S MatrixBase<T, L, S>::operator*(const MatrixBase<T, L, V>& v) const
{
    S r;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < L; j++)
        {
            T rr = (T)0;
            for (int k = 0; k < L; k++)
                rr += get(i, k) * v(k, j);
            r(i, j) = rr;
        }
    }
    return r;
}

//------------------------------------------------------------------------

template <class T, int L, class S> Matrix<T, L> outerProduct(const VectorBase<T, L, S>& a, const VectorBase<T, L, S>& b)
{
    Matrix<T, L> res;
    for (int i = 0; i < L; i++)
        for (int j = 0; j < L; j++)
            res.get(i, j) = a.get(i) * b.get(j);
    return res;
}

//------------------------------------------------------------------------
}
