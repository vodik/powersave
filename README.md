## powersave

A systemd service file and utilizes to set certain powersaving features
on boot (screw consuming more power just because I'm on AC).

### powersave.service

Basically the following script:

```
bulkw auto      /sys/bus/pci/devices/*/power/control
bulkw 1         /sys/bus/usb/devices/*/power/autosuspend
bulkw auto      /sys/bus/usb/devices/*/power/level
bulkw min_power /sys/class/scsi_host/host0/link_power_management_policy

ethtool -s eth0 wol d
iw dev wlan0 set power_save off
```

### modprobe.d/powersave.conf

Enable `power_save=1` for `snd_hda_intel`

### sysctl.d/powersave.conf

- disable NMI watchdog
- set laptop mode
- increase the dirty writeback time

### rules.d/50-powersave.rules

Start or stop [dimmer.service][dimmer] depending if we're running on
battery power or not.

### bulkw

```
usage: bulkw [data] [files ...]
```

`bulkw` is a bulk writing utility. It writes arbitrary data to every
file matched via glob.

  [dimmer]: https://github.com/vodik/dimmer
