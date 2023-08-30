// filesys/filetable.cc

#include "filetable.h"

FileTable::FileTable() {
    fileTable = new FileTableEntry[MAX_OPEN_FILES];
    for (int i = 0; i < MAX_OPEN_FILES; ++i) {
        fileTable[i].openFile = nullptr;
        fileTable[i].inUse = false;
    }
}

FileTable::~FileTable() {
    for (int i = 0; i < MAX_OPEN_FILES; ++i) {
        if (fileTable[i].openFile != nullptr) {
            delete fileTable[i].openFile;
        }
    }
    delete[] fileTable;
}

OpenFileId FileTable::Open(OpenFile *openFile) {
    // Find an available file descriptor
    int fileId = -1;
    for (int i = 0; i < MAX_OPEN_FILES; ++i) {
        if (!fileTable[i].inUse) {
            fileId = i;
            break;
        }
    }

    if (fileId == -1) {
        return -1; // No available file descriptors
    }

    fileTable[fileId].openFile = openFile;
    fileTable[fileId].inUse = true;

    return fileId;
}

int FileTable::Write(char *buffer, int size, OpenFileId id) {
    if (id < 0 || id >= MAX_OPEN_FILES || !fileTable[id].inUse) {
        return -1; // Invalid file descriptor
    }

    return fileTable[id].openFile->Write(buffer, size);
}

int FileTable::Read(char *buffer, int size, OpenFileId id) {
    if (id < 0 || id >= MAX_OPEN_FILES || !fileTable[id].inUse) {
        return -1; // Invalid file descriptor
    }

    return fileTable[id].openFile->Read(buffer, size);
}

int FileTable::Close(OpenFileId id) {
    if (id < 0 || id >= MAX_OPEN_FILES || !fileTable[id].inUse) {
        return -1; // Invalid file descriptor
    }

    delete fileTable[id].openFile;
    fileTable[id].openFile = nullptr;
    fileTable[id].inUse = false;

    return 1;
}
