#ifndef CONFIG_H
#define CONFIG_H

// Enable GC by default
#ifndef ENABLE_GC
#if __linux__
#define ENABLE_GC true
#elif __APPLE__
#define ENABLE_GC false
#endif
#endif

/* Macros that enforce to define */
namespace Chameleon::Config {

enum Configs {
  GC = ENABLE_GC
};

template<Configs config>
concept isGCEnable = Configs::GC == true;

} // Config

#endif /* CONFIG_H */
