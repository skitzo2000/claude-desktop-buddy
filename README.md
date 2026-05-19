# claude-desktop-buddy — CYD port

> **You're on the `cyd` branch.** This is a port of Anthropic's
> [`claude-desktop-buddy`](https://github.com/anthropics/claude-desktop-buddy)
> firmware to the **Cheap Yellow Display** (ESP32-2432S028R) — a ~$10
> ESP32 dev board with a 2.8" 240×320 resistive-touch TFT.
>
> The [`main`](https://github.com/skitzo2000/claude-desktop-buddy/tree/main)
> branch on this fork tracks Anthropic's upstream **byte-for-byte**. The
> CYD work lives only on `cyd` and is structured as a small overlay so
> pulling future upstream changes stays a clean merge.

The original M5StickCPlus device had buttons, an IMU, an RTC chip, and a
battery; CYD has a touchscreen and a USB cable. The HAL layer in
`src/hal/` makes the firmware run on the new board without disturbing the
upstream sources.

## Two ways to use it

| You want… | Pair with | How |
|---|---|---|
| **Claude for macOS/Windows** to drive the device | Anthropic's bundled Hardware Buddy GUI (closed-source, Mac/Win only) | Developer mode → Open Hardware Buddy → Connect |
| **Claude Code** (CLI / IDE-extension / web) to drive the device | The [`claude-hardware-buddy`](https://git.thenortonfamily.net/paul/claude-hardware-buddy) plugin — same wire protocol, Linux + macOS + Windows | `/plugin install claude-hardware-buddy` |

The firmware is the same in both cases. The plugin replaces the desktop
GUI for the Claude Code crowd; the BLE protocol (Nordic UART Service,
newline-delimited JSON) is unchanged.

## Hardware

- **Board**: ESP32-2432S028R ("CYD" — sold under several brand names on
  AliExpress, Amazon, etc. as "Cheap Yellow Display"). Common revisions
  in the wild: 2432S028 single-USB, 2432S028R red-board dual-USB. This
  firmware targets the **2432S028R**.
- **Display**: ILI9341 240×320 SPI, on VSPI.
- **Touch**: XPT2046 resistive controller, on HSPI (separate SPI bus —
  this is critical; sharing the bus with the display breaks both).
- **Power**: USB-only. There's no battery; the device is designed to sit
  on a desk plugged in.

What's not there compared to the M5Stick original: no IMU (so no shake
detection, no face-down nap), no battery readout, no hardware RTC. The
firmware fakes RTC via `millis()` + NVS, and the bridge re-syncs time on
every BLE connect.

## Flashing

Install
[PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/),
then from this directory:

```bash
pio run -e cyd -t upload
```

If you're starting from a previously-flashed device, wipe it first:

```bash
pio run -e cyd -t erase && pio run -e cyd -t upload
```

Calibrate the touchscreen the first time you run it: **long-press the
bottom-right corner** to enter the menu → **calibrate touch** → tap each
of the four corner targets. The calibration is stored in NVS.

## Pairing

### With Claude Desktop (macOS / Windows)

Enable developer mode (**Help → Troubleshooting → Enable Developer
Mode**), then **Developer → Open Hardware Buddy…** → **Connect** → pick
your device.

### With Claude Code (Linux / macOS / Windows)

Install the [`claude-hardware-buddy`](https://git.thenortonfamily.net/paul/claude-hardware-buddy)
plugin and follow its README. The plugin ships a single Go binary that
talks BLE directly — no Anthropic desktop app required.

## Controls

CYD has no buttons. Everything is touch zones:

```
┌───────────────────────────────┐
│ ZONE_SLEEP                  ◯ │  Tap top-right corner → screen off
│                               │  (replaces the M5 power-button toggle)
│                               │
│       BUDDY / GIF             │
│                               │
│                               │
├───────────────────────────────┤
│       HUD / TRANSCRIPT        │  Normal: tap to scroll
│                               │
├──────────────┬────────────────┤
│              │                │
│  ZONE_DENY   │  ZONE_APPROVE  │  Approval prompt: split halves
│   (B)        │     (A)        │  - tap A = approve, tap B = deny
│              │                │  - long-press A 600ms = menu
└──────────────┴────────────────┘
```

Outside of an approval, **A** advances screens and **B** scrolls; same
semantics as the M5 button mapping.

The screen auto-powers-off after 30s of no interaction (kept on while an
approval prompt is up). Any tap wakes it.

## ASCII pets and GIF pets

Both work the same as upstream. Eighteen ASCII species with seven
animations each (sleep, idle, busy, attention, celebrate, dizzy, heart),
or drag a character pack folder onto the bridge's drop target to stream
a custom GIF set over BLE. The GIF format and the seven mood states are
documented in
[upstream's README on `main`](https://github.com/skitzo2000/claude-desktop-buddy/blob/main/README.md#gif-pets)
— that section is unchanged.

One CYD-specific note: GIFs render to the wider 240px canvas instead of
M5's 135px, so character packs sized for M5 will appear left-aligned
with empty space on the right. Re-cropping with `tools/prep_character.py`
fixes this.

## Project layout

```
src/
  main.cpp           — loop, state machine, UI screens
  buddy.cpp          — ASCII species dispatch + render helpers
  buddies/           — 18 species files (byte-identical with upstream)
  ble_bridge.cpp     — Nordic UART service
  character.cpp      — GIF decode + render (byte-identical with upstream)
  data.h, xfer.h     — wire protocol + folder push
  stats.h            — NVS-backed stats, settings, owner, species choice
  hal/               — CYD HAL: board, input (touch), rtc, power, led,
                       audio, imu, touch_calibration
  cyd/               — reserved for the planned main.cpp split
  m5_shim.cpp        — defines the M5 facade instance
include/
  M5StickCPlus.h     — compile-time shim mapping the small M5 API surface
                       (Rtc, Axp) used by upstream files onto HAL calls
characters/          — example GIF character packs
tools/               — generators and converters (unchanged)
```

## Branching strategy on this fork

- **`main`** — tracks `anthropics/claude-desktop-buddy@main` byte-for-byte.
  Never edited directly. Used as the rebase target when pulling upstream
  changes.
- **`cyd`** — the default branch. CYD-port firmware as an overlay over
  `main`. ~5 upstream files modified, the rest of the port is additive
  (HAL layer + shim).
- Feature branches off `cyd`, PR back into `cyd`.

## Further reading

The deep design docs live in the companion plugin repo, next to the rest
of the bridge documentation:

- [PORT.md](https://git.thenortonfamily.net/paul/claude-hardware-buddy/src/branch/main/docs/cyd-port/PORT.md)
  — pin map, library swaps, file-by-file porting plan, geometry retune,
  touch-zone hit-test math, risk register.
- [MILESTONES.md](https://git.thenortonfamily.net/paul/claude-hardware-buddy/src/branch/main/docs/cyd-port/MILESTONES.md)
  — the execution plan that produced this branch (M1 through M5).

For the underlying BLE wire protocol (Nordic UART Service UUIDs, JSON
schemas, folder push transport), see Anthropic's
[REFERENCE.md](REFERENCE.md) — that document is unchanged on this fork.

## License and credit

Apache 2.0. The firmware, ASCII pets, animation state machine, BLE
protocol, GIF character format, and the original device design are all
Anthropic's. The CYD port (HAL layer, touch input, M5 API shim, geometry
retune) is in this fork.
