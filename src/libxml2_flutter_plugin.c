#include "libxml2_flutter_plugin.h"

// A very short-lived native function.
//
// For very short-lived functions, it is fine to call them on the main isolate.
// They will block the Dart execution while running the native function, so
// only do this for native functions which are guaranteed to be short-lived.
FFI_PLUGIN_EXPORT intptr_t sum(intptr_t a, intptr_t b) { return a + b; }

// A longer-lived native function, which occupies the thread calling it.
//
// Do not call these kind of native functions in the main isolate. They will
// block Dart execution. This will cause dropped frames in Flutter applications.
// Instead, call these native functions on a separate isolate.
FFI_PLUGIN_EXPORT intptr_t sum_long_running(intptr_t a, intptr_t b)
{
  // Simulate work.
#if _WIN32
  Sleep(5000);
#else
  usleep(5000 * 1000);
#endif
  return a + b;
}

charptr_t static void schemaParseErrorHandler(void *arg, xmlErrorPtr error)
{
  fprintf(stderr, "Error at line %d, column %d\n%s", error->line, error->int2, error->message);
  *((bool *)arg) = true;
}

FFI_PLUGIN_EXPORT char *validateXml(char *xmlPath, char *xsdPath)
{
  xmlInitParser();
  xmlSchemaPtr schema = NULL;
  xmlSchemaParserCtxtPtr schema_parser_ctxt = NULL;
  int has_schema_errors = 0;
  int ret = -1;
  xmlSchemaValidCtxtPtr valid_ctxt = NULL;
  if ((schema_parser_ctxt = xmlSchemaNewParserCtxt(xsdPath)))
  {
    schema = xmlSchemaParse(schema_parser_ctxt);
    xmlSchemaFreeParserCtxt(schema_parser_ctxt);
    if (schema)
    {
      valid_ctxt = xmlSchemaNewValidCtxt(schema);
    }
  }
  xmlTextReaderPtr reader = NULL;
  reader = xmlReaderForFile(xmlPath, NULL, 0);

  if (reader != NULL)
  {
    if (valid_ctxt)
    {
      xmlTextReaderSchemaValidateCtxt(reader, valid_ctxt, 0);
      xmlSchemaSetValidStructuredErrors(valid_ctxt, schemaParseErrorHandler, &has_schema_errors);
    }
    ret = xmlTextReaderRead(reader);
    while (ret == 1 && !has_schema_errors)
    {
      //... procesing informations
      ret = xmlTextReaderRead(reader);
    }
  }

  char *buf = malloc(sizeof(char) * 1000);
  ;

  if (ret != 0)
  {
    xmlErrorPtr err = xmlGetLastError();
    sprintf(buf, "%s: failed to parse in line %d, col %d. Error %d: %s\n",
            err->file,
            err->line,
            err->int2,
            err->code,
            err->message);
  }
  else
  {
    buf = NULL;
  }
  xmlFreeTextReader(reader);
  xmlCleanupParser();

  return buf;
}
