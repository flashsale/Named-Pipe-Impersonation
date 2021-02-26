#include <iostream>
#include <Windows.h>

const int MESSAGE_SIZE = 512;

int main()
{
	LPCWSTR pipeName = L"\\\\127.0.0.1\\pipe\\pipe-server";
	HANDLE clientPipe = NULL;
	BOOL isPipeRead = true;
	wchar_t message[MESSAGE_SIZE] = { 0 };
	DWORD bytesRead = 0;

	std::wcout << "Connecting to " << pipeName << std::endl;
	// Creates or opens an I/O device
	clientPipe = CreateFile(pipeName,							// Connect to the I/O device (pipe)
		GENERIC_READ | GENERIC_WRITE,		// Both RW, allowed bc Acces Duplex
		0,									// Share Mode, 0 means the file(pipe) cannot be opened
											  // by another process until we close our handle
		NULL,								// Security Attr, NULL = Handle can't be inherited by child processes
		OPEN_EXISTING,						// Creation Disposition, Only open device if it exists
		0,									// Flags and Attributes, not sure what 0 means, prob inherit
		NULL								// Template File, ignored if opening existing file, can be NULL
	);

	while (isPipeRead) {
		// Read data from a specificed I/O device
		isPipeRead = ReadFile(clientPipe, &message, MESSAGE_SIZE, &bytesRead, NULL);
		std::wcout << "Received message: " << message;
	}
	std::cout << "Finished";
	getchar();
	return 0;
}