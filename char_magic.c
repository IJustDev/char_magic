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

char_magic_string_view char_magic_string_view_from_char_pointer(char* str) {
	return char_magic_string_builder_build(char_magic_string_builder_from_char_pointer(str));
}

int char_magic_string_builder_concat(char_magic_string_view str1, char_magic_string_view str2) {
	// TODO
	return 0;
}

char_magic_string_view* char_magic_string_view_split(char_magic_string_view string_view, char separator) {
	char_magic_string_view* views = malloc(sizeof (char_magic_string_builder*) * 64); // TODO don't do this.
	char_magic_string_builder* current_builder = char_magic_string_builder_init();

	int views_index = 0;
	for (int i = 0; i != string_view.length; i++) {
		char c = string_view.string[i];
		if (c == separator) {
			views[views_index++] = char_magic_string_builder_build(current_builder);
			current_builder = char_magic_string_builder_init();
		} else {
			char_magic_string_builder_append(current_builder, c);
		}
	}
	views[views_index] = char_magic_string_builder_build(current_builder);
	return views;
}

void char_magic_string_builder_append_string_view(char_magic_string_builder* builder, char_magic_string_view string_view) {
	for (int i = 0; i != string_view.length; i++) {
		char c = string_view.string[i];
		if (c == '\0') continue;
		char_magic_string_builder_append(builder, c);
	}
}

int main() {
	char_magic_string_builder* builder = char_magic_string_builder_from_char_pointer("Hallo Welt,das ist ein Test");
	char_magic_string_builder_append_string_view(
		builder, char_magic_string_view_from_char_pointer(",Oder nicht?")
	);
	
	char_magic_string_view view = char_magic_string_builder_build(builder);
	char_magic_string_view args = char_magic_string_view_from_char_pointer(view.string);

	char_magic_string_view* views = char_magic_string_view_split(args, ',');
	char_magic_string_view current_view = views[0];

	int i = 1;
	do {
		printf("%s\n", current_view.string);
		current_view = views[i++];
	} while (current_view.string != NULL);
}

