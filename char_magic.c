#include <stdlib.h>
#include <stdio.h>

#define INITIAL_STRING_LENGTH 10

typedef struct {
	char* string;
	int length;
	int capacity;
} char_magic_string_builder;

typedef struct {
	char* string;
	int length;
} char_magic_string_view;

char_magic_string_builder* char_magic_string_builder_init() {
	char_magic_string_builder* builder = malloc(sizeof (char_magic_string_builder*));
	builder->length = 0;
	builder->capacity = INITIAL_STRING_LENGTH;
	builder->string = malloc(INITIAL_STRING_LENGTH);

	return builder;
}

void char_magic_string_builder_append(char_magic_string_builder* builder, char c) {
	if (builder->length == builder->capacity) {
		size_t new_capacity = builder->capacity * 2;
		printf("Reallocating!");
		builder->string = realloc(builder->string, new_capacity);
		builder->capacity = new_capacity;
	}
	printf("%d", builder->length);
	builder->string[builder->length++] = c;
	printf("%c ", builder->string[builder->length - 1]);
	printf("%s | %c\n", builder->string, c);
}

char_magic_string_builder* char_magic_string_builder_from_char_pointer(char* str) {
	char_magic_string_builder* builder = char_magic_string_builder_init();
	int index = 0;
	char c = ' ';
	while (c != '\0') {
		c = str[index++];
		if (c == '\0') break;
		char_magic_string_builder_append(builder, c);
	}
	return builder;
}

char_magic_string_view char_magic_string_builder_build(char_magic_string_builder* builder) {
	char_magic_string_view view = {0};
	view.length = builder->length;
	view.string = builder->string;
	view.string[view.length] = '\0';
	return view;
}

void char_magic_string_builder_close(char_magic_string_builder* builder) {
	free(builder->string);
	free(builder);
}

int char_magic_string_builder_concat(char_magic_string_view str1, char_magic_string_view str2) {
	return 0;
}

char_magic_string_view* split(char_magic_string_view string, char separator) {
	return NULL;
}

int main() {
	char_magic_string_builder* builder = char_magic_string_builder_from_char_pointer("Das ist ein Test");
	char_magic_string_builder_append(builder, 'C');
	char_magic_string_builder_append(builder, 'C');

	char_magic_string_builder_append(builder, 'H');

	char_magic_string_view view = char_magic_string_builder_build(builder);
	printf("%s", view.string);

	char_magic_string_builder_close(builder);
}
