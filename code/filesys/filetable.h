// filesys/filetable.h

#ifndef FILETABLE_H
#define FILETABLE_H

#include "filehdr.h"
#include "openfile.h"

class FileTableEntry {
public:
    OpenFile *openFile;   // The opened file
    bool inUse;           // Is this file table entry in use?
};

class FileTable {
public:
    FileTable();          // Initialize the file table
    ~FileTable();         // De-allocate the file table

    OpenFileId Open(OpenFile *openFile);
    int Write(char *buffer, int size, OpenFileId id);
    int Read(char *buffer, int size, OpenFileId id);
    int Close(OpenFileId id);

private:
    FileTableEntry *fileTable;   // The actual file table
};

#endif // FILETABLE_H
