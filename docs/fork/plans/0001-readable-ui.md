# Readable UI theme

## Requirement

Provide a selectable theme for the owner's Xteink X3 with larger Home and
Settings text, compact spacing, wrapped setting labels, and no text beyond the
visible screen. Keep upstream synchronization manageable. Plugins do not expose
a system-theme API, so reuse the existing firmware theme and shared list hosts.

## Scope and comparison

- Working branch: `feat/ui-font-size`, created from the former `main`.
- Comparison base: `5387117e5f476f081d5275c55dea42ae7df7f537`.
- `main` is absent locally; its last recorded checkout pointed to this base.
  No existing branch is moved, and no commits or publication are authorized.
- The earlier font-size experiment is no longer available, as confirmed by the owner.
- SDK: `946e6ac3d7a9d590ba3224428e6183d55ac7917c`, matching this branch's pin.
  Do not modify the SDK or submodule revision.
- This is a downstream theme requested by the owner. Upstream currently freezes
  new themes in `SCOPE.md`; this is not an upstream submission.

## Design

- Add Readable without renumbering any existing saved theme IDs.
- Reuse Lyra's cover, chrome, input ownership, and shared list navigation.
- Ubuntu 16 pt for Home, primary lists and headings; Ubuntu 14 pt for secondary
  text, nested settings labels and values. Preserve the same script coverage as
  the existing Ubuntu UI fonts and size-matched SD fallback.
- Reduce list insets, Home row gaps, and spacing below headers. Main Settings
  rows reserve one actual text line instead of an unused subtitle line.
- Home labels are width-bounded. Settings retain measured wrapping up to two
  lines, with the existing SDK sizing and viewport feedback.
- Rebind existing screen font slots when the theme changes, before rebuilding
  shared metrics. No new activities, tasks, network work or persisted fields.

## Using the theme

Choose **Settings > Display > UI Theme > Readable**. Home and primary lists
use larger text; nested settings use larger labels and values with compact
spacing. Choose any other theme in the same menu to restore its appearance.
The choice is saved across restarts. With non-Latin SD font fallback, include
14 and 16 pt files in the selected `.cpfont` family in addition to the existing
8/10/12 pt UI sizes. Direct vector fonts remain limited to supported boards.

## Resources and maintenance

New static font data consumes flash; record the built X3 delta. Two additional
font-family registrations use the existing renderer map for the application
lifetime. The active theme replaces the previous theme through checked ownership;
no new framebuffer or per-screen retained container is added. Home still uses
the existing bounded menu-label callback and shared text truncation. SD fallback
uses the existing font owner and teardown at two additional sizes; runtime costs
with non-Latin SD fonts require device checks.

`src/fontIds.h` keeps upstream's existing IDs and adds only `UI_14_FONT_ID` and
`UI_16_FONT_ID`. Running `build-font-ids.sh` would recompute every ID, because
upstream's committed IDs do not match their current font files; that would
rebuild every book's layout cache and conflict with each upstream change to the
file. Existing book caches stay valid.

## Affected devices and acceptance

The owner currently has only an X3, so build and test `default` only. The code
is shared UI and also compiles for X4 Pro and Picco; check those boards before
using this change on them. The X3 emulator is a quick visual check; no
emulation result is physical-device validation.

On X3: compare Home, main Settings, every settings section, long labels and
values, theme picker, English and Ukrainian. Select the last item of a scrolling
list and verify it remains fully visible. Check switching to/from Readable and
restart persistence. Exercise a fifth Home item when Plugins/OPDS is enabled.
Check all four orientations, button/remap navigation, opening and closing a
book (it must open without a layout rebuild), and repeated Settings entry
without heap loss. Device acceptance and hardware measurements are pending.

## Files

- New `src/components/themes/readable/ReadableTheme.*`.
- Theme selection: `CrossPointSettings.h`, `SettingsList.h`, `UITheme.cpp`.
- Fonts: built-in font sources/generation, `main.cpp`, `UIScale.h`,
  `SdCardFontSystem.cpp`, and host font rebinding in `UiAppHost.cpp`.
- Settings layout/selection: `SettingsListActivity.cpp`, `SettingsActivity.cpp`.
- English/Ukrainian theme label and this fork registry/plan.

## Status

Follow-up: upstream font IDs restored and the plan limited to X3. The X3
build passed again (static RAM 66,728 B, flash 5,930,585 B, no warnings).

Implementation, four independent reviews, targeted follow-up, formatting, shared
UI host checks and all three final builds are complete. X3 emulator checks cover
Home, main Settings, English/Ukrainian Display, long-list scrolling, restart
persistence, book open/exit and old-cache reopening. Explicit human acceptance
of the behavior, design and maintenance cost remains pending. No commit, push,
PR, or physical-device flash has been performed.

Initial reviews completed on pinned v1. Accepted fixes add the missing Home
icons and hold the existing render lock during live theme replacement/font
rebinding. Targeted v2 reviews confirm those fixes. The conditional
landscape-Home concern is not established as reachable: reader exit resets the
renderer to Portrait. No firmware path was added to rotate Home.

## Recorded checks

- Baseline X3 build passed: `/private/tmp/crosspoint-readable-baseline-build.log`.
  Static RAM 66,680 B; application flash 5,549,543 B / 6,553,600 B.
- Baseline binaries: `/private/tmp/crosspoint-readable-baseline/`.
- Browser: the owner's Chrome, official eink-qemu web app, X3 528 x 792.
  The supplied release starts and renders Home/Settings. For layout inspection,
  disable Turbo and Ghosting; accelerated guest time otherwise reaches idle
  sleep quickly while inspecting source.
- Prototype X3 build passed: `/private/tmp/crosspoint-readable-prototype-build.log`.
  Static RAM 66,728 B; application flash 5,930,185 B; headroom 623,415 B.
  Delta: +48 B static RAM and +380,642 B flash. Runtime heap is a separate check.
- Shared SDK UI host suite: 321,200 checks, zero failures, recorded in
  `/private/tmp/crosspoint-readable-ui-host.log`.
- Generated font IDs reproduce exactly; formatter wrapper and whitespace checks pass.
- Browser prototype: selected Readable, inspected Home, main Settings and Display,
  and returned between them. English Display fits all ten rows. An emulator
  Wi-Fi exit triggered the firmware's existing silent restart; persistence is
  under inspection. No real device or network credentials were used.
- Final builds: `default`, `x4pro`, `picco` all passed. Full log is
  `build/readable-ui/build.log`; generated binaries and screenshots are beside it.
  Final X3 static RAM is 66,728 B, flash 5,930,585 B, slot headroom 623,015 B.
  Final delta against baseline: +48 B static RAM, +381,042 B flash.
- X4 Pro: 111,796 B static RAM and 5,773,522 B flash. Picco: 112,860 B static RAM
  and 5,776,442 B flash. These are absolute build sizes, not runtime heap values.
- Final X3 emulator reopened `font-prewarm-benchmark.epub` after creating its
  section cache with the baseline binary. It logged the expected parameter
  mismatch, rebuilt the cache, and preserved `spine=0 offset=24 page=1` (second
  page). The test log and screenshot are in `build/readable-ui/`. This check
  predates restoring upstream's font IDs; with them, the cache is kept.
- Final Home shows all four icons with matching label alignment. Ukrainian
  Display wraps long labels and fits all ten rows. Other device input/touch,
  orientations and SD/vector fallback heap checks remain human hardware checks.
- Final live switching Readable > Lyra > Readable passed in the X3 emulator;
  label size and density changed immediately in both directions. The final
  browser tab is left on Ukrainian Display with Readable selected.
