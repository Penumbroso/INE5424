// EPOS Metaprograms

#ifndef __meta_h
#define __meta_h

__BEGIN_SYS

// Sum metaprogram
template< typename ... Ts >
struct TypeSum {
    const static unsigned value = 0;
};
template< typename Head, typename ... Tail >
struct TypeSum<Head, Tail...> {
    const static unsigned value = sizeof(Head) + TypeSum<Tail...>::value;
};

// IF metaprogram
template<bool condition, typename Then, typename Else>
struct IF 
{ typedef Then Result; };

template<typename Then, typename Else>
struct IF<false, Then, Else>
{ typedef Else Result; };

// IF metaprogram for integer
template<bool condition, int Then, int Else>
struct IF_INT
{ enum { Result = Then }; };

template<int Then, int Else>
struct IF_INT<false, Then, Else>
{ enum { Result = Else }; };

//SWITCH-CASE metaprogram
const int DEFAULT = ~(~0u >> 1); //Initialize with the smallest int

struct Nil_Case {};

template <int tag_, typename Type_, typename Next_ = Nil_Case>
struct CASE
{ 
    enum { tag = tag_ }; 
    typedef Type_ Type;
    typedef Next_ Next;
};

template<int tag, typename Case>
class SWITCH
{
    typedef typename Case::Next Next_Case;
    enum { 
        case_tag = Case::tag, 
        found = ( case_tag == tag || case_tag == DEFAULT  )
    };
public:
    typedef typename IF<found, typename Case::Type,
        typename SWITCH<tag, Next_Case>::Result>::Result Result;
};

template<int tag>
class SWITCH<tag, Nil_Case>
{
public:
    typedef Nil_Case Result;
};

// EQUAL metaprogram
template<typename T1, typename T2>
struct EQUAL 
{ enum { Result = false }; };

template<typename T>
struct EQUAL<T, T>
{ enum { Result = true }; };


// LIST metaprogram
template< typename ... Ts > class LIST {};

template< typename _Head, typename ... _Tail >
class LIST< _Head, _Tail... >
{
private:
    typedef _Head Head;
    typedef LIST< _Tail... > Tail;

public:
    enum { Length = Tail::Length + 1 };

    template<int Index, int Current = 0, bool Stop = (Index == Current)>
    struct Get
    { typedef typename Tail::template Get<Index, Current + 1>::Result Result; };

    template<int Index, int Current>
    struct Get<Index, Current, true>
    { typedef Head Result; };

    template<typename Type>
    struct Count
    { enum { Result = EQUAL<Head, Type>::Result + Tail::template Count<Type>::Result }; };

    enum { Polymorphic = (int(Length) != int(Count<Head>::Result)) };
};

template <>
struct LIST<>
{ 
    enum { Length = 0 }; 

    template<int Index, int Current = 0>
    struct Get
    { typedef void Result; };

    template<typename Type>
    struct Count
    { enum { Result = 0 }; };

    enum { Polymorphic = false };
};

__END_SYS

#endif
