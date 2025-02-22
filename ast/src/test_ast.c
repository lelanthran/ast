
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

int main (void)
{
   int ret = EXIT_FAILURE;
   ast_t *ast = ast_new ();
   if (!ast)
      goto cleanup;

   ret = EXIT_SUCCESS;
cleanup:
   ast_del (ast);
   return ret;
}

