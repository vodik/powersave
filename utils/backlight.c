#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <limits.h>
#include <glob.h>

#define CLAMP(x, low, high) \
    __extension__ ({ \
        typeof(x) _x = (x); \
        typeof(low) _low = (low); \
        typeof(high) _high = (high); \
        ((_x > _high) ? _high : ((_x < _low) ? _low : _x)); \
    })

typedef char filepath_t[PATH_MAX];

struct backlight_t {
    long max;
    filepath_t dev;
};

static int get(filepath_t path, long *value)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        warn("failed to open %s", path);
        return -1;
    }

    char buf[1024], *end = NULL;
    if (read(fd, buf, 1024) < 0)
        err(EXIT_FAILURE, "failed to read %s", path);

    *value = strtol(buf, &end, 10);
    if (errno || buf == end) {
        warn("not a number: %s", buf);
        return -1;
    }

    close(fd);
    return 0;
}

static int set(filepath_t path, long value)
{
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        warn("failed to open %s", path);
        return -1;
    }

    char buf[1024];
    int len = snprintf(buf, 1024, "%ld", value);
    if (write(fd, buf, len) < 0)
        err(EXIT_FAILURE, "failed to set backlight");

    close(fd);
    return 0;
}

static int get_backlight_info(struct backlight_t *b, int id)
{
    filepath_t path;

    snprintf(path, PATH_MAX, "/sys/class/backlight/acpi_video%d/max_brightness", id);
    if (get(path, &b->max) < 0)
        return -1;

    snprintf(b->dev, PATH_MAX, "/sys/class/backlight/acpi_video%d/brightness", id);
    return 0;
}

static void __attribute__((__noreturn__)) usage(FILE *out)
{
    fprintf(out, "usage: %s [value]\n", program_invocation_short_name);

    exit(out == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    struct backlight_t b;
    char *arg = argv[1];
    long value = 0;

    if (argc != 2)
        usage(stderr);

    if (get_backlight_info(&b, 0) < 0)
        errx(EXIT_FAILURE, "couldn't get backlight information");

    if (strcmp("max", arg) == 0)
        value = b.max;
    else {
        char *end = NULL;
        value = strtol(arg, &end, 10);
        if (errno || arg == end)
            errx(EXIT_FAILURE, "invalid setting: %s", arg);
    }

    return set(b.dev, CLAMP(value, 0, b.max));
}

// vim: et:sts=4:sw=4:cino=(0
