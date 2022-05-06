//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICE_ENGINE_ENGINE_MATH_H
#define ALICE_ENGINE_ENGINE_MATH_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include <math.h>

namespace AliceAPI {


// vector
typedef glm::vec3 GVec3;
typedef glm::vec2 GVec2;
typedef glm::vec4 GVec4;

typedef glm::ivec4 GVec2i;
typedef glm::ivec4 GVec3i;
typedef glm::ivec4 GVec4i;

typedef glm::quat GQuat;

// matrix
typedef glm::mat3x3 GMat3;
typedef glm::mat4x4 GMat4;
typedef glm::mat2x2 GMat2;

// functions



template <typename T> 
inline GQuat GQuatCast( T const& rot_mat){
   return glm::quat_cast(rot_mat);
}

inline GMat4 GMat4Cast( GQuat const& rot_quat){
   return glm::mat4_cast(rot_quat);
}

inline GMat4 GMat3Cast( GQuat const& rot_quat){
   return glm::mat3_cast(rot_quat);
}

inline GVec3 GQuat2Euler(GQuat const& rot_quat){
    return glm::eulerAngles(rot_quat);
}

inline bool GDecomposeMat(GMat4 & mat, GVec3 & scale, GQuat & quat, GVec3 & translation, GVec3 & skew, GVec4 & perspective){
    return glm::decompose(mat, scale, quat, translation, skew, perspective);
}

template <typename T>
inline T GDot (T const& vec1, T const& vec2){
    return glm::dot(vec1, vec2);
}

template <typename T>
inline T GNormalize (T const& vec){
    return glm::normalize(vec);
}

template <typename T>
inline T GCross (T const& vec1, T const& vec2){
    return glm::cross(vec1, vec2);
}

template <typename T>
inline T GRadians (T const& val){
    return glm::radians(val);
}

//TODO
// translation
template <typename T>
inline T GTranslate (T const& mat, GVec3 const& vec){
    return glm::translate(mat, vec);
}

// scaling
template <typename T>
inline T GScale (T const& mat, GVec3 const& vec){
    return glm::scale(mat, vec);
}

// translation
template <typename T>
inline T GRotate (T const& mat, float angle, GVec3 const& vec){
    return glm::rotate(mat, GRadians(angle), vec);
}

// lookAt transformation
inline GMat4 GLookAt(GVec3 const & pos, GVec3 const& center, GVec3 const& up){
    return glm::lookAt(pos, center, up);
}

// perspective transformation
template <typename T>
inline GMat4 GPerspective(T const& fovy, T const& ratio, T const& near, T const& far){
    return glm::perspective(fovy, ratio, near, far);
}

// orth
template <typename T>
inline GMat4 GOrtho(T const& left, T const& right,  T const& top, T const& bottom, T const& near, T const& far){
    return glm::ortho(left, right, top, bottom, near, far);
}

// inverse
template <typename T>
inline T GInverse(T const & mat){
    return glm::inverse(mat);
}

// transpose
template <typename T>
inline T Gtranspose(T const & mat){
    return glm::transpose(mat);
}

}


#endif //ALICE_ENGINE_ENGINE_MATH_H
