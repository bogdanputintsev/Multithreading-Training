#pragma once
#include "DetailA.h"
#include "DetailB.h"

class Module final
{
public:
	Module() = delete;
	Module(const DetailA& detailA, const DetailB& detailB) noexcept;
private:
	DetailA detailA;  // NOLINT(clang-diagnostic-unused-private-field)
	DetailB detailB;  // NOLINT(clang-diagnostic-unused-private-field)
};