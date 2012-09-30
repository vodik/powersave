# Maintainer: Simon Gomizelj <simongmzlj@gmail.com>

pkgname=vodik-powersave-git
pkgver=20120930
pkgrel=1
pkgdesc="Vodik's powersaving settings"
arch=('i686' 'x86_64')
url="http://github.com/vodik/powersave"
license=('GPL')
depends=('systemd' 'dimmer-git')
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

  make
}

package() {
  make -C "$_gitname-build" DESTDIR="$pkgdir" install
}

# vim: ft=sh syn=sh et
