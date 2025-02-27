﻿#include "Aoba/UnifiedFont.hpp"

#include "Aoba/PixelUnit.hpp"

namespace s3d::aoba::UnifiedFont {
    Array<std::shared_ptr<Font>> Fonts;

    namespace Internal {
        void RegisterFont(int32 size) {
            Fonts.emplace_back(std::make_shared<Font>(Font(size, Typeface::Regular)));
            Fonts.emplace_back(std::make_shared<Font>(Font(size, Typeface::Light)));
            Fonts.emplace_back(std::make_shared<Font>(Font(size, Typeface::Bold)));
        }
    }

    void Initialize() {
        // Default
        Internal::RegisterFont(13_px);

        // Caption
        Internal::RegisterFont(10_px);

        // Header
        Internal::RegisterFont(18_px);
    }

    const Font& Get(UnifiedFontStyle style) {
        return *Fonts[static_cast<size_t>(style)].get();
    }
}
