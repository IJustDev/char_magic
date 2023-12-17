#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_STRING_LENGTH 10

typedef struct {
	char* string;
	int length;
	int capacity;
} cm_string_builder;

typedef struct {
	char* string;
	int length;
} cm_string_view;

void cm_string_builder_close(cm_string_builder* builder) {
	free(builder->string);
	free(builder);
}

cm_string_builder* cm_string_builder_init() {
	cm_string_builder* builder = malloc(sizeof (cm_string_builder*));
	builder->length = 0;
	builder->capacity = INITIAL_STRING_LENGTH;
	builder->string = malloc(INITIAL_STRING_LENGTH);

	return builder;
}

void cm_string_builder_append(cm_string_builder* builder, char c) {
	if (builder->length == builder->capacity) {
		size_t new_capacity = builder->capacity * 2;
		builder->string = realloc(builder->string, new_capacity);
		builder->capacity = new_capacity;
	}
	builder->string[builder->length++] = c;
}


cm_string_builder* cm_string_builder_from_char_pointer(char* str) {
	cm_string_builder* builder = cm_string_builder_init();
	int index = 0;
	char c = ' ';
	while (c != '\0') {
		c = str[index++];
		if (c == '\0') break;
		cm_string_builder_append(builder, c);
	}
	return builder;
}

cm_string_view cm_string_builder_build(cm_string_builder* builder) {
	cm_string_view view = {0};
	view.length = (*builder).length;
	view.string = malloc(sizeof (char*) * view.length + 1);
	strncpy(view.string, builder->string, view.length);
	view.string[view.length] = '\0';
	cm_string_builder_close(builder);
	return view;
}

cm_string_view cm_string_view_from_char_pointer(char* str) {
	return cm_string_builder_build(cm_string_builder_from_char_pointer(str));
}

int cm_string_builder_concat(cm_string_view str1, cm_string_view str2) {
	// TODO
	return 0;
}

cm_string_view* cm_string_view_split(cm_string_view string_view, char separator) {
	cm_string_view* views = malloc(sizeof (cm_string_builder*) * 64); // TODO don't do this.
	cm_string_builder* current_builder = cm_string_builder_init();

	int views_index = 0;
	for (int i = 0; i != string_view.length; i++) {
		char c = string_view.string[i];
		if (c == separator) {
			views[views_index++] = cm_string_builder_build(current_builder);
			current_builder = cm_string_builder_init();
		} else {
			cm_string_builder_append(current_builder, c);
		}
	}
	views[views_index] = cm_string_builder_build(current_builder);
	return views;
}

void cm_string_builder_append_string_view(cm_string_builder* builder, cm_string_view string_view) {
	for (int i = 0; i != string_view.length; i++) {
		char c = string_view.string[i];
		if (c == '\0') continue;
		cm_string_builder_append(builder, c);
	}
}

int main() {
	cm_string_builder* builder = cm_string_builder_from_char_pointer("Hallo Welt,das ist ein Test");
	cm_string_builder_append_string_view(
		builder, cm_string_view_from_char_pointer(",Oder nicht?")
	);
	
	cm_string_view view = cm_string_builder_build(builder);
	cm_string_view args = cm_string_view_from_char_pointer(view.string);

	cm_string_view* views = cm_string_view_split(args, ',');
	cm_string_view current_view = views[0];

	int i = 1;
	do {
		printf("%s\n", current_view.string);
		current_view = views[i++];
	} while (current_view.string != NULL);
}

