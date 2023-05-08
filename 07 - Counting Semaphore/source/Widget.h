#pragma once
#include "DetailC.h"
#include "Module.h"

class Widget
{
public:
	Widget() = delete;
	Widget(const Module& module, const DetailC& detailC);
private:
	Module module;  // NOLINT(clang-diagnostic-unused-private-field)
	DetailC detailC;  // NOLINT(clang-diagnostic-unused-private-field)
};