// EPOS Handler Utility Declarations

#ifndef __handler_h
#define __handler_h

#include <system/config.h>
#include <system/kmalloc.h>

__BEGIN_SYS


struct Handler {
    virtual void operator()() = 0;
    virtual Handler * clone() = 0;
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
        HandlerFunction * clone() {
            return this;
            //return new HandlerFunction( *this ); FIXME
        }
    };
}

template< typename Callable >
Handler * makeHandler( Callable c ) {
    return knew<detail::HandlerFunction<Callable>>( c );
}

__END_SYS

#endif
