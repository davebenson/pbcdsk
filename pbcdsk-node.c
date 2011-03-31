#include "../dsk/dsk.h"

typedef struct _Worker Worker;
typedef struct _Context Context;
typedef struct _WorkerTransfer WorkerTransfer;

struct _WorkerTransfer
{
  Worker *source;               /* or NULL if transfering from manager */
  Worker *dest;
  Chunk *chunk;

};

typedef struct _Chunk Chunk;
struct _Chunk
{
  uint8_t sha1[20];
  unsigned n_copies;
  Worker **copies;
  unsigned desired_copies;
  char **kv_pairs;              /* metadata */
  uint64_t file_size;
  unsigned upload_time;

  dsk_boolean on_manager;

  /* tree */
  Chunk *left, *right, *parent;
  dsk_boolean is_red;
};

struct _Worker
{
  char *id;
  dsk_boolean connected;
  unsigned last_seen_time;

  uint64_t total_file_size;

  dsk_boolean is_red;
  Worker *left, *right, *parent;
};

struct _Context
{
  ...
};

static void
register_cgi (

int main(int argc,
         char **argv)
{
  DskHttpServer *server;
  unsigned bind_port = 0;
  static Context context;

  dsk_cmdline_init ("PBCDSK blob manager", 
                    "Redundant data blob manager",
                    NULL,
                    0);
  dsk_cmdline_add_uint ("port", "Listen on given port with HTTP+ server",
                        "PORT", DSK_CMDLINE_MANDATORY, &bind_port);
  dsk_cmdline_process_args (&argc, &argv);

  /* create http server */
  server = dsk_http_server_new ();

  dsk_http_server_match_save (server);
   dsk_http_server_add_match (server, DSK_HTTP_SERVER_MATCH_PATH, "/");
   dsk_http_server_register_cgi_handler (server, handle_main_page, &context, NULL);
  dsk_http_server_match_restore (server);

  dsk_http_server_match_save (server);
   dsk_http_server_add_match (server, DSK_HTTP_SERVER_MATCH_PATH, "/worker\\?.*");
   dsk_http_server_register_connect_handler (server, "PBCDSK-Worker", try_worker_connect, implement_pbcdsk_worker_page, &context, NULL);
  dsk_http_server_match_restore (server);

  dsk_http_server_match_save (server);
   dsk_http_server_add_match (server, DSK_HTTP_SERVER_MATCH_PATH, "/download-chunk/.*");
   dsk_http_server_register_cgi_handler (server, handle_download_chunk, NULL, NULL);
  dsk_http_server_match_restore (server);

void dsk_http_server_add_match                 (DskHttpServer        *server,
                                                DskHttpServerMatchType type,
                                                const char           *pattern);
  ...

  return dsk_main_run ();
}

