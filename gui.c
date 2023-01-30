#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  GtkWidget *window;
  GtkWidget *text_view;
  GtkWidget *reference_view;
  char *filename;
} AppData;

static void select_word(GtkTextView *text_view, GtkTextIter *iter,
                       GtkTextBuffer *buffer) {
  GtkTextIter start, end;
  if (gtk_text_iter_starts_word(iter)) {
    start = end = *iter;
  } else {
    end = *iter;
    start = *iter;
    gtk_text_iter_backward_word_start(&start);
  }
  gtk_text_iter_forward_word_end(&end);
  gtk_text_buffer_select_range(buffer, &start, &end);

  AppData *data = g_object_get_data(G_OBJECT(text_view), "app-data");
  GtkTextBuffer *reference_buffer =
      gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->reference_view));
  gtk_text_buffer_set_text(reference_buffer, "", -1);

  char *word = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  char buffer[1024];
  int line_number = 1;
  FILE *file = fopen(data->filename, "r");
  while (fgets(buffer, 1024, file) != NULL) {
    if (strstr(buffer, word) != NULL) {
      char line_text[1024];
      sprintf(line_text, "%d: %s", line_number, buffer);
      gtk_text_buffer_insert_at_cursor(
          reference_buffer, line_text, -1);
    }
    line_number++;
  }
  fclose(file);
  g_free(word);
}

static gboolean text_view_button_release(GtkWidget *widget,
                                         GdkEventButton *event,
                                         gpointer data) {
  if (event->button == 1) {
    GtkTextIter iter;
    GtkTextView *text_view = GTK_TEXT_VIEW(widget);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    gtk_text_view_get_iter_at_location(text_view, &iter, event->x, event->y);
    select_word(text_view, &iter, buffer);
  }
  return FALSE;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }

  gtk_init(&argc, &argv);

 
