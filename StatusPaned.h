#include <gtk/gtk.h>

GtkWidget *paned;
GtkWidget *readyLabel;

void status_paned_setting(GtkWidget *featurePaned){

  paned = featurePaned;
  gtk_container_set_border_width(GTK_CONTAINER(paned), 12);
  
  
  mainGrid = gtk_grid_new();
  gtk_grid_set_column_homogeneous(mainGrid, TRUE);
  gtk_grid_set_row_homogeneous(mainGrid, TRUE);
  gtk_container_add(GTK_CONTAINER(paned), mainGrid);
  gtk_grid_set_row_spacing(mainGrid, 10);
  gtk_grid_set_column_spacing(mainGrid, 10);


  ready_label_setting("Ready");
  ready_label_setting("not ready");
  

}

void ready_label_setting(char* string){
  widget_destroyer(gtk_grid_get_child_at(GTK_GRID(mainGrid), 0, 0));
  readyLabel = gtk_label_new(string);
  gtk_grid_attach(GTK_GRID(mainGrid), readyLabel, 0, 0, 6, 2);
}


