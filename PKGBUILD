# Maintainer: Simon Gomizelj <simongmzlj@gmail.com>

pkgname=vodik-powersave-git
pkgver=20121013
pkgrel=1
pkgdesc="Vodik's powersaving settings"
arch=('any')
url="http://github.com/vodik/powersave"
license=('GPL')
depends=('systemd' 'backlight-utils-git')
makedepends=('git')

_gitroot="$PWD"
_gitname="powersave"

build() {
  msg "Connecting to GIT server...."

  if [[ -d $_gitname ]] ; then
    cd "$_gitname" && git pull origin
    msg "The local files are updated."
  else
    git clone "$_gitroot" "$_gitname"
  fi

  msg "GIT checkout done or server timeout"
  msg "Starting make..."

  rm -rf "$srcdir/$_gitname-build"
  cp -r "$srcdir/$_gitname" "$srcdir/$_gitname-build"
  cd "$srcdir/$_gitname-build"
}

package() {
  cd "$srcdir/$_gitname-build"
  install -Dm644 sysctl.d/powersave.conf "$pkgdir/etc/sysctl.d/powersave.conf"
  install -Dm644 modprobe.d/powersave.conf "$pkgdir/etc/modprobe.d/powersave.conf"
  install -Dm644 tmpfiles.d/powersave.conf "$pkgdir/etc/tmpfiles.d/powersave.conf"
  install -Dm644 rules.d/50-backlight-powersave.rules "$pkgdir/etc/udev/rules.d/50-backlight-powersave.rules"
  install -Dm644 rules.d/50-network-powersave.rules "$pkgdir/etc/udev/rules.d/50-network-powersave.rules"
  install -Dm644 rules.d/50-pci-powersave.rules "$pkgdir/etc/udev/rules.d/50-pci-powersave.rules"
  install -Dm644 rules.d/50-usb-powersave.rules "$pkgdir/etc/udev/rules.d/50-usb-powersave.rules"
}

# vim: ft=sh syn=sh et
