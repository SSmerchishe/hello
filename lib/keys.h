#ifndef PROJECT_VERSION
#define PROJECT_VERSION "1.0.0"
#endif

#ifndef GIT_HASH
#define GIT_HASH "unknown"
#endif

#define APP_HELP                    \
	"Created by SSmerchishe."   \
	"\nAvailable keys:"         \
	"\n\t--help\t\t- Help;"     \
	"\n\t--version\t- Version." \
	"\n\t--githash\t- Git Hash. \n"

typedef enum { KEY_UNKNOW, KEY_HELP, KEY_VERSION, KEY_GIT_HASH } Keys;

//Прототипы функций
Keys get_key(const char *key);
void print_help();
void print_version();
void print_githash();
void print_default_msg();