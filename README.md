## powersave

A systemd service file and utilizes to set certain powersaving features
on boot (screw consuming more power just because I'm on AC).

Basically:

```
bulkw auto      /sys/bus/pci/devices/*/power/control
bulkw 1         /sys/bus/usb/devices/*/power/autosuspend
bulkw auto      /sys/bus/usb/devices/*/power/level
bulkw min_power /sys/class/scsi_host/host0/link_power_management_policy

ethtool -s eth0 wol d
iw dev wlan0 set power_save off
```

### bulkw

```
usage: bulkw [data] [files ...]
```

`bulkw` is a bulk writing utility. It writes arbitrary data to every
file matched via glob.
