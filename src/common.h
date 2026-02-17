#pragma once

#include <cstdint>
#include <memory>

typedef int8_t	 i8;
typedef int16_t	 i16;
typedef int32_t	 i32;
typedef int64_t	 i64;
typedef uint8_t	 u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

#define STRINGIFY(x)  _STRINGIFY(x)
#define _STRINGIFY(x) #x

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T, typename... Args>
Scope<T> CreateScope(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
Ref<T> CreateRef(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}