## powersave

My configuration for maximizing the battery life on my Thinkpad T530.

Included here is a systemd service file, various config-lets and a few
utilities to set or control certain power saving features. I set as much
as I can statically on boot; I think its silly to increase power
consumption simply because I'm on AC power. This is integrated with my
[backlight utilities][backlight].

A `PKGBUILD` is included as a convenience.

### modprobe.d/powersave.conf

Enable `power_save=1` for `snd_hda_intel`

### sysctl.d/powersave.conf

- disable NMI watchdog
- set laptop mode
- increase the dirty writeback time

### tmpfiles.d/powersave.conf

Enable pci, usb, and sata powersaving features:

```
w /sys/bus/pci/devices/*/power/control - - - - auto
w /sys/bus/usb/devices/*/power/autosuspend - - - - 1
w /sys/bus/usb/devices/*/power/level - - - - auto
w /sys/class/scsi_host/host*/link_power_management_policy - - - - min_power
```

### rules.d/50-brightness-powersave.rules

Depending if we are on AC or battery power:

- sets the backlight to either 5% or max
- start or stop the [dimmer.service][backlight]

  [backlight]: https://github.com/vodik/backlight-utils


### rules.d/50-internet-powersave.rules

Set the powersaving features that must be enabled by 3rd-party commands:

```
ethtool -s eth0 wol d
iw dev wlan0 set power_save on
```
