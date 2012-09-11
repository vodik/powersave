bulkw:
	make -C utils

install: bulkw
	install -Dm755 utils/bulkw ${DESTDIR}/usr/bin/bulkw
	install -Dm644 powersave.service ${DESTDIR}/usr/lib/systemd/system/powersave.service
