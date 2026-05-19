# claude-desktop-buddy — CYD port

Anthropic's [claude-desktop-buddy](https://github.com/anthropics/claude-desktop-buddy)
firmware, ported to the **Cheap Yellow Display** — a ~$10 ESP32 board with
a 2.8" touchscreen (ESP32-2432S028R).

You get the same buddy: a little pet on your desk that wakes up when Claude
is working, shows what's happening, and lets you tap **approve / deny** on
tool prompts.

## Get started

You'll need a CYD board (USB-C version, sold as "ESP32-2432S028R" on
AliExpress / Amazon).

1. Plug it in.
2. Open **[the web flasher](https://skitzo2000.github.io/claude-desktop-buddy/)**
   in Chrome or Edge and click **Install**.
3. On first boot, tap each of the four corners to calibrate the
   touchscreen.

Done. No downloads, no command line.

## Pair it with Claude

Pick one:

- **Claude Desktop** (macOS / Windows) — enable developer mode
  (Help → Troubleshooting), then **Developer → Open Hardware Buddy →
  Connect**.
- **Claude Code** (Linux / macOS / Windows) — install the
  [`claude-hardware-buddy`](https://git.thenortonfamily.net/paul/claude-hardware-buddy)
  plugin.

## More details

- [docs/](docs/) — manual, screenshots, original device photos.
- [PORT.md](https://git.thenortonfamily.net/paul/claude-hardware-buddy/src/branch/main/docs/cyd-port/PORT.md)
  — how the port works (pin map, HAL, touch zones, optional add-ons).
- [REFERENCE.md](REFERENCE.md) — BLE wire protocol, GIF character format.
- [upstream README](https://github.com/anthropics/claude-desktop-buddy)
  — Anthropic's original docs, including the full ASCII pet roster.

## Building from source

The web flasher above is the right path for end users. If you want to
modify the firmware:

```bash
pio run -e cyd -t upload
```

Needs [PlatformIO](https://platformio.org/install/cli). The same
command CI runs is in `.github/workflows/release.yml` — every push
produces a downloadable artifact, and every `v*` tag cuts a release
with a merged `.bin` attached.

## License

MIT. Firmware, pets, protocol, and original device design are
Anthropic's. CYD port (HAL, touch input, M5 shim) is in this fork.
