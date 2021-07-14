#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char *variableList[1000]; int variableIndex = 0;
int integerList[1000] = { 0 }; int intIndex= 0;

bool checKeyword(char* str) {

	if (!strcmp(str, "int") ||
		!strcmp(str, "move") || !strcmp(str, "to") || !strcmp(str, "add") ||
		!strcmp(str, "sub") || !strcmp(str, "from") ||
		!strcmp(str, "loop") || !strcmp(str, "times") ||
		!strcmp(str, "out")) {
		return true;
	}

	return false;
}

bool checkInteger(char* str) {
	
	int len = strlen(str);

	if (len > 100) {
		return false;
	}
	
	for (int i = 0; i < len; i++) {
		if (i > 0) {
			if (str[i] == '-' || len == 1) {
				return false;
			}
		}
		if (!(isdigit(str[i]) || str[i] == '-')) {
			return false;
		}
	}

	return true;
}

bool checkIntegerVariable(char* str) {

	for (int i = 0; i < variableIndex; i++) {
		if (!strcmp(str, variableList[i])) {
			return true;
		}
	}

	return false;
}

bool checkVariable(char* str)
{
	int len = strlen(str);

	if (len > 20) {
		return false;
	}

	for (int i = 0; i < len; i++) {
		if (str[0] == '_') {
			return false;
		}
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_'))) {
			return false;
		}
	}

	return true;
}

void parser(char* code) {
	int lineCount = 0;
	char *line[1000];
	char *splitCode = strtok(code, ".");
	while (splitCode != NULL) {
		line[lineCount++] = splitCode;
		splitCode = strtok(NULL, ".");
	}
	
	for (int i = 0; i < lineCount; i++) {
		
		int wordCount = 0;
		char *word[1000];
		char *splitLine = strtok(line[i], " \n\r[]\"");
		while (splitLine != NULL) {
			word[wordCount++] = splitLine;
			splitLine = strtok(NULL, " \n\r");
		}

		if (wordCount == 0) { return; }
		
		
		//Int kontrol word count 2
		if (!strcmp(word[0], "int")) {

			//Variable
			if (word[1] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Variable is expected it must be notNULL.\n");
				return 0;
			}
			else if (checKeyword(word[1])) {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is a keyword. Variable is expected.\n", word[1]);
				return 0;
			}
			else if (checkVariable(word[1])) {
			

				variableList[variableIndex++] = word[1];
				integerList[intIndex++] = 0;
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is not a variable. Variable is expected.\n", word[1]);
				return 0;
			}

			// Yeterli Uzunluga Ulasti Tree
			if (wordCount == 2) {
				
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("End of line is expected.\n");
				return 0;
			}
		}


		//Move kontrl word count 4
		else if (!strcmp(word[0], "move")) {
			

			//Integer Or Variable
			int moveInt = 0;
			if (word[1] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Integer or variable are expected it must be notNULL.\n");
				return 0;
			}
			else if (checKeyword(word[1])) {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is a keyword. Integer or variable are expected.\n", word[1]);
				return 0;
			}
			else if (checkInteger(word[1])) {
				

				moveInt = atoi(word[1]);
			}
			else if (checkIntegerVariable(word[1])) {
				

				for (int i = 0; i < variableIndex; i++) {
					if (!strcmp(variableList[i], word[1])) {
						moveInt = integerList[i];
						break;
					}
				}
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is not a integer or variable. Integer or variable are expected.\n", word[1]);
				return 0;
			}

			//To kontrol word count 2-4
			if (word[2] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Keyword 'to' is expected it must be notNULL.\n");
				return 0;
			}
			else if (!strcmp(word[2], "to")) {
				
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("Keyword 'to' is expected.\n");
				return 0;
			}

			//Variable 
			if (word[3] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Variable is expected it must be notNULL.\n");
				return 0;
			}
			else if (checKeyword(word[3])) {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is a keyword. Variable is expected.\n", word[3]);
				return 0;
			}
			else if (checkIntegerVariable(word[3])) {
				

				for (int i = 0; i < variableIndex; i++) {
					if (!strcmp(variableList[i], word[3])) {
						integerList[i] = moveInt;
						break;
					}
				}
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is not a variable. Variable is expected.\n", word[3]);
				return 0;
			}

			//EOF
			if (wordCount == 4) {
				
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("End of line is expected.\n");
				return 0;
			}
		}


		//Add kontrol word count 4
		else if (!strcmp(word[0], "add")) {
			

			//Integer Or Variable
			int addInt = 0;
			if (word[1] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Integer or variable are expected it must be notNULL.\n");
				return 0;
			}
			else if (checKeyword(word[1])) {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is a keyword. Integer or variable are expected.\n", word[1]);
				return 0;
			}
			else if (checkInteger(word[1])) {
				

				addInt = atoi(word[1]);
			}
			else if (checkIntegerVariable(word[1])) {
				

				for (int i = 0; i < variableIndex; i++) {
					if (!strcmp(variableList[i], word[1])) {
						addInt = integerList[i];
						break;
					}
				}
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is not a integer or variable. Integer or variable are expected.\n", word[1]);
				return 0;
			}

			//To
			if (word[2] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Keyword 'to' is expected it must be notNULL.\n");
				return 0;
			}
			else if (!strcmp(word[2], "to")) {
				
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("Keyword 'to' is expected.\n");
				return 0;
			}

			//Variable
			if (word[3] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Variable is expected it must be notNULL.\n");
				return 0;
			}
			else if (checKeyword(word[3])) {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is a keyword. Variable is expected.\n", word[3]);
				return 0;
			}
			else if (checkIntegerVariable(word[3])) {
				

				for (int i = 0; i < variableIndex; i++) {
					if (!strcmp(variableList[i], word[3])) {
						integerList[i] += addInt;
						break;
					}
				}
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is not a variable. Variable is expected.\n", word[3]);
				return 0;
			}

			//EOF
			if (wordCount == 4) {
				
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("End of line is expected.\n");
				return 0;
			}
		}


		//Subs 4 word count
		else if (!strcmp(word[0], "sub")) {
			

			//Integer Or Variable
			int subInt = 0;
			if (word[1] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Integer or variable are expected it must be notNULL.\n");
				return 0;
			}
			else if (checKeyword(word[1])) {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is a keyword. Integer or variable are expected.\n", word[1]);
				return 0;
			}
			else if (checkInteger(word[1])) {
				

				subInt = atoi(word[1]);
			}
			else if (checkIntegerVariable(word[1])) {
				

				for (int i = 0; i < variableIndex; i++) {
					if (!strcmp(variableList[i], word[1])) {
						subInt = integerList[i];
						break;
					}
				}
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is not a integer or variable. Integer or variable are expected.\n", word[1]);
				return 0;
			}

			//From
			if (word[2] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Keyword 'from' is expected it must be notNULL.\n");
				return 0;
			}
			else if (!strcmp(word[2], "from")) {
			
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("Keyword 'from' is expected.\n");
				return 0;
			}

			//Variable
			if (word[3] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Variable is expected it must be notNULL.\n");
				return 0;
			}
			else if (checKeyword(word[3])) {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is a keyword. Variable is expected.\n", word[3]);
				return 0;
			}
			else if (checkIntegerVariable(word[3])) {
				

				for (int i = 0; i < variableIndex; i++) {
					if (!strcmp(variableList[i], word[3])) {
						integerList[i] -= subInt;
						break;
					}
				}
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is not a variable. Variable is expected.\n", word[3]);
				return 0;
			}

			//EOF
			if (wordCount == 4) {
				
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("End of line is expected.\n");
				return 0;
			}
		}

		//Out
		else if (!strcmp(word[0], "out")) {
		

			//Integer, Variable Or String
			if (word[1] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Integer, variable or string are expected.\n");
				return 0;
			}
			else if (checkInteger(word[1])) {
				

				printf("Integer Value: %s\n", word[1]);
			}
			else if (checkIntegerVariable(word[1])) {
				

				for (int i = 0; i < variableIndex; i++) {
					if (!strcmp(variableList[i], word[1])) {
						printf("'%s' variable value: %i \n", word[1], integerList[i]);
						break;
					}
				}
			}
			else {
				printf("%s\n", word[1]);
			}

			//EOF
			if (wordCount == 2) {
				
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("End of line is expected.\n");
				return 0;
			}
		}

		//Loop 4 word count
		else if (!strcmp(word[0], "loop")) {
			

			//Integer Or Variable
			int loopInt = 0;
			if (word[1] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Integer or variable are expected it must be notNULL.\n");
				return 0;
			}
			else if (checKeyword(word[1])) {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is a keyword. Integer or variable are expected.\n", word[1]);
				return 0;
			}
			else if (checkInteger(word[1])) {
				

				loopInt = atoi(word[1]);
			}
			else if (checkIntegerVariable(word[1])) {
				

				for (int i = 0; i < variableIndex; i++) {
					if (!strcmp(variableList[i], word[1])) {
						loopInt = integerList[i];
						break;
					}
				}
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("'%s' is not a integer or variable. Integer or variable are expected.\n", word[1]);
				return 0;
			}

			//Times
			if (word[2] == NULL) {
				printf("Error Handled, Line is:%d \n",i);
				printf("Keyword 'times' is expected it must be notNULL.\n");
				return 0;
			}
			else if (!strcmp(word[2], "times")) {
				
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("Keyword 'times' is expected.\n");
				return 0;
			}

			//Code
			for (int i = 0; i < loopInt; i++) {
				char newCode[100] = "";
				for (int i = 3; i < wordCount; i++) {
					strcat(newCode, " ");
					strcat(newCode, word[i]);
				}
				strcat(newCode, ".");
				parser(newCode);
			}

			//EOF
			if (wordCount > 4) {
				
			}
			else {
				printf("Error Handled, Line is:%d \n",i);
				printf("End of line is expected.\n");
				return 0;
			}
		}

		else {
			
		}
	}
}

char commentLine[100]; char leftComment[100]; char rightComment[100];
void remover(char* str) {
	bool trueComment = false;
	int j;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '{') {
			for (j = i; j < strlen(str); j++) {
				if (str[j] == '}') {
					substring(str, i + 1, j - i - 1, commentLine);
					substring(str, 0, i, leftComment);
					substring(str, j + 1, strlen(str), rightComment);
					strcat(leftComment, rightComment);
					strcpy(str, leftComment);

					trueComment = true;

					remover(str);
				}
			}
			if (!trueComment) {
				
				printf("Comment Line is not completed.\n");
				exit(0);
			}
		}
	}
}
int substring(char *source, int from, int n, char *temp) {
	int length, i;
	for (length = 0; source[length] != '\0'; length++);
	if (from > length) {
		return 1;
	}
	if ((from + n) > length) {
		n = (length - from);
	}
	for (i = 0; i < n; i++) {
		temp[i] = source[from + i];
	}
	temp[i] = '\0';
	return 0;
}

int main(int argc, char *argv[]) {
	
	
	FILE *fp;
	long lSize;
	char *code;

	char *SourcefilePath = argv[1];
	char ba[] = ".ba";
	strncat(SourcefilePath, ba,3);

	fp = fopen(SourcefilePath, "rb");
	if (!fp) perror(SourcefilePath), exit(1);

	fseek(fp, 0L, SEEK_END);
	lSize = ftell(fp);
	rewind(fp);

	code = calloc(1, lSize + 1);
	if (!code) fclose(fp), fputs("memory alloc fails", stderr), exit(1);

	if (1 != fread(code, lSize, 1, fp)) {
		fclose(fp), free(code), fputs("entire read fails", stderr), exit(1);
	}

	remover(code);
	parser(code);
}
