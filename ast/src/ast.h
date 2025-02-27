
#ifndef H_AST
#define H_AST

typedef struct ast_t ast_t;

struct ast_bytes_t {
   size_t nbytes;
   uint8_t *array;
};


typedef void (ast_walker_func_t) (ast_t *node, void *params, size_t depth);

#ifdef __cplusplus
extern "C" {
#endif

   ast_t *ast_new (ast_t *parent,
                   const char *srcfile_name,
                   size_t srcfile_line,
                   size_t srcfile_cpos);
   void ast_del (ast_t **ast);
   void ast_walk (ast_t *ast, ast_walker_func_t *fptr, void *params);

   void *ast_get_payload (ast_t *ast);
   void *ast_set_payload (ast_t *ast, void *payload);

   const char *ast_get_tag (ast_t *ast);
   const char *ast_set_tag (ast_t *ast, const char *tag);

   struct ast_bytes_t *ast_save (ast_t *src);
   ast_t ast_load (struct ast_bytes_t *src);

   // TODO: Possibly put this into a separate file. A parser.yy program can read
   // the input and write the binary that we can then load and process.
   /* ****************************************************************************
    * Reads the ast in the file specifed by fname. If fname is NULL then stdin is
    * read.
    *
    * The format is very simple:
    *    '...':                  A string literal, tagged as STRING_SQUOTE
    *    "...":                  A string literal, tagged as STRING_DQUOTE
    *    `...`:                  A string literal, tagged as STRING BQUOTE
    *    [0-9]                   DIGIT
    *    [1-9]                   PDIGIT
    *    [1-9][0-9]+:            An integer literal (64-bits) NUMBER_INT
    *    [1-9][0-9]+.[0-9]+      A double precision float literal NUMBER_FLOAT
    *    [_a-zA-z][!:ws:"'`:]+   A symbol
    *    (                       Start of a list
    *    )                       End of a list
    *    :{SYMBOL}[={SYMBOL}]    A key-value pair appended to the current node, when
    *                            current node is a list. An error outside of a list.
    */
   ast_t *ast_read (ast_t *parent, const char *fname, size_t line, size_t cpos);

#ifdef __cplusplus
};
#endif


#endif


