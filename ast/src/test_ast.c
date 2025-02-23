
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

static void print_ast (ast_t *node, size_t depth, void *params)
{
   (void)params;
   for (size_t i=0; i<depth; i++) {
      putchar(' ');
   }

   printf ("%s: %p\n", ast_get_tag (node), ast_get_payload (node));
}

int main (void)
{
   int ret = EXIT_FAILURE;
   ast_t *ast = ast_new (NULL, "1", 1, 1);
   if (!ast)
      goto cleanup;

   ast_walk (ast, print_ast, NULL);

   ret = EXIT_SUCCESS;
cleanup:
   ast_del (&ast);
   return ret;
}

