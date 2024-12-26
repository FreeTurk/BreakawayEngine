#pragma once

#include <functional>
#include <tuple>
#include <vector>

typedef std::function<void()> Callback;
typedef std::tuple<int, int, int> RGB;
typedef std::vector<RGB> Line;
typedef std::vector<Line> Matrix;