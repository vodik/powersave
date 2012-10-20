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

Enable sata powersaving features. Ideally should be a udev rules but
I don't know if its exposed.

```
w /sys/class/scsi_host/host?/link_power_management_policy - - - - min_power
```

### rules.d/50-backlight-powersave.rules

Rules for the backlight. Depending if we are on AC or battery power:

- sets the backlight to either 5% or max
- start or stop the [dimmer.service][backlight]

  [backlight]: https://github.com/vodik/backlight-utils


### rules.d/50-network-powersave.rules

Set the powersaving features on network devices that must be enabled by
3rd-party commands. For every detected device:

```
ACTION=="add", SUBSYSTEM=="net", KERNEL=="eth*" RUN+="/usr/sbin/ethtool -s %k wol d"
ACTION=="add", SUBSYSTEM=="net", KERNEL=="wlan*" RUN+="/usr/sbin/iw dev %k set power_save on"
```

**NOTE**: this assumes modern Linux wireless drivers. There's no guarantee
about naming of devices.

### rules.d/50-pci-powersave.rules

Enable pci powersaving features:

```
ACTION=="add", SUBSYSTEM=="pci", ATTR{power/control}="auto"
```

### rules.d/50-usb-powersave.rules

Enable powersaving and autosuspend on usb ports:

```
ACTION=="add", SUBSYSTEM=="usb", ATTR{power/autosuspend}="1"
ACTION=="add", SUBSYSTEM=="usb", ATTR{power/level}="auto"
```
