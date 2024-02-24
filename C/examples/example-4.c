#include <gtk/gtk.h>

/* Surface to store current scribbles */
static cairo_surface_t *surface = NULL;

static void
clear_surface (void)
{
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

/* Create a new surface of the appropriate size to store our scribbles */
static void
resize_cb (GtkWidget *widget,
           int        width,
           int        height,
           gpointer   data)
{
  if (surface)
    {
      cairo_surface_destroy (surface);
      surface = NULL;
    }

  if (gtk_native_get_surface (gtk_widget_get_native (widget)))
    {
      surface = gdk_surface_create_similar_surface (gtk_native_get_surface (gtk_widget_get_native (widget)),
                                                    CAIRO_CONTENT_COLOR,
                                                    gtk_widget_get_width (widget),
                                                    gtk_widget_get_height (widget));

      /* Initialize the surface to white */
      clear_surface ();
    }
}

/* Redraw the screen from the surface. Note that the draw
 * callback receives a ready-to-be-used cairo_t that is already
 * clipped to only draw the exposed areas of the widget
 */
static void
draw_cb (GtkDrawingArea *drawing_area,
         cairo_t        *cr,
         int             width,
         int             height,
         gpointer        data)
{
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);
}

/* Draw a rectangle on the surface at the given position */
static void
create_rectangle(GtkWidget *widget,
            double     x,
            double     y,
            GtkWidget *surface)
{
  cairo_t *cr;

  /* Paint to the surface, where we store our state */
  cr = cairo_create (surface);

  cairo_rectangle(cr, x - 3, y - 3, 6, 6);
  cairo_fill(cr);

  cairo_destroy(cr);

  /* Now invalidate the drawing area. */
  gtk_widget_queue_draw(widget);
}


static void
pressed (GtkGestureClick *gesture,
         int              n_press,
         double           x,
         double           y,
         GtkWidget       *area)
{
  clear_surface ();
  gtk_widget_queue_draw (area);
}

static void
close_window (void)
{
  if (surface)
    cairo_surface_destroy (surface);
}


// Idk wtf this is, and it's used nowhere
static void window_map_cb(GtkWidget *window, gpointer data) {
    GtkWidget *drawing_area = GTK_WIDGET(data);
    gtk_widget_queue_draw(drawing_area);
}

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // Set the color for the background
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); // White background
    cairo_paint(cr); // Fill the background

    // Set the color for drawing
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0); // Black color

    // Draw a rectangle
    cairo_rectangle(cr, 10, 10, 100, 100); // Parameters: x, y, width, height
    cairo_fill(cr); // Fill the rectangle

    // More drawing code can go here...

    return FALSE; // Return FALSE to indicate that the signal was handled
}

static void
reset_drawing (GtkGestureClick *widget,
         GtkWidget       *area)
{
  clear_surface ();
  gtk_widget_queue_draw (area);
}

static void
on_quit_clicked (GtkWidget *widget, gpointer data){
  GApplication *app = G_APPLICATION(data); // Cast the user_data to GApplication
  g_application_quit(app); // Quit the application
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *drawing_area;
  GtkWidget *button_reset;
  GtkWidget *button_quit;
  GtkGesture *drag;
  GtkWidget *grid;
  GtkGesture *press;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Drawing Area");

  g_signal_connect (window, "destroy", G_CALLBACK (close_window), NULL);

  // create a grid
  grid = gtk_grid_new();
  gtk_widget_set_halign (grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (grid, GTK_ALIGN_CENTER);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_window_set_child (GTK_WINDOW (window), grid);

  frame = gtk_frame_new (NULL);
  // gtk_window_set_child (GTK_WINDOW (window), frame);


  drawing_area = gtk_drawing_area_new ();

  gtk_widget_set_size_request (drawing_area, 400, 300);
  gtk_frame_set_child (GTK_FRAME (frame), drawing_area);
  gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (drawing_area), draw_cb, NULL, NULL);
  g_signal_connect_after (drawing_area, "resize", G_CALLBACK (resize_cb), NULL);

  // create buttons
  button_reset = gtk_button_new_with_label("Reset");
  button_quit = gtk_button_new_with_label("Quit");
  // connect buttons
  g_signal_connect(button_reset, "clicked", G_CALLBACK(reset_drawing), drawing_area);
  g_signal_connect(button_quit, "clicked", G_CALLBACK(on_quit_clicked), app); // Pass the GtkApplication as user_data

  
  gtk_grid_attach(GTK_GRID(grid), frame, 0, 0, 2, 1); // x,y,spanx,spany = 0, 0, 1, 1
  gtk_grid_attach(GTK_GRID(grid), button_reset, 0, 1, 1, 1); // x,y,spanx,spany = 0, 0, 1, 1
  gtk_grid_attach(GTK_GRID(grid), button_quit, 1, 1, 1, 1);


  gtk_window_present (GTK_WINDOW (window));
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
