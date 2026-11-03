# Fork changes

| Change | Branch / base | Upstream files | Upstream candidate | Status |
| --- | --- | --- | --- | --- |
| Readable UI theme | `feat/ui-font-size`, base `5387117e` | Font generation/registration and IDs, theme selection, `UIScale.h`, `UiAppHost.cpp`, `SdCardFontSystem.cpp`, Settings layout, English/Ukrainian labels | No: downstream theme; upstream theme additions are frozen | Builds/reviews/X3 emulator checks complete; owner acceptance and hardware checks pending; see [plan](plans/0001-readable-ui.md) |

Keep saved theme values 0-4 unchanged when resolving upstream conflicts.
Readable is value 5. Persistence uses the full value table; the display-only
picker hides Cover Grid on boards without PSRAM and maps the remaining indexes
back to their saved IDs. Reapply the font rebinding before shared UI metrics are
published when merging changes to `UiAppHost::resetUi()`.

`src/fontIds.h`: keep upstream's existing IDs and add only `UI_14_FONT_ID` and
`UI_16_FONT_ID`. Running `build-font-ids.sh` recomputes every ID, because
upstream's committed IDs do not match their current font files.
