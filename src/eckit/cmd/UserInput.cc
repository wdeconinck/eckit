#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "eckit/cmd/UserInput.h"


namespace eckit {

struct termios save;
static int inited = 0;


enum {
    ESC = 0x1b,
    BACKSPACE = 0x7f,
    TAB = 9,
    CR = 13,
    CONTROL_D = 0x4,
    CONTROL_U = 0x15,
    // Virtual codes
    UP_ARROW = 1000,
    DOWN_ARROW = 1001,
    LEFT_ARROW = 1002,
    RIGHT_ARROW = 1003,
    HOME = 1004,
    END = 1005,
    DELETE = 1006,
    INSERT = 1007,
    PAGE_UP = 1008,
    PAGE_DOWN = 1009
};


static void exitRaw() {
    if (inited) {
        tcsetattr(0, TCSAFLUSH, &save);
    }
}

static void enterRaw() {

    if (!isatty(0)) {
        return;
    }

    if (tcgetattr(0, &save) < 0) {
        perror("tcgetattr");
    }

    struct termios raw = save;

    cfmakeraw(&raw);

    // Re-enable ^C and ^Z

    raw.c_lflag |= ISIG;

    raw.c_cc[VMIN] = 1; // On char at a time
    raw.c_cc[VTIME] = 0;

    if (!inited) {
        atexit(&exitRaw);
        inited = 1;
    }

    if (tcsetattr(0, TCSAFLUSH, &raw) < 0) {
        perror("tcsetattr");
    }
}

typedef struct entry {
    struct entry *next;
    struct entry *prev;
    char *line;
    int len;
} entry;

static entry *history = NULL;

typedef struct context {
    const char *prompt;
    entry *curr;
    int pos;
    int overwrite;
} context;

static int processCode(int c, context *s);

static void output(const context *s) {
    char *buffer = (char *)malloc(strlen(s->prompt) + strlen(s->curr->line) + 20);
    sprintf(buffer, "\r%s%s\033[0K\r\033[%dC", s->prompt, s->curr->line, strlen(s->prompt) + s->pos);
    write(1, buffer, strlen(buffer));
    free(buffer);
}

static void del(context *s) {
    if (s->pos > 0) {
        int i;
        char *line = s->curr->line;
        int len = strlen(line);
        for (i = s->pos - 1; i < len; i++) {
            line[i] = line[i + 1];
        }
        s->pos --;
        line[len] = 0;
    }
}

static void ins(context *s, char c) {
    char *line = s->curr->line;
    int len = strlen(line);

    if (len + 2 <= s->curr->len ) {
        char *old = s->curr->line;
        s->curr->len += 80;
        s->curr->line = (char *)calloc(s->curr->len, 1);
        strcpy(s->curr->line, old);
        free(old);
        line = s->curr->line;
    }

    if (!s->overwrite) {
        int i;
        int len = strlen(line);
        for (i = len; i >= s->pos; i--) {
            line[i + 1] = line[i];
        }
    }
    line[s->pos++] = c;
}

static char nextChar() {
    char c;
    if (read(0, &c, 1) != 1) {
        return 0;
    }
    return c;
}

static struct {
    const char *sequence;
    int code;
} escapes[] = {
    {"[A", UP_ARROW, },
    {"[B", DOWN_ARROW, },
    {"[C", RIGHT_ARROW, },
    {"[D", LEFT_ARROW, },
    {"OH", HOME, },
    {"OF", END, },
    {"[1~", HOME, },
    {"[2~", INSERT, },
    {"[3~", DELETE, },
    {"[4~", END, },
    {"[5~", PAGE_UP, },
    {"[6~", PAGE_DOWN, },
};

static void esc(context *s) {
    int len = sizeof(escapes) / sizeof(escapes[0]);
    char c;
    int i = 0;
    int j = 0;
    char buf[80];
    memset(buf, 0, sizeof(buf));
    while (1) {
        int partial = 0;
        buf[j++] = nextChar();
        for (i = 0; i < len; i++) {
            if (strncmp(escapes[i].sequence, buf, j) == 0) {
                partial++;
            }
            if (strcmp(escapes[i].sequence, buf) == 0) {
                processCode(escapes[i].code, s);
                return;
            }
        }

        if (partial == 0) {
            break;
        }
    }

    /* No match: output all charaters */
    for (i = 0; i < j; i++) {
        processCode(buf[i], s);
    }
}

static int processCode(int c, context *s) {
    switch (c) {

    case 0:
    case CONTROL_D:
        s->curr->line[0] = 0;
        return 1;

    case BACKSPACE:
        del(s);
        break;

    case DELETE:
        s->pos++;
        del(s);
        break;

    case TAB:
        break;

    case CONTROL_U:
        s->pos = 0;
        s->curr->line[0] = 0;
        break;

    case ESC:
        esc(s);
        break;

    case UP_ARROW:
        if (s->curr->prev) {
            s->curr = s->curr->prev;
            s->pos = strlen(s->curr->line);
        }
        break;

    case DOWN_ARROW:

        if (s->curr->next) {
            s->curr = s->curr->next;
            s->pos = strlen(s->curr->line);
        }
        break;

    case RIGHT_ARROW:
        s->pos++;
        if (s->pos > strlen(s->curr->line)) {
            s->pos = strlen(s->curr->line);
        }
        break;

    case LEFT_ARROW:
        s->pos--;
        if (s->pos < 0) {
            s->pos = 0;
        }
        break;


    case HOME:
        s->pos = 0;
        break;

    case END:
        s->pos = strlen(s->curr->line);
        break;

    case PAGE_UP:
        break;

    case PAGE_DOWN:
        break;

    case INSERT:
        s->overwrite = 1 - s->overwrite;
        break;

    case CR:
        write(1, "\r\n", 2);
        return 1;
        break;

    default:
        ins(s, c);
        break;

    }
    return 0;
}

void UserInput::printHistory(int max) {
    entry *last = NULL;
    entry *e;

     if (max == 0) {
        max = INT_MAX;
    }

    e = history;
    while (e && max-- > 0) {
        last = e;
        e = e->prev;
    }

    while (last) {
        printf("%s\n", last->line);
        last = last->next;
    }
}

void UserInput::saveHistory(const char *path, int max) {

    entry *last = NULL;
    entry *e;

    FILE *f = fopen(path, "w");

    if (!f) {
        perror(path);
        return;
    }

    if (max == 0) {
        max = INT_MAX;
    }

    e = history;
    while (e && max-- > 0) {
        last = e;
        e = e->prev;
    }

    while (last) {
        fprintf(f, "%s\n", last->line);
        last = last->next;
    }

    fclose(f);

}

void UserInput::loadHistory(const char *path) {

    char line[10240];
    FILE *f = fopen(path, "r");

    if (!f) {
        perror(path);
        return;
    }

    memset(line, 0, sizeof(line));
    while (fgets(line, sizeof(line) - 1, f)) {

        entry *h = (entry *)calloc(sizeof(entry), 1);

        int len = strlen(line);
        while (len) {
            if (line[len - 1] == '\n' || line[len - 1] == '\r') {
                line[len - 1] = 0;
                len--;
            } else {
                break;
            }
        }

        if (len) {

            h->len = len + 1 ;
            h->line = strdup(line);
            h->prev = history;

            if (history) {
                history->next = h;
            }

            history = h;
        }
    }

    fclose(f);

}

const char * UserInput::getUserInput(const char *prompt) {

    int done = 0;
    context s;
    entry *h = (entry *)calloc(sizeof(entry), 1);
    h->len = 80;
    h->line = (char *)calloc(h->len, 1);
    h->prev = history;

    if (history) {
        history->next = h;
    }

    history = h;

    memset(&s, 0 , sizeof(s));
    s.prompt = prompt;
    s.curr = h;

    enterRaw();

    output(&s);

    while (!done) {
        char c = nextChar();
        done = processCode(c, &s);
        if (!done) {
            output(&s);
        }
    }

    exitRaw();

    if(strlen(s.curr->line) == 0) {
        // Remove from history
        if(s.curr->prev) {
            s.curr->prev->next = s.curr->next;
        }
        if(s.curr->next) {
            s.curr->next->prev = s.curr->prev;
        }

        if(history == s.curr) {
            history = s.curr->next;
        }

        free(s.curr->line);
        free(s.curr);
        return "";
    }

    return s.curr->line;
}

} // namespace eckit