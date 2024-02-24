
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "checkers_handler.h"


// Some global variables
static cairo_surface_t *surface = NULL;
static unsigned int canvas_width = 100;
static unsigned int canvas_height = 100;
static bool draw_square_status = FALSE;
int* array_board;

static void on_quit_clicked (GtkWidget *widget, gpointer data){
  GApplication *app = G_APPLICATION(data); // Cast the user_data to GApplication
  g_application_quit(app); // Quit the application
}

static void draw_square(GtkButton *button, gpointer user_data){
  // Hide the draw button
  gtk_widget_set_visible(button, FALSE);

  // Set the flag to draw the square
  draw_square_status = TRUE;

  // Queue redraw of the drawing area
  GtkWidget *drawing_area = GTK_WIDGET(user_data);
  gtk_widget_queue_draw(drawing_area);
}

static void reset_drawing(GtkButton *button, gpointer user_data){
  // Set the flag to draw the square
  draw_square_status = FALSE;

  // Queue redraw of the drawing area
  GtkWidget *drawing_area = GTK_WIDGET(user_data);
  gtk_widget_queue_draw(drawing_area);

  // Show the draw button again
  GtkWidget *draw_button = g_object_get_data(G_OBJECT(button), "draw_button");
  gtk_widget_set_visible(draw_button, TRUE);
}

// Note: This function is copied from https://docs.gtk.org/gtk4/getting_started.html
static void clear_surface(void){
  cairo_t *cr;

  cr = cairo_create(surface);

  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);

  cairo_destroy(cr);
}

/* Create a new surface of the appropriate size to store our scribbles */
// Note: This function is copied from https://docs.gtk.org/gtk4/getting_started.html
static void resize_cb(GtkWidget *widget, int width, int height, gpointer data){
  if (surface){
    cairo_surface_destroy(surface);
    surface = NULL;
  }

  if (gtk_native_get_surface(gtk_widget_get_native (widget))){
    surface = gdk_surface_create_similar_surface(gtk_native_get_surface(gtk_widget_get_native(widget)),
                                                  CAIRO_CONTENT_COLOR,
                                                  gtk_widget_get_width(widget),
                                                  gtk_widget_get_height(widget));

    /* Initialize the surface to white */
    clear_surface();
  }
  canvas_width = width;
  canvas_height = height;
}

static void clicked_left(GtkGestureClick *gesture, int n_press, double x, double y, GtkWidget *area)
{
  const unsigned int size_x = canvas_width / 8;
  const unsigned int size_y = canvas_height / 8;

  printf("Index in a array would be (%d,%d)\n", (int) x/size_x, (int) y/size_y);
}


static void create_board(cairo_t *cr){
  const unsigned int size_x = canvas_width / 8;
  const unsigned int size_y = canvas_height / 8;
  unsigned int pos_x = size_x;
  unsigned int pos_y = 0;
  const unsigned int to_center = MIN(size_x, size_y)/2; // ditance between pos_x/pos_y to center of the box
  const unsigned int radius = (int) MIN(size_x, size_y)/2.5;
  
  // Set the drawing color to black for the square

  for (unsigned int j = 0; j < 8; j++){
    for (unsigned int i = 0; i < 4; i++){
      // Draw a square
      cairo_set_source_rgb(cr, 0, 0, 0);
      cairo_rectangle(cr, pos_x, pos_y, size_x, size_y);
      cairo_fill(cr);
      
      if (j != 3 && j != 4){
        // Drawing the disk
        cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
        cairo_arc(cr, pos_x+to_center, pos_y+to_center, radius, 0, 2 * G_PI);
        cairo_fill(cr);
      }

      pos_x += size_x + size_x; // it's faster to do additions than multiplications
    }

    pos_y += size_y;
    if (j%2 == 0){pos_x = 0;}
    else {pos_x = size_x;}
  }
}

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
  // Set the background color to white
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); // RGB values for white
  cairo_paint(cr); // Paints the current source everywhere within the current clip region.

  if (draw_square_status) {
    create_board(cr);
  }
}


void on_app_activate(GApplication *app, gpointer user_data) {
  // --- Declaring variables ---
  // main stuff
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
  GtkWidget *drawing_area = gtk_drawing_area_new();
  GtkWidget *frame; // Container for the drawing area
  GtkWidget *grid = gtk_grid_new(); // Container for the buttons
  GtkWidget *vbox; // Container for vertical layout (for the frame and grid)

  // buttons
  GtkWidget *button_reset;
  GtkWidget *button_quit;
  GtkWidget *button_draw;
  
  // drawing area events (or "bindings")
  GtkGesture *left_click;

  
  // --- The actual code --- 

  // an array for the grid
  array_board = checkers_create_grid();
  printf("test %d\n", array_get(array_board, 0,1));


  gtk_window_set_title(GTK_WINDOW (window), "A squared square");
  gtk_window_set_default_size(GTK_WINDOW (window), 425, 460);
  
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // 5 pixels of spacing between children
  gtk_window_set_child(GTK_WINDOW(window), vbox);

  // set up the grid
  gtk_widget_set_halign (grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (grid, GTK_ALIGN_CENTER);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  // gtk_window_set_child(GTK_WINDOW(window), grid);

  // drawing area
  gtk_widget_set_size_request(drawing_area, canvas_width, canvas_height);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_function, NULL, NULL);
  g_signal_connect_after (drawing_area, "resize", G_CALLBACK (resize_cb), NULL);

  // create buttons
  button_reset = gtk_button_new_with_label("Reset");
  button_quit = gtk_button_new_with_label("Quit");
  button_draw = gtk_button_new_with_label("Draw Square");
  
  // connect buttons
  g_signal_connect(button_quit, "clicked", G_CALLBACK(on_quit_clicked), app); // Pass the GtkApplication as user_data
  g_signal_connect(button_reset, "clicked", G_CALLBACK(reset_drawing), drawing_area); // Pass the GtkApplication as user_data
  g_object_set_data(G_OBJECT(button_reset), "draw_button", button_draw); // Pass button_draw to button_reset for later use
  g_signal_connect(button_draw, "clicked", G_CALLBACK(draw_square), drawing_area); 

  // Create a frame and ensure the frame expands vertically
  frame = gtk_frame_new(NULL);
  gtk_frame_set_child(GTK_FRAME(frame), drawing_area);
  gtk_box_append(GTK_BOX(vbox), frame);
  gtk_widget_set_vexpand(frame, TRUE); 

  gtk_box_append(GTK_BOX(vbox), grid);

  // grid some stuff
  gtk_grid_attach(GTK_GRID(grid), button_draw, 0, 0, 2, 1); // x,y,spanx,spany = 0, 0, 2, 1
  gtk_grid_attach(GTK_GRID(grid), button_reset, 0, 2, 1, 1); 
  gtk_grid_attach(GTK_GRID(grid), button_quit, 1, 2, 1, 1);


  // --- Drawing_area events handler --- 

  // for the left click of the mouse
  left_click = gtk_gesture_click_new();
  gtk_gesture_single_set_button(GTK_GESTURE_SINGLE (left_click), GDK_BUTTON_PRIMARY);
  gtk_widget_add_controller(drawing_area, GTK_EVENT_CONTROLLER (left_click));
  g_signal_connect(left_click, "pressed", G_CALLBACK (clicked_left), drawing_area);



  gtk_window_present(GTK_WINDOW(window)); // display the window
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  // Use G_APPLICATION_DEFAULT_FLAGS and ensure the application ID is valid
  app = gtk_application_new("Gtk.Application", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  // don't forget to free the memory
  free(array_board);

  return status;
}