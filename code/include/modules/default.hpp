#pragma once
#ifndef MODULES_DEFAULT_HPP
#define MODULES_DEFAULT_HPP

#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include <array>
#include <vector>

#include <cocos2dcpp.h>

#include "base/module.hpp"
#include "base/cmake_config.hpp"
#include "base/hooks.hpp"
#include "base/hook_handler.hpp"

namespace Default
{
	class Module : public Base::Module
	{
	protected:
		void on_initialize();
	};
}

#endif
