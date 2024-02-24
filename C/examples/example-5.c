#include <gtk/gtk.h>

static unsigned int canvas_width = 500;
static unsigned int canvas_height = 400;
static bool draw_square_status = FALSE;

static void on_quit_clicked (GtkWidget *widget, gpointer data){
  GApplication *app = G_APPLICATION(data); // Cast the user_data to GApplication
  g_application_quit(app); // Quit the application
}

static void draw_square(GtkButton *button, gpointer user_data) {
  // Set the flag to draw the square
  draw_square_status = TRUE;

  // Queue redraw of the drawing area
  GtkWidget *drawing_area = GTK_WIDGET(user_data);
  gtk_widget_queue_draw(drawing_area);

  // Hide the draw button
  gtk_widget_set_visible(button, FALSE);
}

static void reset_drawing(GtkButton *button, gpointer user_data) {
  // Set the flag to draw the square
  draw_square_status = FALSE;

  // Queue redraw of the drawing area
  GtkWidget *drawing_area = GTK_WIDGET(user_data);
  gtk_widget_queue_draw(drawing_area);

  // Show the draw button again
  GtkWidget *draw_button = g_object_get_data(G_OBJECT(button), "draw_button");
  gtk_widget_set_visible(draw_button, TRUE);
}

static void create_board(cairo_t *cr){
  const unsigned int size_x = canvas_width / 8;
  const unsigned int size_y = canvas_height / 8;
  unsigned int pos_x = 0;
  unsigned int pos_y = 0;
  
  // Set the drawing color to black for the square
  cairo_set_source_rgb(cr, 0, 0, 0);

  for (unsigned int j = 0; j < 8; j++){
    for (unsigned int i = 0; i < 4; i++){
      // Draw a square
      cairo_rectangle(cr, pos_x, pos_y, size_x, size_y);
      cairo_fill(cr);
      pos_x += size_x + size_x; // it's faster to do additions than multiplications
    }
    pos_y += size_y;
    if (j%2 == 1){pos_x = 0;}
    else {pos_x = size_x;}
  }
}

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
  // Set the background color to white
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); // RGB values for white
  cairo_paint(cr); // Paints the current source everywhere within the current clip region.

  if (draw_square_status) {
    create_board(cr);
  }
}

static void on_app_activate(GApplication *app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
  GtkWidget *grid = gtk_grid_new();
  GtkWidget *drawing_area = gtk_drawing_area_new();

  gtk_window_set_title(GTK_WINDOW (window), "A squared square");
  // gtk_window_set_default_size(GTK_WINDOW (window), canvas_width+25, canvas_height+100);
  
  // set up the grid
  gtk_widget_set_halign (grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (grid, GTK_ALIGN_CENTER);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_window_set_child(GTK_WINDOW(window), grid);

  // drawing area
  gtk_widget_set_size_request(drawing_area, canvas_width, canvas_height);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_function, NULL, NULL);

  // create buttons
  GtkWidget *button_reset = gtk_button_new_with_label("Reset");
  GtkWidget *button_quit = gtk_button_new_with_label("Quit");
  GtkWidget *button_draw = gtk_button_new_with_label("Draw Square");
  
  // connect buttons
  g_signal_connect(button_quit, "clicked", G_CALLBACK(on_quit_clicked), app); // Pass the GtkApplication as user_data
  g_signal_connect(button_reset, "clicked", G_CALLBACK(reset_drawing), drawing_area); // Pass the GtkApplication as user_data
  g_object_set_data(G_OBJECT(button_reset), "draw_button", button_draw); // Pass button_draw to button_reset for later use
  g_signal_connect(button_draw, "clicked", G_CALLBACK(draw_square), drawing_area); 

  // grid everthing
  gtk_grid_attach(GTK_GRID(grid), button_draw, 0, 0, 2, 1); // x,y,spanx,spany = 0, 0, 2, 1
  gtk_grid_attach(GTK_GRID(grid), drawing_area, 0, 1, 2, 1); // x,y,spanx,spany = 0, 1, 2, 1
  gtk_grid_attach(GTK_GRID(grid), button_reset, 0, 2, 1, 1); 
  gtk_grid_attach(GTK_GRID(grid), button_quit, 1, 2, 1, 1);


  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  // Use G_APPLICATION_DEFAULT_FLAGS and ensure the application ID is valid
  app = gtk_application_new("com.example.GtkApplication", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
