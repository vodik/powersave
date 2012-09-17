CFLAGS := -std=c99 \
	-Wall -Wextra -pedantic \
	${CFLAGS}

all: bulkw
bulkw: bulkw.o

install: bulkw
	install -Dm755 envoy ${DESTDIR}/usr/bin/envoy
	install -Dm644 envoy@.service ${DESTDIR}/usr/lib/systemd/system/envoy@.service
	install -Dm644 envoy@.socket ${DESTDIR}/usr/lib/systemd/system/envoy@.socket

clean:
	${RM} bulkw *.o

.PHONY: clean install uninstall
