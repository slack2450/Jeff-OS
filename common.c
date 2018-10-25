void* memset(void* bufptr, int value, unsigned int size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (unsigned int i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}
