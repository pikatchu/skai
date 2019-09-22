#include <arrayfire.h>
#include "skip/Finalized.h"
#include "skip/util.h"

extern "C" {

  skip::RObj* SKIP_ArrayFire_constant(double value, long dim) {
    auto arr = af::constant(value, dim);
    auto result = skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
    return result;
  }

  skip::RObj* SKIP_ArrayFire_randu(long dim1, long ndims, long dim2, long dim3, long dim4) {
    switch (ndims) {
      case 0:
      {
        auto arr = af::randu(dim1);
        auto result = skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
        return result;
      }
      case 1:
      {
        auto arr = af::randu(dim1, dim2);
        auto result = skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
        return result;
      }
      case 2:
      {
        auto arr = af::randu(dim1, dim2, dim3);
        auto result = skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
        return result;
      }
      case 3:
      {
        auto arr = af::randu(dim1, dim2, dim3, dim4);
        auto result = skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
        return result;
      }
      default:
        break;
    }
  }

  double SKIP_ArrayFire_scalar(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    return internal->m_cppClass.scalar<float>();
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

    try {
      auto arr = internal1->m_cppClass * internal2->m_cppClass;
      return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
    } catch(std::exception e) {
      skip::printStackTrace();
      throw e;
    }
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

  long SKIP_ArrayFire_numDims(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj)->m_cppClass;
    auto dims = internal.numdims();

    return dims;
  }

  long SKIP_ArrayFire_getDim(skip::RObj* obj, long i) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj)->m_cppClass;
    auto dim = internal.dims(i);

    return dim;
  }

  skip::RObj* SKIP_ArrayFire_getDims(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj)->m_cppClass;
    auto dims = internal.dims();
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), dims);
  }

  skip::RObj* SKIP_ArrayFire_getType(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj)->m_cppClass;
    auto type = internal.type();
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), type);
  }

  skip::RObj* SKIP_ArrayFire_constant_one(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = af::constant(1, internal->m_cppClass.dims());
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_exp(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = af::exp(internal->m_cppClass);
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_sin(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = af::sin(internal->m_cppClass);
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_cos(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = af::cos(internal->m_cppClass);
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_tan(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = af::tan(internal->m_cppClass);
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

  skip::RObj* SKIP_ArrayFire_matmul(skip::RObj* obj1, skip::RObj* obj2) {
    auto internal1 = static_cast<skip::Finalized<af::array>*>(obj1);
    auto internal2 = static_cast<skip::Finalized<af::array>*>(obj2);

    try {
      auto arr = af::matmul(internal1->m_cppClass, internal2->m_cppClass);
      return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
    } catch(std::exception e) {
      skip::printStackTrace();
      throw e;
    }

  }

  skip::RObj* SKIP_ArrayFire_transpose(skip::RObj* obj) {
    auto internal = static_cast<skip::Finalized<af::array>*>(obj);
    auto arr = af::transpose(internal->m_cppClass);
    return skip::Finalized<af::array>::createNew(skip::Obstack::cur(), arr);
  }

}
