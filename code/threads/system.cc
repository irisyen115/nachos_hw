// threads/system.cc

#include "filetable.h"

void Initialize() {
    // ...
    fileSystem->Initialize();
    // ...
    fileTable = new FileTable();
    // ...
}
