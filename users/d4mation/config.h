#define FORCE_NKRO

/* Assume Windows-based Keymap for things like Macros */
#ifndef WINDOWS_LAYOUT_IS_DEFAULT
    #define WINDOWS_LAYOUT_IS_DEFAULT true
#endif

/* Enable "CMD Overlay" when using Windows */
#ifndef CMD_WINDOWS_ENABLE
    #define CMD_WINDOWS_ENABLE false
#endif

/* CTRL is in the position that you expect CMD to be in */
#ifndef CMD_WINDOWS_DEFAULT_CTRL
    #define CMD_WINDOWS_DEFAULT_CTRL true
#endif
