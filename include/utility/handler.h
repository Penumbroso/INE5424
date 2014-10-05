// EPOS Handler Utility Declarations

#ifndef __handler_h
#define __handler_h

#include <system/config.h>
#include <new>

__BEGIN_SYS

struct Handler {
    virtual void operator()() = 0;
    virtual ~Handler() {}
};

namespace detail {
    template< typename Callable >
    struct HandlerFunction : Handler {
        Callable f;
        HandlerFunction( Callable& f ) : f( f ) {}
        virtual void operator()() {
            f();
        }
    };
}

template< typename Callable >
Handler * makeHandler( Callable c ) {
    return new (SYSTEM) detail::HandlerFunction<Callable>( c );
}

__END_SYS

#endif
