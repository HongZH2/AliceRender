//
// Created by HongZh on 2022/06/22, 00:57:00
//

#ifndef ALICE_ENGINE_RENDER_HELPER_H
#define ALICE_ENGINE_RENDER_HELPER_H

#include <type_traits>
namespace AliceAPI {

/*
*  a helper function for checking T is one type of Arguments
*/
template <typename T1, typename T2, typename ... Args>
constexpr bool isOneOfType(){
    if constexpr (std::is_same_v<T1, T2>) return true;
    if constexpr (sizeof...(Args) != 0) return isOneOfType<T1, Args...>();
    return false;
}

}

#endif //ALICE_ENGINE_RENDER_HELPER_H