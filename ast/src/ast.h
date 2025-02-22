
#ifndef H_AST
#define H_AST

typedef struct ast_t ast_t;

#ifdef __cplusplus
extern "C" {
#endif

   ast_t *ast_new (void);
   void ast_del (ast_t *ast);

#ifdef __cplusplus
};
#endif


#endif


