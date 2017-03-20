//LIBS = 'pkg-config --libs gtk+-3.0';
//CFLAGS = 'pkg-config --cflags gtk+-3.0';  
#include <gtk/gtk.h>

// emacs ftw!!!
int main(int argc, char ** argv)
{
  GtkWidget *MainWindow;

  gtk_init(&argc, &argv);

  MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title(GTK_WINDOW(MainWindow), "My Application");
  gtk_window_set_default_size(GTK_WINDOW(MainWindow), 400, 300);
  gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);
  gtk_widget_show_all(MainWindow);

  g_signal_connect(G_OBJECT(MainWindow),"destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return 0;
}

