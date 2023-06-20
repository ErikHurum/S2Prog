/* setlocale.c Forwardning functions for all locales. */
/* Copyright (C) 2003 IAR Systems.  All rights reserved. */
#include <yvals.h>
#include <locale.h>

#include <xlocale.h>
#include <xtls.h>
#include <limits.h>

#if _DLIB_FULL_LOCALE_SUPPORT

/*
 * The current lconv structure.
 */

_TLS_DEFINE_INIT(,struct lconv, _Locale_lconv) =
{
  "", "", "", "", "", "", "",
  CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX,
  CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX,
  ".",
  "", "", "", "",
  "false",
  "true",
  "",
  ""
};
_TLS_DEFINE_NO_INIT(,struct lconv, _Locale_lconv);


struct lconv * localeconv()
  /* Return the current locale. */
{
  return (struct lconv *)_TLS_DATA_PTR(_Locale_lconv);
}


#else /* _DLIB_FULL_LOCALE_SUPPORT */

struct lconv * localeconv()
  /* Return the current locale. */
{
  extern const struct lconv _LOCALE_WITH_USED(lconv);
  return (struct lconv *)&_LOCALE_WITH_USED(lconv);
}

#endif /* _DLIB_FULL_LOCALE_SUPPORT */
