#ifndef LIB_INCLUDE_TICK_PROX_PROX_GROUP_L1_H_
#define LIB_INCLUDE_TICK_PROX_PROX_GROUP_L1_H_

// License: BSD 3 clause

#include "prox_with_groups.h"

template <class T>
class DLL_PUBLIC TProxGroupL1 : public TProxWithGroups<T> {
 public:
  using TProxWithGroups<T>::get_class_name;

 protected:
  std::unique_ptr<TProx<T> > build_prox(T strength, ulong start, ulong end,
                                        bool positive) override;

 public:
  // This exists soley for cereal/swig
  TProxGroupL1() : TProxGroupL1(0, nullptr, nullptr, false) {}

  TProxGroupL1(T strength, SArrayULongPtr blocks_start,
               SArrayULongPtr blocks_length, bool positive)
      : TProxWithGroups<T>(strength, blocks_start, blocks_length, positive) {}

  TProxGroupL1(T strength, SArrayULongPtr blocks_start,
               SArrayULongPtr blocks_length, ulong start, ulong end,
               bool positive)
      : TProxWithGroups<T>(strength, blocks_start, blocks_length, start, end,
                           positive) {}

  template <class Archive>
  void serialize(Archive& ar) {
    ar(cereal::make_nvp("ProxWithGroups", cereal::base_class<TProx<T> >(this)));
  }

  BoolStrReport compare(const TProxGroupL1<T>& that) {
    std::stringstream ss;
    ss << get_class_name();
    auto are_equal = TProxWithGroups<T>::compare(that, ss);
    return BoolStrReport(are_equal, ss.str());
  }
  BoolStrReport operator==(const TProxGroupL1<T>& that) {
    return compare(that);
  }
};

using ProxGroupL1 = TProxGroupL1<double>;
using ProxGroupL1Double = TProxGroupL1<double>;
using ProxGroupL1Float = TProxGroupL1<float>;

CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(ProxGroupL1Double,
                                   cereal::specialization::member_serialize)
CEREAL_REGISTER_TYPE(ProxGroupL1Double)

CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(ProxGroupL1Float,
                                   cereal::specialization::member_serialize)
CEREAL_REGISTER_TYPE(ProxGroupL1Float)

#endif  // LIB_INCLUDE_TICK_PROX_PROX_GROUP_L1_H_
