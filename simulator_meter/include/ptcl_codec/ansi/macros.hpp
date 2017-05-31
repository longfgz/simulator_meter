#ifndef LCLWH8V2L8S6M7N9_PUBLIC_UTIL_MACROS
#define LCLWH8V2L8S6M7N9_PUBLIC_UTIL_MACROS

#include <boost/preprocessor/cat.hpp> 
#include <boost/preprocessor/comparison/equal.hpp> 
#include <boost/preprocessor/control/if.hpp>

// �ڲ�ʹ�õĺ�
#define NORMAL_PARAMETER(type_)   type_ data
#define REF_PARAMETER(type_)      type_ const &data

// �ڲ�ʹ�õĺ�
#define FUNC_PARAMETER_(type_, use_ref_)                              \
  BOOST_PP_IF( BOOST_PP_EQUAL(use_ref_, 0)                            \
    , NORMAL_PARAMETER(type_)                                         \
    , REF_PARAMETER(type_) )

// ��Ϊ��Ӱ������ڴ沼�֣����Դ˺�δ������ĳ�Ա�����Ķ���
#define DEFINE_MEMBER_ACCESSOR(type_, mem_, func_, use_ref_)          \
	public: inline void set_##func_(FUNC_PARAMETER_(type_, use_ref_))   \
          { mem_ = data; };                                           \
	public: inline type_ get_##func_() const { return mem_; };

// Ϊ��Ԫ���Կ�����ķ���Ȩ��
// Mock�ܷ���ģ������Ա����
#ifdef UNIT_TEST
#   define TEST_ACCESS public:
    // ATTENTION !!!!!!!!!!!!
    // virtual �ؼ��ֿ��ܻ�ı������ڴ沼�֣���ע�⵽�˵��ʹ��
#   define TEST_VIRTUAL virtual
    // ����������������࣬��ʹ������ĺ궨��һ�����Է�ֹ����ʱ��Դй¶
#   define TEST_VIRTUAL_DESTRUCTOR(class_name_) \
      public: virtual ~class_name_() {}
#else
#   define TEST_ACCESS
#   define TEST_VIRTUAL
#   define TEST_VIRTUAL_DESTRUCTOR(class_name_)
#endif  // #ifdef UNIT_TEST

#endif  // #ifndef LCLWH8V2L8S6M7N9_PUBLIC_UTIL_MACROS