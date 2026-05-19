# claude-desktop-buddy — CYD port

Anthropic's [claude-desktop-buddy](https://github.com/anthropics/claude-desktop-buddy)
firmware, ported to the **Cheap Yellow Display** — a ~$10 ESP32 board with
a 2.8" touchscreen (ESP32-2432S028R).

You get the same buddy: a little pet on your desk that wakes up when Claude
is working, shows what's happening, and lets you tap **approve / deny** on
tool prompts.

## Get started

You'll need a CYD board (USB-C version, sold as "ESP32-2432S028R" on
AliExpress / Amazon) and [PlatformIO](https://platformio.org/install/cli).

```bash
pio run -e cyd -t upload
```

That's it for the firmware. First boot will ask you to calibrate the
touchscreen — tap each of the four corner targets.

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

## License

MIT. Firmware, pets, protocol, and original device design are
Anthropic's. CYD port (HAL, touch input, M5 shim) is in this fork.
