CFLAGS := -std=gnu99 \
	-Wall -Wextra -pedantic \
	${CFLAGS}

all: bulkw backlight
bulkw: bulkw.o
backlight: backlight.o

install: all
	install -Dm755 envoy ${DESTDIR}/usr/bin/envoy
	install -Dm644 envoy@.service ${DESTDIR}/usr/lib/systemd/system/envoy@.service
	install -Dm644 envoy@.socket ${DESTDIR}/usr/lib/systemd/system/envoy@.socket

clean:
	${RM} bulkw backlight *.o

.PHONY: clean install
