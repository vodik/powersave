bulkw:
	make -C utils

install: bulkw
	install -Dm755 utils/bulkw ${DESTDIR}/usr/bin/bulkw
	install -Dm644 powersave.service ${DESTDIR}/usr/lib/systemd/system/powersave.service
	install -Dm644 sysctl.d/powersave.conf ${DESTDIR}/etc/sysctl.d/powersave.conf
	install -Dm644 modprobe.d/powersave.conf ${DESTDIR}/etc/modprobe.d/powersave.conf
