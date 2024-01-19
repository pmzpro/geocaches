#define MAX_CODES 2000
Cache geocaches[MAX_CODES];

// typedef enum{EARTHCACHE, LETTERBOX, MULTI, PUZZLE, TRADITIONAL, VIRTUAL, WEBCAM} kind;
// typedef enum{MICRO, SMALL, REGULAR, LARGE, OTHER_SIZE, VIRTUALL, NOT_CHOSEN} size;
// typedef enum{AVAILABLE, DISABLED} status;

typedef struct {
    char *code;
    char *name;
    char *state;
    char *owner;
    double latitude;
    double longitude;
    char *kind;
    char *size;
    double difficulty;
    double terrain;
    char *status;
    char *hidden_date;
    int founds;
    int not_found;
    int favourites;
    int altitude;
} Cache;



void getGeocaches(const char file[], Cache geocaches[], int *geocacheCount);
void clearGeocaches(int *geocacheCount);
void listGeocaches(const Cache geocaches[], int geocacheCount);
void foundPGeocaches(const Cache geocaches[], int geocacheCount);
