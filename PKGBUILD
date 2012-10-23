# Maintainer: Philip Stark <spam@codechaos.ch>
pkgname=backlightctl
pkgver=0.1
pkgrel=1
epoch=0
pkgdesc="Lightweight monitor backlight tool written in pure C."
arch=('i686' 'x86_64')
url="http://github.com/hellerbarde/backlightctl"
license=('MIT')
groups=()
depends=()
makedepends=('cmake' 'make')
checkdepends=()
optdepends=('sudo: for sensible use of the program by ordinary users')
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
changelog=
source=($pkgname-$pkgver.tar.gz)
noextract=()
md5sums=() #generate with 'makepkg -g'

build() {
    cd "$srcdir/$pkgname-$pkgver"
    mkdir Build && cd Build
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..
    make all
}

check() {
  cd "$srcdir/$pkgname-$pkgver"
}

package() {
  cd "$srcdir/$pkgname-$pkgver"
  make DESTDIR="$pkgdir/" install
}

