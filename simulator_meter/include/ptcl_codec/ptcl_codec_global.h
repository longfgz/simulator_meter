#pragma once

#include <string>
#include <string.h>

#ifdef WIN32
  #define PTCL_CODEC_EXPORT __declspec(dllexport)
#else
  #define PTCL_CODEC_EXPORT
#endif

#define PTCL_YNDY_PROTOCOL			//���ϵ�ѹ�������ʾ