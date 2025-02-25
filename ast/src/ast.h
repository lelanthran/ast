
#ifndef H_AST
#define H_AST

typedef struct ast_t ast_t;

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

#ifdef __cplusplus
};
#endif


#endif


