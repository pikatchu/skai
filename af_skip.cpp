#include<arrayfire.h>
#include "skip/Finalized.h"

extern "C" {

  skip::RObj* SKIP_ArrayFire_constant(double value, long dim) {
    auto arr = af::constant(value, dim);
    auto result = skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
    return result;
  }

  skip::RObj* SKIP_ArrayFire_randu(long dim) {
    auto arr = af::randu(dim);
    auto result = skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
    return result;
  }

  void SKIP_ArrayFire_print(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    af::print("", internal->m_cppClass);
  }

  void SKIP_ArrayFire_eval(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    af::eval(internal->m_cppClass);
  }

  skip::RObj* SKIP_ArrayFire_abs(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = af::abs(internal->m_cppClass);
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_lt_av(skip::RObj* obj, double value) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = internal->m_cppClass < value;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_mult_aa(skip::RObj* obj1, skip::RObj* obj2) {
    auto internal1 = static_cast<skip::Finalized<af::array>*>(obj1);
    auto internal2 = static_cast<skip::Finalized<af::array>*>(obj2);
    auto arr = internal1->m_cppClass * internal2->m_cppClass;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_mult_ia(long n, skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = n * internal->m_cppClass;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_mult_fa(double value, skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = value * internal->m_cppClass;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_plus_aa(skip::RObj* obj1, skip::RObj* obj2) {
    auto internal1 = static_cast<skip::Finalized<af::array>*>(obj1);
    auto internal2 = static_cast<skip::Finalized<af::array>*>(obj2);
    auto arr = internal1->m_cppClass + internal2->m_cppClass;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_plus_fa(double value, skip::RObj* obj) {
    auto internal2 = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = value + internal2->m_cppClass;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_minus_aa(skip::RObj* obj1, skip::RObj* obj2) {
    auto internal1 = static_cast<skip::Finalized<af::array>*>(obj1);
    auto internal2 = static_cast<skip::Finalized<af::array>*>(obj2);
    auto arr = internal1->m_cppClass - internal2->m_cppClass;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_minus_fa(double value, skip::RObj* obj) {
    auto internal2 = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = value - internal2->m_cppClass;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_negate(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = - internal->m_cppClass;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_div_aa(skip::RObj* obj1, skip::RObj* obj2) {
    auto internal1 = static_cast<skip::Finalized<af::array>*>(obj1);
    auto internal2 = static_cast<skip::Finalized<af::array>*>(obj2);
    auto arr = internal1->m_cppClass / internal2->m_cppClass;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_div_fa(double value, skip::RObj* obj) {
    auto internal2 = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = value / internal2->m_cppClass;
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  bool SKIP_ArrayFire_allTrue(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    return af::allTrue<bool>(internal->m_cppClass);
  }

  skip::RObj* SKIP_ArrayFire_constant_of_int(long value, skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj)->m_cppClass;
    auto arr = af::constant(value, internal.dims(), internal.type());
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }


  skip::RObj* SKIP_ArrayFire_constant_one(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = af::constant(1, internal->m_cppClass.dims());
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

}
