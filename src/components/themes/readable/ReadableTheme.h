#pragma once

#include "components/themes/lyra/LyraTheme.h"

namespace ReadableMetrics {
inline constexpr ThemeMetrics values = [] {
  auto metrics = LyraMetrics::values;
  metrics.verticalSpacing = 8;
  metrics.contentSidePadding = 12;
  metrics.listRowHeight = 48;
  metrics.listInset = 12;
  metrics.listSidePadding = 12;
  metrics.menuSpacing = 4;
  metrics.homeMenuTopOffset = 12;
  return metrics;
}();
}  // namespace ReadableMetrics

class ReadableTheme : public LyraTheme {
 public:
  void drawButtonMenu(GfxRenderer& renderer, Rect rect, int buttonCount, int selectedIndex,
                      const std::function<std::string(int index)>& buttonLabel,
                      const std::function<UIIcon(int index)>& rowIcon) const override;
};
