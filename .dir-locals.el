((nil . ((eval . (progn
                   (require 'projectile)
                   (require 'dap-mode)
                   (dap-register-debug-template
                    "Interpreter Unittests"
                    (list
                     :type "gdb"
                     :request "launch"
                     :name "Interpreter Unittests"
                     :target (concat (projectile-project-root) "./bazel-bin/src/interpreter_unittests")
                     :cwd nil))
                   (dap-register-debug-template
                    "Chameleons Main Unittests"
                    (list
                     :type "gdb"
                     :request "launch"
                     :name "CHAMELEONS_MAIN_UNITTESTS"
                     :target (concat (projectile-project-root) "./bazel-bin/src/TransEngine/TransLang/chameleonsmain_unittest")
                     :cwd nil
                     ))
                   )))))
