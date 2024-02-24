// creates chess AI : https://www.youtube.com/watch?v=l0bv8IgELfU

// tutorials
// https://www.youtube.com/watch?v=PnWsKLux2zI
// https://www.youtube.com/watch?v=TPyiNl_fmyQ&list=PLEs_0O72adQBUpcPJv7dKaElGwyzVljtk&pp=iAQB


#include <gtk/gtk.h>


static GtkWidget *label_pasta; // Declare the label globally
bool pasta_status = FALSE;

static void print_hello(GtkWidget *widget, gpointer data){
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

static void activate(GtkApplication *app, gpointer user_data){
  GtkWidget *window;
  GtkWidget *button_hello;
  GtkWidget *button_quit;
  GtkWidget *grid;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "Pasta-label");
  gtk_window_set_default_size(GTK_WINDOW (window), 400, 200);

  grid = gtk_grid_new();
  // grid = gtk_grid_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (grid, GTK_ALIGN_CENTER);

  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_window_set_child (GTK_WINDOW (window), grid);

  button_hello = gtk_button_new_with_label("Pasta?");
  button_quit = gtk_button_new_with_label("Quit");

  /* // this is not working
  gtk_widget_set_hexpand(button_hello, FALSE); // to prevent the button from expanding horizontally
  gtk_widget_set_vexpand(button_hello, FALSE); // and vertically.
  gtk_widget_set_size_request(button_hello, 40, 25); // to force the button to a specific size.
  */
  label_pasta = gtk_label_new("Yay!\nPasta!");
  gtk_widget_set_visible(label_pasta, FALSE); // Hide the label initially
  
  g_signal_connect(button_hello, "clicked", G_CALLBACK(print_hello), NULL); 
  g_signal_connect(button_quit, "clicked", G_CALLBACK(on_quit_clicked), app); // Pass the GtkApplication as user_data


  gtk_grid_attach(GTK_GRID(grid), button_hello, 0, 0, 1, 1); // x,y,spanx,spany = 0, 0, 1, 1
  gtk_grid_attach(GTK_GRID(grid), label_pasta, 1, 0, 1, 1); // x,y,spanx,spany = 1, 0, 1, 1
  gtk_grid_attach(GTK_GRID(grid), button_quit, 0, 1, 1, 1); 

  gtk_window_present(GTK_WINDOW (window));
}

int main(int argc, char **argv){
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
