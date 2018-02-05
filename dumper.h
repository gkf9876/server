#ifndef __DUMPER_H__
#define __DUMPER_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <tmx.h>
#include <tsx.h>

#define str_bool(b) (b==0? "false": "true")

void print_orient(enum tmx_map_orient orient);
void print_stagger_index(enum tmx_stagger_index index);
void print_stagger_axis(enum tmx_stagger_axis axis);
void print_renderorder(enum tmx_map_renderorder ro);
void print_draworder(enum tmx_objgr_draworder dro);
void print_halign(enum tmx_horizontal_align halign);
void print_valign(enum tmx_vertical_align valign);

void mk_padding(char pad[11], int depth);

void print_prop(tmx_property *p, void *depth);

void dump_prop(tmx_properties *p, int depth);

void print_obj_type(enum tmx_obj_type type);

void dump_points(double **p, int pl);

void dump_objects(tmx_object *o, int depth);

void dump_image(tmx_image *i, int depth);

void dump_tile(tmx_tile *t, unsigned int tilecount);

void dump_tileset(tmx_tileset_list *tsl);

int dump_layer(tmx_layer *l, unsigned int tc, int depth);

int dump_map(tmx_map *m, int depth, int x, int y);

static int mal_vs_free_count = 0;

void* dbg_alloc(void *address, size_t len);

void dbg_free(void *address);

/* for tmx_load_callback */
int read_function(void *file, char *buffer, int len);

int isOption(const char *arg);

int isMap(const char *arg);

void printUsage(const char *arg0);

#endif