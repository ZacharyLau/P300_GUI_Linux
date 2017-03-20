#include <gtk/gtk.h>

GtkWidget *paned;
GtkWidget *addFileButton;
GtkWidget *clearAllFilesButton;
GtkWidget *mainGrid;
GtkWidget *weightsLoadedLabel;
GtkWidget *filePrefixTextview;
GtkWidget *fileNumbertoSaveTextview;

GtkWidget *mudButton;
GtkWidget *prmButton;
GtkWidget *prmV2Button;


void feature_weights_paned_setting(GtkWidget *featurePaned){

  paned = featurePaned;
  gtk_container_set_border_width(GTK_CONTAINER(paned), 12);
  
  
  mainGrid = gtk_grid_new();
  gtk_grid_set_column_homogeneous(mainGrid, TRUE);
  gtk_grid_set_row_homogeneous(mainGrid, TRUE);
  gtk_container_add(GTK_CONTAINER(paned), mainGrid);
  gtk_grid_set_row_spacing(mainGrid, 10);
  gtk_grid_set_column_spacing(mainGrid, 10);
    
  add_file_button_setting();

  clear_all_files_button_setting();

  weights_loaded_label_setting("No Weights Loaded");

  GtkWidget *emptyLabel = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(mainGrid), emptyLabel, 0, 5, 3, 3);
  
  file_prefix_text_view_setting();

  file_number_to_save_text_view_setting();

  three_buttons_setting();

}

void three_buttons_setting(){
  mudButton = gtk_button_new_with_label("*.mud");
  prmButton = gtk_button_new_with_label("*.prm");
  prmV2Button = gtk_button_new_with_label("*.prm(v2)");

  gtk_grid_attach(GTK_GRID(mainGrid), mudButton, 0, 10, 2, 2);
  gtk_grid_attach(GTK_GRID(mainGrid), prmButton, 2, 10, 2, 2);
  gtk_grid_attach(GTK_GRID(mainGrid), prmV2Button, 4, 10, 2, 2);
}

void file_number_to_save_text_view_setting(){
  GtkWidget *fileNumberLabel = gtk_label_new("File #'s to Save: ");
  gtk_grid_attach(GTK_GRID(mainGrid), fileNumberLabel, 0, 9, 3, 1);

  fileNumbertoSaveTextview = gtk_text_view_new();
//  gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(respWindowTextview)), "0 800", -1); 
  gtk_grid_attach(GTK_GRID(mainGrid), fileNumbertoSaveTextview, 3, 9, 3, 1);
}

void file_prefix_text_view_setting(){
  GtkWidget *filePrefixLabel = gtk_label_new("File Prefix: ");
  gtk_grid_attach(GTK_GRID(mainGrid), filePrefixLabel, 0, 8, 3, 1);

  filePrefixTextview = gtk_text_view_new();
//  gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(respWindowTextview)), "0 800", -1); 
  gtk_grid_attach(GTK_GRID(mainGrid), filePrefixTextview, 3, 8, 3, 1);

}

void add_file_button_setting(){
  addFileButton = gtk_button_new_with_label("Add *.mud Files");
  gtk_grid_attach(GTK_GRID(mainGrid), addFileButton, 1, 0, 4, 2);
}

void clear_all_files_button_setting(){
  clearAllFilesButton = gtk_button_new_with_label("Clear All*.mud Files");
  gtk_grid_attach(GTK_GRID(mainGrid), clearAllFilesButton, 1, 2, 4, 2);
}

void weights_loaded_label_setting(char *string){
  widget_destroyer(gtk_grid_get_child_at(GTK_GRID(mainGrid), 0, 4));
  weightsLoadedLabel = gtk_label_new(string);
  gtk_grid_attach(GTK_GRID(mainGrid), weightsLoadedLabel, 0, 4, 6, 1);
}





