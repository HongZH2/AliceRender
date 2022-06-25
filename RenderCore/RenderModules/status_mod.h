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
  virtual void setDepthTestFunc(const AE_TEST_FUNC & func) = 0;
  // set StencilTEst Function
  virtual void setStencilTestFunc(const AE_TEST_FUNC & func, const int32_t & ref, const uint32_t & mask) = 0;
  virtual void setStencilOps(const AE_TEST_OPS & sfail, const AE_TEST_OPS & dpfail, const AE_TEST_OPS & dppass) = 0;
  // set blend Functon 
  virtual void setBlendFunc(const AE_BLEND_FUNC & sfunc, const AE_BLEND_FUNC & dfunc) = 0;
  // set Polygon Mode
  virtual void setPolygonMode(const AE_POLYGON_MODE_TYPE & pmode) = 0;

  // buffer clearing
  virtual void clearBuffer(const AE_COLOR_BUFFER_MASK & mask) = 0;
  virtual void setBufferColor(const GVec4 & color) = 0;
  // stencil mask 
  virtual void setStencilMask(const uint8_t & mask) = 0;

  virtual void setLineWidth(const float & width) = 0;
  virtual void setPointSize(const float & size) = 0;

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
    if(disable_list_.find(flag) != disable_list_.end()){
      disable_list_.erase(flag);
    }
    enable_list_.insert(flag);
    if constexpr (sizeof...(rest) != 0) pushEnableList(rest ...);
  }

  template<typename T, typename ... R>
  void pushDisableList(T && flag, R && ... rest){ // push status that you 'd like to disable 
    if(enable_list_.find(flag) != enable_list_.end()){
      enable_list_.erase(flag);
    }
    disable_list_.insert(flag);
    if constexpr (sizeof...(rest) != 0) pushDisableList(rest ...);
  }

  void setBufferColor(const GVec4 & color);  // delay status
  void clearBufferBit(const AE_COLOR_BUFFER_MASK & mask);
  void setViewPort(const GVec4i & rect); 
  void setLineWidth(const float & width);  
  void setPointSize(const float & size);
  void setDepthFunc(const AE_TEST_FUNC & dfunc);
  void setStencilFunc(const AE_TEST_FUNC & func, const int32_t & ref, const uint32_t & mask);
  void setStencilOps(const AE_TEST_OPS & sfail, const AE_TEST_OPS & dpfail, const AE_TEST_OPS & dppass);
  void setBlendFunc(const AE_BLEND_FUNC & sfunc, const AE_BLEND_FUNC & dfunc);
  void setPolygonMode(const AE_POLYGON_MODE_TYPE & pmode);
  void setStencilMask(const uint8_t & stencil_mask);

  StatusSaver();
  ~StatusSaver();
protected:

  enum OpsType{
    Ops_Buffer_Col = 1 << 1,
    Ops_Buffer_Msk = 1 << 2,
    Ops_ViewPort = 1 << 3,
    Ops_Line_Width = 1 << 4,
    Ops_Depth_Func = 1 << 5,
    Ops_Stencil_Func = 1 << 6,
    Ops_Stencil_Ops = 1 << 7,
    Ops_Blend_Func = 1 << 8,
    Ops_Polygon_model = 1 << 9,
    Ops_Stencil_Msk = 1 << 10,
    Ops_Point_Size = 1 << 11
  };

  struct StatusContainer{
    float line_width_ = 1.0f;
    float point_size_ = 1.0f;
    uint8_t stencil_mask_;
    uint8_t stencil_func_mask_;
    uint8_t stencil_ref_;
    GVec4i view_;
    GVec4 buffer_color_ = GVec4(0.0f);

    AE_TEST_FUNC depth_func_;
    AE_TEST_FUNC stencil_func_;
    AE_TEST_OPS sfail_;
    AE_TEST_OPS dpfail_;
    AE_TEST_OPS dppass_;
    AE_BLEND_FUNC src_func_;
    AE_BLEND_FUNC dst_func_;
    AE_POLYGON_MODE_TYPE polygon_mode_;
    AE_COLOR_BUFFER_MASK buffer_mask_ = AE_COLOR_BUFFER_BIT; 

    uint64_t ops_mask_ = 0x00000000; // operation mask for checking if the ops has been set before. 
  } prev_, cur_;

  std::set<AE_STATUS_TYPE> enable_list_;
  std::set<AE_STATUS_TYPE> disable_list_;
  std::vector<std::function<void(StatusContainer &)>> operations_;

  std::shared_ptr<StatusModule> status_ops_; 
};


}


#endif // ALICE_ENGINE_STATUS_MODULE_H