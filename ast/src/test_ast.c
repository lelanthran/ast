
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ds_str.h"

#include "ast.h"

static void free_payload (ast_t *node, void *params, size_t depth)
{
   (void)params;
   for (size_t i=0; i<depth; i++) {
      putchar(' ');
   }

   printf ("[%s]: [%s]\n", ast_get_tag (node), (char *)ast_get_payload (node));
   free (ast_get_payload (node));
}

int main (void)
{
   int ret = EXIT_FAILURE;
   ast_t *ast = ast_new (NULL, "1", 1, 1);
   if (!ast)
      goto cleanup;

   ast_set_tag (ast, "root-tag");
   ast_set_payload (ast, ds_str_dup ("root payload"));
   ast_walk (ast, free_payload, NULL);

   ret = EXIT_SUCCESS;
cleanup:
   ast_del (&ast);
   return ret;
}

