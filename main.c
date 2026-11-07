//#include - готовый инструмент из библиотеки Линукса

#include <stdio.h> //Инструмент ввода-вывода (printf, fopen, fgets)

#include <stdlib.h> //Базовые функции системы такие как управление памятью, завершение программы и exit

#include <string.h> //Инструмент работы со строками
		    
#include <stdbool.h>

struct CPUInfo {
	char modelName[256];
	char vendorProc[256];

	int ProcCore;
};

int parse_cpu_info(struct CPUInfo *info) {
	FILE *file = fopen("/proc/cpuinfo", "r");
	
	bool IsModelNameFound = false;
	bool IsVendorFound = false;

	char buffer[256];

	if(file == NULL) {
		perror("Не удалось прочитать");
		return 1;
	}
	while(fgets(buffer, sizeof(buffer), file) /* читает одну строчку из открытого файла и следит что бы не превысила 256 байт */ != NULL) {
		if(strncmp(buffer, "model name", 10) == 0 /* Берет первые 10 символов из buffer сравнивает с буквосочитанием, если совпало возвращается 0 */ && IsModelNameFound == false) {
			IsModelNameFound = true;
			strncpy(info->modelName, buffer, sizeof(info->modelName));
			printf("%s", info->modelName);
		}
		else if(strncmp(buffer, "processor", 9) == 0) {
			info->ProcCore++;
		}
		else if(strncmp(buffer, "vendor_id", 9) == 0 && IsVendorFound == false) {
			IsVendorFound = true;
			strncpy(info->vendorProc, buffer, sizeof(info->vendorProc));
			printf("%s", info->vendorProc);
		}
	}

	printf("Кол-во ядер процессора: %d\n", info->ProcCore);
	fclose(file);
	return 0;
}

int main() {
	struct CPUInfo myCPU;

	parse_cpu_info(&myCPU);

	return 0;
}
