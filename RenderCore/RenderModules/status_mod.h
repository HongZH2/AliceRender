//
// Created by HongZh on 2022/02/25, 10:59:02
//

#ifndef ALICE_ENGINE_STATUS_MODULE_H
#define ALICE_ENGINE_STATUS_MODULE_H

#include "module_predeclared.h"

namespace AliceAPI {


class StatusModule {
public:
  virtual ~StatusModule();
  static std::shared_ptr<StatusModule> getInstancePtr();

  // enable status 
  virtual void enableStatus(const AE_STATUS_TYPE & stype, const int32_t & var) = 0;
  virtual int32_t checkStatus(const AE_STATUS_TYPE & stype) = 0;

  // set DepthTest Function
  virtual void setDepthTestFunc(const AE_DEPTH_TEST_FUNC & func) = 0;
  // set blend Functon 
  virtual void setBlendFunc(const AE_BLEND_FUNC & sfunc, const AE_BLEND_FUNC & dfunc) = 0;

  // buffer clearing
  virtual void clearColorBuffer() = 0;
  virtual void clearDepthBuffer() = 0;
  virtual void clearStencilBuffer() = 0;
  virtual void clearAllBuffer() = 0;
  virtual void setBufferColor(const GVec4 & color) = 0;
  virtual void setLineWidth(const float & width) = 0;

  // viewport
  virtual void viewport(const GVec4i & rect) = 0;
  virtual GVec4i checkViewport() = 0;

protected:
  StatusModule();
};

// status flag for applying setting 
enum StatusFlag {
  NoneSetting = 0,
  SetBufferColor = 1 << 1,
  SetViewport = 1 << 2,  
  SetLineWidth = 1 << 3,
  RefleshColor = 1 << 4,
  RefleshDepth = 1 << 5,
  RefleshStencil = 1 << 6,
  RefleshAll = RefleshColor | RefleshDepth | RefleshStencil,
  EnableDepthTest = 1 << 7,
  DisableDepthTest = 1 << 8,
  EnableFaceCull = 1 << 9,
  DisableFaceCull = 1 << 10,
  EnableBlend = 1 << 11,
  DisableBlend = 1 << 12
};  

/*
* Delayed status setting 
*/
class StatusSaver{
public:
  void saveAndApply(uint64_t setting);  // TODO: remove
  void saveAndApply(); // save status
  void resetStatus(); // reset
  void setBufferColor(const GVec4 & color);  // delay status
  void setViewPort(const GVec4i & rect); // delay status
  void setLineWidth(const float & width);  
  void setDepthFunc(const AE_DEPTH_TEST_FUNC & dfunc);
  void setBlendFunc(const AE_BLEND_FUNC & sfunc, const AE_BLEND_FUNC & dfunc);

  StatusSaver();
  StatusSaver(const uint64_t & setting);
  ~StatusSaver();
protected:
  void applyStatus(const uint64_t & setting);
  struct StatusContainer{
    float line_width_ = 1.0f;
    GVec4i view_;
    GVec4 buffer_color_ = GVec4(0.0f);

    AE_DEPTH_TEST_FUNC depth_func_;
    AE_BLEND_FUNC src_func_;
    AE_BLEND_FUNC dst_func_;

    uint64_t setting_ = 0;  
  } prev_, cur_;
  
  bool is_initilized_ = false;

  std::shared_ptr<StatusModule> status_ops_; 
};


}


#endif // ALICE_ENGINE_STATUS_MODULE_H