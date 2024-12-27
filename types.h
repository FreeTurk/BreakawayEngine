#pragma once

#include <functional>
#include <tuple>
#include <vector>

typedef std::function<void()> Callback;
typedef std::tuple<int, int, int, int> RGBA;
typedef std::vector<RGBA> Line;
typedef std::vector<Line> Matrix;
typedef std::vector<Matrix> Matrix3D;