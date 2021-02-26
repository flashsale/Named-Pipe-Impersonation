
#include <Windows.h>
#include <iostream>

int main() {
	LPCWSTR pipeName = L"\\\\.\\pipe\\pipe-server";
	LPVOID pipeBuffer = NULL;
	HANDLE serverPipe;
	DWORD readBytes = 0, readBuffer = 0, bytesWritten = 0;
	int err = 0;
	BOOL isPipeConnected, isPipeOpen;
	wchar_t message[] = L"CLA";
	DWORD messageLength = lstrlen(message) * 2;

	std::wcout << "Creating named pipe " << pipeName << std::endl;
	serverPipe = CreateNamedPipe(pipeName,						// Unique pipe name LPCSTR
		PIPE_ACCESS_DUPLEX,			// Open mode flags (* Bi-directional pipe *)
		PIPE_TYPE_MESSAGE,				// Pipe mode (* Msg written to console *)
		1,								// Max Instances
		2048,							// Output buffer reserved bytes
		2048,							// Input buffer reserved bytes
		0,								// Time out value (0=50ms)
		NULL							// Securitty Attributes
	);				 // Returns a handle to the server end of the named pipe instance

	// Returns differently if it is sync or async, not sure how to set or determine that, either way non zero is success
	// Pass in handle to pipe and OverLapped Structure? Null if not
	isPipeConnected = ConnectNamedPipe(serverPipe, NULL);
	if (isPipeConnected) {
		std::wcout << "Incoming connection to " << pipeName << std::endl;
	}

	std::wcout << "Sending message: " << message << std::endl;

	// Write to a specified I/O device, returns nonzero on success
	WriteFile(serverPipe,			// Handle to device, in our case the pipe instead of a file
		message,				// Buffer to write to file
		messageLength,		// Buffer size to be written
		&bytesWritten,		// OUT number of bytes written
		NULL					// Overlapped is back, I should learn what this means.. NULL for non overlapped though so
	);

	return 0;
}