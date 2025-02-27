
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "ds_str.h"
#include "ds_hmap.h"

#include "ast.h"




/* ************************************************** */

struct ast_t {
   // The source for this node (helpful for diagnostic messages)
   char    *srcfile_name;
   size_t   srcfile_line;
   size_t   srcfile_cpos;

   // A tag for this node, set by the caller. This is essentially the node name (if
   // a symbol) or the node value (if a literal)
   char    *tag;

   // A payload, managed by the caller
   void    *payload;

   // A set of key-value attributes
   ds_hmap_t *attributes;

   // The parent element, NULL if root node
   ast_t   *parent;

   // An ordered list of children
   size_t   nchildren;
   ast_t  **children;
};

static ast_t *ast_append_child (ast_t *parent, ast_t *child)
{
   if (!parent)
      return NULL;

   size_t newlen = parent->nchildren + 1;
   ast_t **tmp = realloc (parent->children, newlen * (sizeof *tmp));
   if (!tmp)
      return NULL;

   parent->children = tmp;
   parent->children[parent->nchildren] = child;
   return parent;
}

ast_t *ast_new (ast_t *parent,
                const char *srcfile_name,
                size_t srcfile_line,
                size_t srcfile_cpos)
{
   bool error = true;
   ast_t *ret = calloc (1, sizeof *ret);
   if (!ret)
      goto cleanup;

   if (parent) {
      if (!ast_append_child (parent, ret))
         goto cleanup;
   }

   if (!(ast_set_tag (ret, "")))
      goto cleanup;

   ret->srcfile_name = ds_str_dup (srcfile_name);
   ret->srcfile_line = srcfile_line;
   ret->srcfile_cpos = srcfile_cpos;

   error = false;
cleanup:
   if (error) {
      ast_del (&ret);
   }
   return ret;
}

static void attribute_free (const void *key, size_t key_len,
                            void *value, size_t value_len,
                            void *extra_param)
{
   (void)key;
   (void)key_len;
   (void)value_len;
   (void)extra_param;

   free (value);
}

void ast_del (ast_t **ast)
{
   if (!ast || !*ast)
      return;

   for (size_t i=0; i<(*ast)->nchildren; i++) {
      ast_del (&(*ast)->children[i]);
   }

   ds_hmap_iterate ((*ast)->attributes, attribute_free, NULL);

   free ((*ast)->srcfile_name);
   free ((*ast)->tag);
   free (*ast);
   *ast = NULL;
}




/* ************************************************** */

static void ast_walker_func (ast_t *ast,
                             ast_walker_func_t *fptr,
                             void *params,
                             size_t depth)
{
   if (!ast)
      return;

   fptr (ast, params, depth);
   for (size_t i=0; i<ast->nchildren; i++) {
      fptr (ast->children[i], params, depth + 1);
   }
}

void ast_walk (ast_t *ast, ast_walker_func_t *fptr, void *params)
{
   ast_walker_func (ast, fptr, params, 0);
}




/* ************************************************** */

void *ast_get_payload (ast_t *ast)
{
   if (!ast)
      return NULL;

   return ast->payload;
}

void *ast_set_payload (ast_t *ast, void *payload)
{
   if (!ast)
      return NULL;

   return ast->payload = payload;
}




/* ************************************************** */

const char *ast_get_tag (ast_t *ast)
{
   if (!ast)
      return NULL;

   return ast->tag;
}

const char *ast_set_tag (ast_t *ast, const char *tag)
{
   if (!ast || !tag)
      return NULL;

   free (ast->tag);
   return ast->tag = ds_str_dup (tag);
}


/* ************************************************** */

