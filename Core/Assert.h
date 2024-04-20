#pragma once

#include <iostream>

#define ASSERT(condition) if (!condition) __builtin_trap();
