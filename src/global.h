#pragma once

#ifndef JUNUO_BASE_EXPORT
#	ifdef JUNUO_BASE_MODULE
#		define JUNUO_BASE_EXPORT __declspec(dllexport)
#	else
#		define JUNUO_BASE_EXPORT __declspec(dllimport)
#	endif
#endif
