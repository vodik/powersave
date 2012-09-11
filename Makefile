bulkw:
	make -C utils

install: bulkw
	install -Dm755 utils/bulkw ${DESTDIR}/usr/bin/bulkw
	install -Dm644 powersave.service ${DESTDIR}/usr/lib/systemd/system/powersave.service
	# install -Dm644 powersave ${DESTDIR}/usr/bin/powersave
	# install -Dm644 50-powersave.rules ${DESTDIR}/etc/udev/rules.d/50-powersave.rules
