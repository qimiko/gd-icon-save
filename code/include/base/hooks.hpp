#pragma once
#ifndef HOOKS_HPP
#define HOOKS_HPP

#include <dlfcn.h>
#include <string>
#include <unistd.h>
#include <cstring> // memcpy
#include <vector>
#include <sys/mman.h>

#include <dobby.h>
#include <cocos2dcpp.h>

extern void *GLOBAL_HANDLE;
extern void *GLOBAL_BASE;
extern size_t GLOBAL_PAGESIZE;

bool create_hook(uintptr_t target_fn, uintptr_t hook_fn, uintptr_t o_fn);
[[deprecated("this fn currently doesn't work with new hook system")]] bool remove_hook(uintptr_t addr);

void setup_handle();
void *get_sym_addr(const char *);

void *page_of(uintptr_t addr);
bool patch_single_byte(uint8_t *addr, uint8_t byte);
void patch_multiple_byte(uint8_t *addr, std::vector<uint8_t> bytes);

struct Hook
{
	uintptr_t orig_fn;
	uintptr_t hook_fn;
	uintptr_t trampoline_fn;
};

template <typename T>
T *ptr_to_offset(void *base, unsigned int offset)
{
	return reinterpret_cast<T *>(reinterpret_cast<uintptr_t>(base) + offset);
};

template <typename T>
T get_from_offset(void *base, unsigned int offset)
{
	return *ptr_to_offset<T>(base, offset);
};

#endif
