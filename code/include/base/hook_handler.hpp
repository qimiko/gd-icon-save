#pragma once
#ifndef HOOK_HANDLER_HPP
#define HOOK_HANDLER_HPP

#include <algorithm>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "hooks.hpp"

class HookHandler {
protected:
    void _add_hook_from_list(uintptr_t orig, uintptr_t hook, uintptr_t trampoline, int32_t priority = 0);

    // <orig_fn_addr, <hook_fn_addr, trampoline_fn_addr>>
    typedef std::unordered_map<uintptr_t, std::pair<uintptr_t, uintptr_t>> _internal_hook_t;

    std::unordered_map<int, std::vector<Hook>> _hook_list;

public:
    static HookHandler& get_handler();

    // priority system is lower numbers take priority over lower ones, thus -1000 will probably always run first
    template <int32_t V, typename T, typename U, typename = typename std::enable_if<std::is_function<U>::value>::type>
    HookHandler& add_hook(const T orig, const U* hook_fn, U** trampoline_fn)
    {
        this->_add_hook_from_list(reinterpret_cast<uintptr_t>(orig), reinterpret_cast<uintptr_t>(hook_fn), reinterpret_cast<uintptr_t>(trampoline_fn), V);
        return *this;
    };

    template <typename T, typename U, typename = typename std::enable_if<std::is_function<U>::value>::type>
    HookHandler& add_hook(const T orig, const U* hook_fn, U** trampoline_fn)
    {
        this->_add_hook_from_list(reinterpret_cast<uintptr_t>(orig), reinterpret_cast<uintptr_t>(hook_fn), reinterpret_cast<uintptr_t>(trampoline_fn));
        return *this;
    };

    HookHandler& install_patch(const uintptr_t rel_addr, const std::vector<uint8_t>& bytes)
    {
        auto patch_ptr = ptr_to_offset<uint8_t>(GLOBAL_BASE, rel_addr);
        patch_multiple_byte(patch_ptr, bytes);

        return *this;
    }

    // this can and really only should be run once, beyond that and you'll overwrite things for no reason
    void install_hooks();

    HookHandler(HookHandler const&) = delete;
    void operator=(HookHandler const&) = delete;

protected:
    void _resolve_hook_to_map(Hook& hook, _internal_hook_t& hook_list);

    [[nodiscard]]
    std::vector<Hook>& _get_hook_list_by_priority(const int32_t pri)
    {
        // insert returns an <iterator, bool> even if keys conflict
        auto pri_it = this->_hook_list.insert({ pri, {} });

        // thus this strange access method lol
        return pri_it.first->second;
    }

private:
    HookHandler() { }
};

#endif