#ifndef LANGS_H
#define LANGS_H

namespace Base {

enum SUPPORTED_LANGUAGE {
  MINIMUM_LANG_INDEX = 0,
  TYPESCRIPT = 0,
  CPP = 1,

  // Testing purposes
  TESTLANG = 2,
  WGSL = 3,
  NUM_OF_LANG_SUPPORTED,
};

} // Base

#endif /* LANGS_H */
