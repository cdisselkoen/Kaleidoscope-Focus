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
#define FOCUS_COMMAND(n, d) ({                        \
    static KaleidoscopePlugins::Focus::Command _c = { \
      &n, NULL, NULL};                                \
    &_c;                                              \
    })
#else
#define FOCUS_COMMAND(n, d) ({                          \
      static KaleidoscopePlugins::Focus::Command _c = { \
        &n, F(d), NULL};                                \
      &_c;                                              \
    })
#endif

namespace KaleidoscopePlugins {
  class Focus : public KaleidoscopePlugin {
  public:
    typedef bool (*commandHandler) (const char *command);
    typedef struct Command {
      commandHandler handler;
      const __FlashStringHelper *docs;
      Command *next;
    } Command;

    Focus (void);

    virtual void begin (void) final;

    static void addCommand (Command *command);
    static const Command *getRootCommand (void);

  private:
    static Command *rootCommand;
    static char command[32];

    static void loopHook (bool postClear);
  };
};

extern KaleidoscopePlugins::Focus Focus;

namespace FocusCommands {
  bool help (const char *command);
  bool version (const char *command);
};

#define FOCUS_CMD_HELP FOCUS_COMMAND(FocusCommands::help, \
                                     "help\n"             \
                                     "----\n"             \
                                     "This screen.")

#define FOCUS_CMD_VERSION FOCUS_COMMAND(FocusCommands::version,         \
                                        "version\n"                     \
                                        "-------\n"                     \
                                        "Print the running firmware version.")
