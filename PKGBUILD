# Maintainer: Simon Gomizelj <simongmzlj@gmail.com>

pkgname=vodik-powersave-git
pkgver=1
pkgver() {
  cd "powersave"
  git describe | sed 's/^v//;s/-/./g'
}
pkgrel=1
pkgdesc="Vodik's powersaving settings"

arch=('any')
url="http://github.com/vodik/powersave"
license=('GPL')
depends=('systemd')
makedepends=('git')
source=("git+file://$PWD")
sha1sums=('SKIP')

package() {
  cd "powersave"
  install -Dm644 sysctl.d/powersave.conf "$pkgdir/usr/lib/sysctl.d/powersave.conf"
  install -Dm644 modprobe.d/powersave.conf "$pkgdir/usr/lib/modprobe.d/powersave.conf"
  install -Dm644 rules.d/50-network-powersave.rules "$pkgdir/usr/lib/udev/rules.d/50-network-powersave.rules"
  install -Dm644 rules.d/50-sata-powersave.rules "$pkgdir/usr/lib/udev/rules.d/50-sata-powersave.rules"
  install -Dm644 rules.d/50-pci-powersave.rules "$pkgdir/usr/lib/udev/rules.d/50-pci-powersave.rules"
  install -Dm644 rules.d/50-usb-powersave.rules "$pkgdir/usr/lib/udev/rules.d/50-usb-powersave.rules"
}

# vim: ft=sh syn=sh et
