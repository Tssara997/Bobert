#pragma once

#ifdef Bobert_EXPORTS
  #define Bobert_API __declspec(dllexport)
#else
  #define Bobert_API __declspec(dllimport)
#endif


namespace Bobert {
  Bobert_API void Print();
}