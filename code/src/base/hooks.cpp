#include "base/hooks.hpp"

void* GLOBAL_HANDLE = nullptr;
void* GLOBAL_BASE = nullptr;
size_t GLOBAL_PAGESIZE;

bool create_hook(uintptr_t target_fn, uintptr_t hook_fn, uintptr_t o_fn)
{
    DobbyHook(reinterpret_cast<void*>(target_fn),
        reinterpret_cast<void*>(hook_fn), reinterpret_cast<void**>(o_fn));

    return true;
}

bool remove_hook(uintptr_t addr)
{
    DobbyDestroy(reinterpret_cast<void*>(addr));

    return true;
}

void setup_handle()
{
    Dl_info p;
    dladdr((void*)&AppDelegate::get, &p);

    GLOBAL_BASE = p.dli_fbase;

    auto handle = dlopen("libcocos2dcpp.so", RTLD_NOW);
    GLOBAL_HANDLE = handle;

    GLOBAL_PAGESIZE = sysconf(_SC_PAGESIZE);
}

void* get_sym_addr(const char* sym_name)
{
    if (GLOBAL_HANDLE == nullptr)
        return nullptr;

    return dlsym(GLOBAL_HANDLE, sym_name);
}

// https://stackoverflow.com/a/20382241
void* page_of(uintptr_t addr)
{
    return reinterpret_cast<void*>((addr) & ~(GLOBAL_PAGESIZE - 1));
}

bool patch_single_byte(uint8_t* addr, uint8_t byte)
{
    void* ptr_page = page_of(reinterpret_cast<uintptr_t>(addr));

    if (mprotect(ptr_page, GLOBAL_PAGESIZE, PROT_WRITE | PROT_EXEC | PROT_READ) == 0) {
        std::memset(addr, byte, sizeof(byte));
        mprotect(ptr_page, GLOBAL_PAGESIZE, PROT_EXEC | PROT_READ);

        return true;
    } else {
        return false;
    }
}

void patch_multiple_byte(uint8_t* addr, std::vector<uint8_t> bytes)
{
    auto curr_addr = addr;

    for (const auto byte : bytes) {
        patch_single_byte(addr, byte);
        addr += 0x1;
    }
}