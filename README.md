# My build of dwm - a dynamic window manager for X

This is my custom build of [dwm](https://dwm.suckless.org/), a dynamic window manager originally from the official [suckless](https://suckless.org/) website, customized to suit my personal needs and still provide a much smaller, faster and simpler tiling window manager with all necessary functionality.

## Applied Patches

I have applied the following patches to enhance functionality and appearance:

- [`adjacenttag-skipvacant`](https://dwm.suckless.org/patches/adjacenttag/)
- [`bar-height-spacing`](https://dwm.suckless.org/patches/bar_height/)
- [`borderrule`](https://dwm.suckless.org/patches/borderrule/)
- [`dwmblocks`](https://github.com/ashish-yadav11/dwmblocks)
- [`fixborders`](https://dwm.suckless.org/patches/alpha/)
- [`fsignal`](https://dwm.suckless.org/patches/fsignal/)
- [`hide_vacant_tags`](https://dwm.suckless.org/patches/hide_vacant_tags/)
- [`noborderfloatingfix`](https://dwm.suckless.org/patches/noborder/)
- [`swallow`](https://dwm.suckless.org/patches/swallow/)
- [`vanitygaps`](https://dwm.suckless.org/patches/vanitygaps/)
- [`xrdb`](https://dwm.suckless.org/patches/xrdb/)

## Patch Functionality

This build of **dwm** includes several patches to enhance usability, visual appearance, and dynamic behavior. Features like **vanitygaps**, **bar-height-spacing**, and **borderrule** allow for a cleaner and more customizable layout. Functional improvements include **swallow** for seamless terminal-based app launches, **fsignal** and **dwmblocks** for dynamic status bar updates, and **xrdb** for loading settings from `.Xresources` or [pywal](https://github.com/eylles/pywal16) without recompilation. Additional usability tweaks like skipping vacant tags, hiding unused tags, and fixing border behavior round out a smooth and efficient window management experience.

## Additional Customizations

- Installed **CaskaydiaCove Nerd Font** at 14px size
- Applied the [Catppuccin Mocha](https://github.com/catppuccin/catppuccin) colorscheme, following their official [style guide](https://github.com/catppuccin/catppuccin/blob/main/docs/style-guide.md)
- Use `xcompmgr` on lightweight systems and `picom` on more capable ones
- Applied the `fixborders` patch to ensure window borders remain opaque under transparency
- Enabled thin 1px borders, and disabled borders entirely for certain window types
- Configured a 10px gap between windows and screen edges, with smart gaps (no gap when only one window is present)

## Key Bindings

- A second `MODKEY` was added using `Mod4Mask` (Super key)
- Use `Super + Tab` to cycle through all non-empty tags in order
- When the last tag is reached, it automatically wraps back to the first one, allowing seamless navigation
- Navigate between tags with `Super + Right` (next) and `Super + Left` (previous)
- `Alt + Space` opens **dmenu_run**, allowing you to quickly launch any executable from your `$PATH` using a simple fuzzy search
- `Alt + Q` opens a **dmenu** power menu with options: **Cancel**, **Lock**, **Quit**, **Reboot** or **Poweroff**
- `Super + Q` kills the focused client, while `Alt + Shift + Q` quits **dwm** and all open clients - equivalent to selecting **Quit** from the power menu
- Clipboard shortcuts like `Alt + C` and `Alt + V` open **cliphist** via **dmenu** to manage clipboard history
- The clipboard script is available here: [cliphist](https://github.com/sebastianzehner/cliphist)
- Multimedia keys (from your keyboard) control audio directly:
  - Volume Up: `XF86AudioRaiseVolume`
  - Volume Down: `XF86AudioLowerVolume`
  - Mute Toggle: `XF86AudioMute`
- These trigger a `pipewire`-based volume script with visual notifications and update the status bar

## Installation

```bash
git clone https://github.com/sebastianzehner/dwm
cd dwm
doas make install
```

## Disclaimer

I'm not a professional developer - just a hobbyist sharing my personal setup.  
This build is provided as-is, with no guarantees that it will work for you.  
If something breaks, you're on your own - but feel free to explore, adapt, and improve!
