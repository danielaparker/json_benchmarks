#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#if !defined(_WIN32) && !defined(NDEBUG)
#include <execinfo.h>
#include <signal.h>
#endif
#include "gason.h"

const int SHIFT_WIDTH = 4;

void dumpString(FILE *fp, const char *s) {
    fputc('"', fp);
    while (*s) {
        int c = *s++;
        switch (c) {
        case '\b':
            fprintf(fp, "\\b");
            break;
        case '\f':
            fprintf(fp, "\\f");
            break;
        case '\n':
            fprintf(fp, "\\n");
            break;
        case '\r':
            fprintf(fp, "\\r");
            break;
        case '\t':
            fprintf(fp, "\\t");
            break;
        case '\\':
            fprintf(fp, "\\\\");
            break;
        case '"':
            fprintf(fp, "\\\"");
            break;
        default:
            fputc(c, fp);
        }
    }
    fprintf(fp, "%s\"", s);
}

void dumpValue(FILE *fp, JsonValue o, int indent = 0) {
    switch (o.getTag()) {
    case JSON_NUMBER:
        fprintf(fp, "%f", o.toNumber());
        break;
    case JSON_STRING:
        dumpString(fp,o.toString());
        break;
    case JSON_ARRAY:
        // It is not necessary to use o.toNode() to check if an array or object
        // is empty before iterating over its members, we do it here to allow
        // nicer pretty printing.
        if (!o.toNode()) {
            fprintf(fp, "[]");
            break;
        }
        fprintf(fp, "[\n");
        for (auto i : o) {
            fprintf(fp, "%*s", indent + SHIFT_WIDTH, "");
            dumpValue(fp,i->value, indent + SHIFT_WIDTH);
            fprintf(fp, i->next ? ",\n" : "\n");
        }
        fprintf(fp, "%*s]", indent, "");
        break;
    case JSON_OBJECT:
        if (!o.toNode()) {
            fprintf(fp, "{}");
            break;
        }
        fprintf(fp, "{\n");
        for (auto i : o) {
            fprintf(fp, "%*s", indent + SHIFT_WIDTH, "");
            dumpString(fp,i->key);
            fprintf(fp, ": ");
            dumpValue(fp,i->value, indent + SHIFT_WIDTH);
            fprintf(fp, i->next ? ",\n" : "\n");
        }
        fprintf(fp, "%*s}", indent, "");
        break;
    case JSON_TRUE:
        fprintf(fp, "true");
        break;
    case JSON_FALSE:
        fprintf(fp, "false");
        break;
    case JSON_NULL:
        fprintf(fp, "null");
        break;
    }
}
