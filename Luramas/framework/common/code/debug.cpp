#include "../debug.hpp"
#ifdef _WIN32
#include <Windows.h>
#endif

std::string LURMAS_GLOBAL_PDUMP;

namespace luramas::debug {
#ifdef _WIN32
      void copy_to_clipboard(const std::string &str) {
            if (!OpenClipboard(nullptr)) {
                  return;
            }
            EmptyClipboard();
            const auto h_global = GlobalAlloc(GMEM_MOVEABLE, str.size() + 1u);
            if (!h_global) {
                  CloseClipboard();
                  return;
            }
            std::memcpy(static_cast<char *>(GlobalLock(h_global)), str.c_str(), str.size() + 1u);
            GlobalUnlock(h_global);
            SetClipboardData(CF_TEXT, h_global);
            CloseClipboard();
            GlobalFree(h_global);
            return;
      }
#endif
} // namespace luramas::debug