/* -*- mode: c++ -*-
 * Kaleidoscope-Focus -- Bidirectional communication plugin
 * Copyright (C) 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Kaleidoscope.h>

#if FOCUS_WITHOUT_DOCS
#define FOCUS_HOOK(n, d) ({                               \
      static KaleidoscopePlugins::Focus::HookNode _c = {  \
        &n, NULL, NULL};                                  \
      &_c;                                                \
    })
#else
#define FOCUS_HOOK(n, d) ({                               \
      static KaleidoscopePlugins::Focus::HookNode _c = {  \
        &n, F(d), NULL};                                  \
      &_c;                                                \
    })
#endif

namespace KaleidoscopePlugins {
class Focus : public KaleidoscopePlugin {
 public:
  typedef bool (*Hook)(const char *command);
  typedef struct HookNode {
    Hook handler;
    const __FlashStringHelper *docs;
    HookNode *next;
  } HookNode;

  Focus(void);

  void begin(void) final;

  static void addHook(HookNode *newNode);
  static const HookNode *getRootNode(void);

  /* Helpers */
  static void printNumber(uint16_t number);
  static void printSpace(void);
  static void printColor(uint8_t r, uint8_t g, uint8_t b);
  static void printSeparator(void);
  static void printBool(bool b);

 private:
  static HookNode *rootNode;
  static char command[32];

  static void loopHook(bool postClear);
  static void drain(void);
};
};

extern KaleidoscopePlugins::Focus Focus;

namespace FocusHooks {
bool help(const char *command);
bool version(const char *command);
};

#define FOCUS_HOOK_HELP    FOCUS_HOOK(FocusHooks::help, "help")
#define FOCUS_HOOK_VERSION FOCUS_HOOK(FocusHooks::version, "version")
