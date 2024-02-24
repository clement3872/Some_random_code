// copy pasted from https://docs.gtk.org/gtk4/getting_started.html

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

static void
close_window (void)
{
  if (surface)
    cairo_surface_destroy (surface);
}

static void on_quit_clicked (GtkWidget *widget, gpointer data){
  if (surface)
    cairo_surface_destroy (surface);
  GApplication *app = G_APPLICATION(data); // Cast the user_data to GApplication
  g_application_quit(app); // Quit the application
}

static void
activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *drawing_area;
  GtkWidget *button_quit;
  GtkWidget *vbox; // Container for vertical layout

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Drawing Area");

  // Create a vertical box with a small spacing between children
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_window_set_child(GTK_WINDOW(window), vbox);

  frame = gtk_frame_new(NULL);
  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, 150, 150); // Optional, sets a minimum size

  gtk_frame_set_child(GTK_FRAME(frame), drawing_area);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_cb, NULL, NULL);
  g_signal_connect_after (drawing_area, "resize", G_CALLBACK (resize_cb), NULL);

  // Add the frame to the vbox and allow it to expand
  gtk_box_append(GTK_BOX(vbox), frame);
  gtk_widget_set_vexpand(frame, TRUE); // Ensure the frame expands vertically

  // Create the button and add it below the frame without allowing it to expand
  button_quit = gtk_button_new_with_label("Quit");
  g_signal_connect(button_quit, "clicked", G_CALLBACK(on_quit_clicked), app);
  gtk_box_append(GTK_BOX(vbox), button_quit);
  gtk_widget_set_vexpand(button_quit, FALSE); // Button should not expand, it stays at its natural height

  gtk_window_present(GTK_WINDOW(window));
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
