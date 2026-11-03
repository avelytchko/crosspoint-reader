#include "ReadableTheme.h"

#include <GfxRenderer.h>

#include <algorithm>

#include "components/UiAppHelpers.h"

void ReadableTheme::drawButtonMenu(GfxRenderer& renderer, Rect rect, const int buttonCount, const int selectedIndex,
                                   const std::function<std::string(int index)>& buttonLabel,
                                   const std::function<UIIcon(int index)>& rowIcon) const {
  namespace fui = freeink::ui;
  const auto& metrics = ReadableMetrics::values;
  auto target = makeUiTarget(renderer);
  const int rowHeight = getMenuRowHeight(renderer);
  const Rect safe = UITheme::getInstance().getScreenSafeArea(renderer, true, false);
  const int bottom = safe.y + safe.height;
  for (int i = 0; i < buttonCount; ++i) {
    const fui::Rect row{static_cast<int16_t>(rect.x + metrics.contentSidePadding),
                        static_cast<int16_t>(rect.y + i * (rowHeight + metrics.menuSpacing)),
                        static_cast<int16_t>(rect.width - 2 * metrics.contentSidePadding),
                        static_cast<int16_t>(rowHeight)};
    if (row.y + row.height > bottom) break;
    if (selectedIndex == i) renderer.fillRoundedRect(row.x, row.y, row.width, row.height, 6, Color::LightGray);

    auto text = row.inset(fui::Insets{0, 12, 0, 12});
    if (rowIcon) {
      const UIIcon type = rowIcon(i);
      fui::BitmapRef icon;
      switch (type) {
        case UIIcon::Settings:
          icon = fui::bitmapFromIcon(icon_settings_32);
          break;
        case UIIcon::Transfer:
          icon = fui::bitmapFromIcon(icon_upload_32);
          break;
        default:
          icon = listIconFor(type, 32);
          break;
      }
      if (icon) {
        target.bitmap(fui::Rect{text.x, static_cast<int16_t>(row.y + (row.height - 32) / 2), 32, 32}, icon,
                      fui::BitmapMode::Contain);
        text.x += 44;
        text.width = std::max<int16_t>(0, text.width - 44);
      }
    }
    fui::TextStyle style{fui::GfxRendererTarget::FONT_BODY};
    style.maxLines = 1;
    const auto label = buttonLabel(i);
    target.text(text, label.c_str(), style);
  }
}
