#include <stdlib.h>
#include <string.h>
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

void char_magic_string_builder_close(char_magic_string_builder* builder) {
	free(builder->string);
	free(builder);
}

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
		builder->string = realloc(builder->string, new_capacity);
		builder->capacity = new_capacity;
	}
	builder->string[builder->length++] = c;
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
	view.length = (*builder).length;
	view.string = malloc(sizeof (char*) * view.length + 1);
	strncpy(view.string, builder->string, view.length);
	view.string[view.length] = '\0';
	char_magic_string_builder_close(builder);
	return view;
}


int char_magic_string_builder_concat(char_magic_string_view str1, char_magic_string_view str2) {
	return 0;
}

char_magic_string_builder** char_magic_string_view_split(char_magic_string_view string_view, char separator) {
	char_magic_string_builder** builders = malloc(sizeof (char_magic_string_view*) * 10);
	int builders_i = 0;
	char_magic_string_builder* current_builder = char_magic_string_builder_init();

	for (int i = 0; i != string_view.length; i++) {
		char c = string_view.string[i];
		if (c == separator) {
			builders[builders_i++] = current_builder;
			current_builder = char_magic_string_builder_init();
		} else {
			char_magic_string_builder_append(current_builder, c);
		}
	}
	builders[builders_i] = current_builder;
	return builders;
}

int main() {
	char_magic_string_builder* builder = char_magic_string_builder_from_char_pointer("Das ist ein Test");
	char_magic_string_builder_append(builder, 'C');
	char_magic_string_builder_append(builder, 'C');
	char_magic_string_builder_append(builder, 'H');

	char_magic_string_view view = char_magic_string_builder_build(builder);

	char_magic_string_builder** builders = char_magic_string_view_split(view, ' ');

	for (int i = 0; i != 10; i++) {
		if (builders[i] == NULL) {
			break;
		}
		char_magic_string_view v = char_magic_string_builder_build(builders[i]);
		printf("Length: %d Value: %s\n", v.length, v.string);
	}

	printf("Length: %d; Value: %s", view.length, view.string);
}

