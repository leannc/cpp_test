//
// Created by kang on 2024/10/9.
//
#include "UseCase.h"
#include <tuple>
#include <unordered_map>

using Name = std::string;

struct AD {
  AD(int a) : a_(a) {}
  int a_;
};
struct DA {
  DA(int a) : a_(a) {}
  int a_;
};

template <typename DeviceT>
class Components {
 private:
  std::unordered_map<Name, DeviceT> devices_;  // 假设用 unordered_map 存储，键为 Name，值为设备对象
 public:
  DeviceT* Get(const Name& name) {
    auto it = devices_.find(name);
    if (it != devices_.end()) { return &(it->second); }
    return nullptr;  // 没找到返回空指针
  }
  // 这里通常还会有 Add、Remove 等方法，为了简洁省略
  void Add(const Name& name, const DeviceT& device) { devices_.insert(std::make_pair(name, device)); }
};

template <typename... DeviceTypes>
class DeviceManager {
 public:
  DeviceManager() = default;

  // 核心：通用的 Get 方法模板
  template <typename TargetDeviceT>  // 目标设备类型
  TargetDeviceT* Get(const Name& name) {
    // 从 tuple 中找到存储对应类型 Components 的那个，并调用其 Get 方法
    return &(std::get<Components<TargetDeviceT>>(componentTuples_).Get(name));
    // 注意：这里假设 Components<TargetDeviceT> 类型一定在 DeviceTypes... 中，否则编译失败
  }

  // 可选：提供 Add 方法的模板（如果你需要的话）
  template <typename TargetDeviceT>
  void Add(const Name& name, const TargetDeviceT& device) {
    // 同样找到对应的 Components，然后调用其 Add 方法
    // 假设你的 Components<T> 有 Add 方法
    std::get<Components<TargetDeviceT>>(componentTuples_).Add(name, device);
  }

 private:
  std::tuple<Components<DeviceTypes>...> componentTuples_;
};

void variadic_template_member_attributes() {
  DeviceManager<AD, DA> myDeviceManager;
  myDeviceManager.Add<AD>("ad1", AD(1));
  myDeviceManager.Add<AD>("ad2", AD(2));
  myDeviceManager.Add<DA>("DA11", DA(11));
  myDeviceManager.Add<DA>("DA22", DA(22));

  // 3. 获取设备 - 现在语法更统一了
  AD* ad_ptr = myDeviceManager.Get<AD>("ad1");
  std::cout << ad_ptr->a_ << std::endl;

  DA* da_ptr = myDeviceManager.Get<DA>("DA11");
  std::cout << da_ptr->a_ << std::endl;
}
