// tutorials
// https://www.youtube.com/watch?v=PnWsKLux2zI
// https://www.youtube.com/watch?v=TPyiNl_fmyQ&list=PLEs_0O72adQBUpcPJv7dKaElGwyzVljtk&pp=iAQB


#include <gtk/gtk.h>


/*
// add the button at the end 
static GtkWidget *pasta_label = NULL; // Global pointer for the label

static void
print_hello (GtkWidget *widget, gpointer data){
  // Check if the label has been created
  if (!pasta_label) {
    pasta_label = gtk_label_new("Pasta");
    // Add the label to the box container, assuming `data` is a pointer to the box
    gtk_box_append(GTK_BOX(data), pasta_label);
  } else {
    // Make sure the label is visible
    gtk_widget_show(pasta_label);
    // Update the label's text to "Pasta" in case it needs to be reset
    gtk_label_set_text(GTK_LABEL(pasta_label), "Pasta");
  }
}
*/

static GtkWidget *label_pasta; // Declare the label globally
bool pasta_status = FALSE;

static void
print_hello (GtkWidget *widget, gpointer data){
  // Show/hide the label when the "Hello World" button is clicked
  if (!pasta_status){
    gtk_widget_set_visible(label_pasta, TRUE);
    pasta_status = TRUE;
  }
  else{
    gtk_widget_set_visible(label_pasta, FALSE);
    pasta_status = FALSE;
  }
}

static void
on_quit_clicked (GtkWidget *widget, gpointer data){
  GApplication *app = G_APPLICATION(data); // Cast the user_data to GApplication
  g_application_quit(app); // Quit the application
}

static void
activate (GtkApplication *app, gpointer user_data){
  GtkWidget *window;
  GtkWidget *button_hello;
  GtkWidget *button_quit;
  GtkWidget *box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Pasta-label");
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 200);

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

  gtk_box_set_spacing(GTK_BOX(box), 10);  // Set spacing between children (buttons) of the box
  gtk_window_set_child (GTK_WINDOW (window), box);

  button_hello = gtk_button_new_with_label ("Pasta?");
  button_quit = gtk_button_new_with_label ("Quit");

  label_pasta = gtk_label_new("Yay!\nPasta!");
  gtk_widget_set_visible(label_pasta, FALSE); // Hide the label initially
  
  g_signal_connect (button_hello, "clicked", G_CALLBACK (print_hello), NULL); 
  g_signal_connect (button_quit, "clicked", G_CALLBACK (on_quit_clicked), app); // Pass the GtkApplication as user_data

  gtk_box_append (GTK_BOX (box), button_hello);
  gtk_box_append (GTK_BOX (box), label_pasta);
  gtk_box_append (GTK_BOX (box), button_quit);

  gtk_window_present (GTK_WINDOW (window));
}

int
main (int argc, char **argv){
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
