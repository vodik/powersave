all:
	make -C utils

install: utils
	make -C utils install
	install -Dm644 powersave.service ${DESTDIR}/usr/lib/systemd/system/powersave.service
	install -Dm644 sysctl.d/powersave.conf ${DESTDIR}/etc/sysctl.d/powersave.conf
	install -Dm644 modprobe.d/powersave.conf ${DESTDIR}/etc/modprobe.d/powersave.conf
	install -Dm644 rules.d/50-powersave.rules ${DESTDIR}/etc/udev/rules.d/50-powersave.rules

clean:
	make -C utils clean

.PHONY: clean install
