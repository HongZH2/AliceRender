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
  // set Polygon Mode
  virtual void setPolygonMode(const AE_POLYGON_MODE_TYPE & pmode) = 0;

  // buffer clearing
  virtual void clearBuffer(const AE_COLOR_BUFFER_MASK & mask) = 0;
  virtual void setBufferColor(const GVec4 & color) = 0;
  virtual void setLineWidth(const float & width) = 0;

  // viewport
  virtual void viewport(const GVec4i & rect) = 0;
  virtual GVec4i checkViewport() = 0;

protected:
  StatusModule();
};


/*
* Delayed status setting 
*/
class StatusSaver{
public:
  void saveAndApply(); // save status
  void resetStatus(); // reset
 
  template<typename T, typename ... R>
  void pushEnableList(T && flag, R && ... rest){  // push status that you 'd like to enable 
    enable_list_.push_back(flag);
    if constexpr (sizeof...(rest) != 0) pushEnableList(rest ...);
  }

  template<typename T, typename ... R>
  void pushDisableList(T && flag, R && ... rest){ // push status that you 'd like to disable 
    enable_list_.push_back(flag);
    if constexpr (sizeof...(rest) != 0) pushDisableList(rest ...);
  }

  void setBufferColor(const GVec4 & color);  // delay status
  void clearBufferBit(const AE_COLOR_BUFFER_MASK & mask);
  void setViewPort(const GVec4i & rect); 
  void setLineWidth(const float & width);  
  void setDepthFunc(const AE_DEPTH_TEST_FUNC & dfunc);
  void setBlendFunc(const AE_BLEND_FUNC & sfunc, const AE_BLEND_FUNC & dfunc);
  void setPolygonMode(const AE_POLYGON_MODE_TYPE & pmode);

  StatusSaver();
  ~StatusSaver();
protected:

  struct StatusContainer{
    float line_width_ = 1.0f;
    GVec4i view_;
    GVec4 buffer_color_ = GVec4(0.0f);

    AE_DEPTH_TEST_FUNC depth_func_;
    AE_BLEND_FUNC src_func_;
    AE_BLEND_FUNC dst_func_;
    AE_POLYGON_MODE_TYPE polygon_mode_;
    AE_COLOR_BUFFER_MASK buffer_mask_ = AE_COLOR_BUFFER_BIT;  
  } prev_, cur_;

  std::vector<AE_STATUS_TYPE> enable_list_;
  std::vector<AE_STATUS_TYPE> disable_list_;
  std::vector<std::function<void(StatusContainer &)>> operations_;

  std::shared_ptr<StatusModule> status_ops_; 
};


}


#endif // ALICE_ENGINE_STATUS_MODULE_H