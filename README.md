## powersave

My configuration for maximizing the battery life on my Thinkpad T530.

Included here is a systemd service file, various config-lets and a few
utilities to set or control certain power saving features. I set as much
as I can statically on boot; I think its silly to increase power
consumption simply because I'm on AC power.

Also look at my [backlight utilities][backlight]. The `lightd` daemon
is useful to automatically manage/dim the backlight.

A `PKGBUILD` is included as a convenience.

  [backlight]: https://github.com/vodik/lightd

### modprobe.d/powersave.conf

Enable `power_save=1` for `snd_hda_intel`

### sysctl.d/powersave.conf

- disable NMI watchdog
- set laptop mode
- increase the dirty writeback time

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

### rules.d/50-sata-powersave.rules

Enable sata powersaving features:

```
ACTION=="add", SUBSYSTEM=="scsi_host", ATTR{link_power_management_policy}="min_power"
```

### rules.d/50-usb-powersave.rules

Enable powersaving and autosuspend on usb ports:

```
ACTION=="add", SUBSYSTEM=="usb", TEST=="power/autosuspend" ATTR{power/autosuspend}="1"
ACTION=="add", SUBSYSTEM=="usb", TEST=="power/control" ATTR{power/control}="auto"
```
