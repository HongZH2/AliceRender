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

// status container for applying setting 
 enum StatusSetting {
  none_setting = 0,
  set_colorbuffer = 1 << 1,
  set_viewport = 1 << 2,
  reflesh_color = 1 << 3,
  reflesh_depth = 1 << 4,
  reflesh_stencil = 1 << 5,
  reflesh_all_buffer = reflesh_depth | reflesh_color | reflesh_stencil,
  depth_test = 1 << 6,
  cull_face = 1 << 7,
  blend = 1 << 8,   // TODO: 
  set_line_width = 1 << 9,
  all_default = reflesh_color | reflesh_depth | reflesh_stencil | depth_test | cull_face | blend
};  

// TODO: read/write color buffer

class StatusContainer{
public:
  StatusContainer();
  StatusContainer(const int32_t & setting);
  ~StatusContainer();  

  void applyStatus(const int32_t & status_setting);  
  virtual void setBufferColor(const GVec4 & color);  // set color buffer immediatelly
  virtual void setViewPort(const GVec4i & rect); // set viewport immediatelly
  virtual void setLineWidth(const float & width);  // set line width
protected:
  int32_t status_setting_ = 0;
  float line_width_ = 1.0f;
  AE_BLEND_FUNC blend_func_s_;
  AE_BLEND_FUNC blend_func_d_;
  AE_DEPTH_TEST_FUNC depth_func_;
  GVec4i view_;
  GVec4 color_ = GVec4(0.0f);
  std::shared_ptr<StatusModule> status_ops_ = StatusModule::getInstancePtr();;
};


class StatusSaver: public StatusContainer{
public:
  void saveAndApply(int32_t setting);  // TODO: remove
  void saveAndApply(); // save status
  void resetStatus(); // reset
  void setBufferColor(const GVec4 & color) override;  // delay status
  void setViewPort(const GVec4i & rect) override; // delay status
  void setLineWidth(const float & width) override;  
  void setDepthFunc(const AE_DEPTH_TEST_FUNC & dfunc);
  void setBlendFunc(const AE_BLEND_FUNC & sfunc, const AE_BLEND_FUNC & dfunc);

  StatusSaver();
  StatusSaver(const int32_t & setting);
  ~StatusSaver();
protected:
  bool is_initilized_ = false; 
  int32_t prev_setting_ = 0;
  float prev_line_width = 1.0f;
  GVec4i prev_view_;
  GVec4 prev_color_ = GVec4(0.0f);
};


}


#endif // ALICE_ENGINE_STATUS_MODULE_H