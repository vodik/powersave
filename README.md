## powersave

My configuration for maximizing the battery life on my Thinkpad T530.

Included here is a systemd service file, various config-lets and a few
utilities to set or control certain power saving features. I set as much
as I can statically on boot; I think its silly to increase power
consumption simply because I'm on AC power.

A `PKGBUILD` is included as a convenience.

### powersave.service

Basically the following script:

```
bulkw auto      /sys/bus/pci/devices/*/power/control
bulkw 1         /sys/bus/usb/devices/*/power/autosuspend
bulkw auto      /sys/bus/usb/devices/*/power/level
bulkw min_power /sys/class/scsi_host/host0/link_power_management_policy

ethtool -s eth0 wol d
iw dev wlan0 set power_save on
```

### modprobe.d/powersave.conf

Enable `power_save=1` for `snd_hda_intel`

### sysctl.d/powersave.conf

- disable NMI watchdog
- set laptop mode
- increase the dirty writeback time

### rules.d/50-powersave.rules

Depending if we are on AC or battery power:

- sets the backlight to either `4` or `max`
- start or stop the [dimmer.service][dimmer]

### backlight

```
usage: backlight [value]
```

`backlight` is a simple utility to control the backlight. It is suid so
any normal user can control the brightness.

### bulkw

```
usage: bulkw [data] [files ...]
```

`bulkw` is a bulk writing utility. It writes arbitrary data to every
file matched via glob.

  [dimmer]: https://github.com/vodik/dimmer
