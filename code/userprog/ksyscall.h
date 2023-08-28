/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"
#include "synchconsole.h"


void SysHalt()
{
  kernel->interrupt->Halt();
}

void SysPrintInt(int val)
{ 
  DEBUG(dbgTraCode, "In ksyscall.h:SysPrintInt, into synchConsoleOut->PutInt, " << kernel->stats->totalTicks);
  kernel->synchConsoleOut->PutInt(val);
  DEBUG(dbgTraCode, "In ksyscall.h:SysPrintInt, return from synchConsoleOut->PutInt, " << kernel->stats->totalTicks);
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

int SysCreate(char *filename)
{
	// return value
	// 1: success
	// 0: failed
	return kernel->fileSystem->Create(filename);
}


// Open a file with the name, and returns its corresponding OpenFileId. 
// Return -1 if fail to open the file.
OpenFileId SysOpen(char *name) // 191012[J]: 似乎可以了?
{
  return kernel->fileSystem->OpenAFile(name);
}

// Write “size” characters from the buffer into the file, 
// and return the number of characters actually written to the file. 
// Return -1, if fail to write the file. 
int SysWrite(char *buffer, int size, OpenFileId id)
{
  return kernel->fileSystem->WriteFile0(buffer, size, id);
}

// Read “size” characters from the file to the buffer, 
// and return the number of characters actually read from the file. 
// Return -1, if fail to read the file.
int SysRead(char *buffer, int size, OpenFileId id)
{
  return kernel->fileSystem->ReadFile(buffer, size, id);
}

// Close the file with id. 
// Return 1 if successfully close the file. Otherwise, return -1.
int SysClose(OpenFileId id)
{
  return kernel->fileSystem->CloseFile(id);
}

#endif /* ! __USERPROG_KSYSCALL_H__ */