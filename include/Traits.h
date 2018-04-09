//
// Created by leo on 18-4-9.
//

#ifndef THREAD_TRAITS_H
#define THREAD_TRAITS_H

namespace __CThread {

    template<typename T>
    struct LambdaTraits
            : LambdaTraits<decltype(&T::operator())> {
    };

    template<typename C, typename R, typename ... Args>
    struct LambdaTraits<R (C::*)(Args...) const> {
        using ReturnType = R;
        using ClassType = C;
    };

}

#endif //THREAD_TRAITS_H
