#include <stdio.h>
#include <stdbool.h>
#include <libxml/xmlreader.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

char *validateXml(char *xmlPath, char *xsdPath);