#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

#define print_err(STR) fprintf(stderr, "\x1b[31m%s\x1b[0m", STR);

uint32_t crc32(const unsigned char* buf, uint32_t len)
{
	uint32_t crc_table[256];
	uint32_t crc;

	for (unsigned int i = 0; i < 256; i++)
	{
		crc = i;
		for (unsigned int j = 0; j < 8; j++)
			crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

		crc_table[i] = crc;
	};

	crc = 0xFFFFFFFFUL;

	while (len--)
		crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);

	return crc ^ 0xFFFFFFFFUL;
}

int main(int argc, char** argv)
{
	char* file_name;
	if (argc != 3) {
		print_err("Expected command line arguments\n");
		print_err("./prog_name file_name hash_value\n");
		return -1;
	}

	file_name = argv[1];

	FILE* fp = fopen(file_name, "rb");

	if (!fp) {
		print_err("fopen(): error\n");
		fclose(fp);
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	uint32_t f_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	uint8_t* p_data = (uint8_t*)malloc(sizeof(*p_data) * f_size);
	fread(p_data, f_size, 1, fp);

	uint32_t crc32_cash = crc32(p_data, f_size);

	free(p_data);

	char* end;
	uint32_t cash = strtoul(argv[2], &end, 16);

	// exp: *end == '\0'
	if (*end) {
		print_err("strtoul(): error\n");
		fclose(fp);
		return -2;
	}

	if (cash == crc32_cash)
		fprintf(stdout, "cash == crc32_hash:\n%X == %X\n", cash, crc32_cash);
	else {
		print_err("File was corrupted\n");
		fclose(fp);
		return -3;
	}


	fclose(fp);

	return 0;
}
