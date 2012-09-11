#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <glob.h>

static void write_to(const char *msg, const char *path)
{
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        warn("failed to open %s", path);
        return;
    }

    size_t len = strlen(msg);
    if (write(fd, msg, len) < 0)
        err(EXIT_FAILURE, "failed to write contents to %s", path);

    close(fd);
}

int main(int argc, char *argv[])
{
    glob_t gl;
    const char *msg = argv[1];
    size_t i;

    if (argc < 3)
        errx(EXIT_FAILURE, "not enough arguments");

    if (glob(argv[2], 0, NULL, &gl) != 0)
        errx(EXIT_FAILURE, "failed to glob %s\n", argv[2]);

    for (i = 3; i < (size_t)argc; ++i) {
        if (glob(argv[i], GLOB_APPEND, NULL, &gl) != 0)
            errx(EXIT_FAILURE, "failed to glob %s\n", argv[i]);
    }

    for (i = 0; i < gl.gl_pathc; ++i)
        write_to(msg, gl.gl_pathv[i]);

    globfree(&gl);
    return 0;
}

// vim: et:sts=4:sw=4:cino=(0
