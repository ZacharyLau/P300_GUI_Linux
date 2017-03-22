#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>


GtkWidget *paned;
GtkWidget *mainGrid;

GtkWidget *selectTrainingDataButton;

GtkWidget *noTrainingDataLabel;

GtkWidget *samplingRatePaned;
GtkWidget *samplingRateIndicator;

GtkWidget *regressionCombobox;
GtkWidget *respWindowTextview;
GtkWidget *randomSampleTextview;

GtkWidget *spatialFiltterCombobox;
GtkWidget *lowpassCombobox;
GtkWidget *highpassCombobox;

GtkWidget *decimationFrequenciesTextview;
GtkWidget *maxModelFeaturesTextview;
GtkWidget *freespellFileTextview;

GtkWidget *channelSet1Textview;

GtkWidget *channelSet2Textview;
GtkWidget *channelSet2Checkbutton;

GtkWidget *createSpreadSheetCheckbutton;
GtkWidget *StdErrorCheckbutton;

GtkWidget *generateFeatureWeightsButton;
GtkWidget *creater2rPlotsButton;

//select training data dialog components 
GtkWidget *selectTrainingDataChooser;
GtkWidget *selectTrainingDataWindow;
//GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
gint res;
//Gtk_file_chooser
GtkWidget *selectTrainingDataDialog;
GSList *trainingDataList;

void select_training_data_dialog();
int concadenate_two_strings(char* , char* );
//********************************************************************************************
//****************************METHODS!!!!!!!!!!!!!!*******************************************


void training_data_paned_setting(GtkWidget *TrainingPaned){
  paned = TrainingPaned;
  gtk_container_set_border_width(GTK_CONTAINER(paned), 6);
//set main grid to paned
  mainGrid = gtk_grid_new();  
  gtk_grid_set_column_homogeneous(mainGrid, TRUE);
  gtk_grid_set_row_homogeneous(mainGrid, TRUE);
  gtk_container_add(GTK_CONTAINER(paned), mainGrid);
  gtk_grid_set_row_spacing(mainGrid, 3);
  gtk_grid_set_column_spacing(mainGrid, 10);

//set training data button 
  selectTrainingDataButton = gtk_button_new_with_label("Select Training Data");
  gtk_grid_attach(GTK_GRID(mainGrid), selectTrainingDataButton, 1, 0, 4, 1);
  g_signal_connect(G_OBJECT(selectTrainingDataButton), "clicked", G_CALLBACK(select_training_data_dialog), NULL);

//no training data label
  no_training_data_label_setting(1);

//sampling rate label  
  sampling_rate_label_setting("22");

//number of channels lebel
  number_of_channels_setting("18");

//number of sequences label
  number_of_sequences_setting("1");

//regression method label and combo box
  regression_method_combo_box_setting();

//resp. window label and text view
  resp_window_text_box_setting();

//random sample for training label and text view  
  random_sample_for_training_setting();

//spatial filtter label and combo box
  spatial_filtter_combo_box_setting();

//lowpass filtter label and combo box
  lowpass_combo_box_setting();

//highpass filtter label and combo box
  highpass_combo_box_setting();
  
//decimation frequencies label and textview
  decimation_frequencies_text_view_setting();

//max model features label and textview
  max_model_features_text_view_setting();
 
//freespell file label and textview
  freespell_file_text_view_setting();

//channel set 1 label and textview
  channel_set_1_text_view_setting();

//channel set 2 label and textview
  channel_set_2_text_view_setting();

//create spreadsheet and std error checkbox
  create_spreadsheet_and_std_error_check_box_setting();

//set generate feature weights button 
  generateFeatureWeightsButton = gtk_button_new_with_label("Generate Feature Weights");
  gtk_grid_attach(GTK_GRID(mainGrid), generateFeatureWeightsButton, 1, 19, 4, 1);

//set generate r^2 plots button 
  creater2rPlotsButton = gtk_button_new_with_label("Generate r^2 Plots");
  gtk_grid_attach(GTK_GRID(mainGrid), creater2rPlotsButton, 1, 20, 4, 1);

//set version information label
  GtkWidget *versionLabel = gtk_label_new("P300 Pretty fly for a G-U-I v0.1Beta (03/15/2017)");
  gtk_grid_attach(GTK_GRID(mainGrid), versionLabel, 0, 21, 6, 1);

}


void select_training_data_dialog(){
  
  
  selectTrainingDataChooser = gtk_file_chooser_dialog_new ("Open File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_OK, NULL);


  gtk_file_chooser_set_select_multiple(selectTrainingDataChooser, TRUE);
  selectTrainingDataDialog = gtk_dialog_run(GTK_DIALOG(selectTrainingDataChooser));

  trainingDataList = gtk_file_chooser_get_filenames(selectTrainingDataChooser);

  if(selectTrainingDataDialog == GTK_RESPONSE_OK){
    trainingDataList = gtk_file_chooser_get_filenames(selectTrainingDataChooser);
    printf("do something \n");
    fflush(stdout);
    for(int i = 0; i < g_slist_length(trainingDataList); i++){
      printf("%s \n", g_slist_nth_data (trainingDataList, i));
      fflush(stdout);
    }
  gtk_widget_destroy(selectTrainingDataChooser);
  return;
     
  }else{
    printf("do nothing \n");
    fflush(stdout);
    gtk_widget_destroy(selectTrainingDataChooser);
    return;
  }


  

}


void create_spreadsheet_and_std_error_check_box_setting(){
  GtkWidget *createSpreadSheetCheckbutton = gtk_check_button_new_with_label("Create Spreadsheet");
  gtk_grid_attach(GTK_GRID(mainGrid), createSpreadSheetCheckbutton, 0, 18, 4, 1);

  GtkWidget *StdErrorCheckbutton = gtk_check_button_new_with_label("Std Error");
  gtk_grid_attach(GTK_GRID(mainGrid), StdErrorCheckbutton, 4, 18, 2, 1);
}

void channel_set_2_text_view_setting(){
  GtkWidget *channel2Frame = gtk_frame_new("");
  channelSet2Checkbutton = gtk_check_button_new_with_label("Channel Set 2: ");
  gtk_frame_set_label_widget(channel2Frame, channelSet2Checkbutton);
  gtk_grid_attach(GTK_GRID(mainGrid), channel2Frame, 0, 16, 6, 2);
  
  GtkWidget *textPaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_set_border_width(GTK_CONTAINER(textPaned), 6);
  gtk_container_add(GTK_CONTAINER(channel2Frame), textPaned);

  channelSet2Textview = gtk_text_view_new();
  gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(channelSet2Textview)), "1 2 3 4 5 6 7 8 9 10 11 12 13 14", -1); 
  
  gtk_container_add(GTK_CONTAINER(textPaned), channelSet2Textview);

}

void channel_set_1_text_view_setting(){

  GtkWidget *channel1Frame = gtk_frame_new("Channel Set 1: ");
  gtk_frame_set_shadow_type(GTK_FRAME(channel1Frame), GTK_SHADOW_IN);
  gtk_grid_attach(GTK_GRID(mainGrid), channel1Frame, 0, 14, 6, 2);

  GtkWidget *textPaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_set_border_width(GTK_CONTAINER(textPaned), 6);
  gtk_container_add(GTK_CONTAINER(channel1Frame), textPaned);
  channelSet1Textview = gtk_text_view_new();
  gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(channelSet1Textview)), "1 2 3 4 5 6 7 8", -1); 
  gtk_container_add(GTK_CONTAINER(textPaned), channelSet1Textview);

}

void freespell_file_text_view_setting(){

  GtkWidget *freespellFileLabel = gtk_label_new("Freespell File: ");
  gtk_grid_attach(GTK_GRID(mainGrid), freespellFileLabel, 0, 13, 2, 1);

  freespellFileTextview = gtk_text_view_new();
  gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(freespellFileTextview)), "None", -1); 
  gtk_grid_attach(GTK_GRID(mainGrid), freespellFileTextview, 2, 13, 4, 1);

}

void decimation_frequencies_text_view_setting(){
  GtkWidget *decimationFrequenciesLabel = gtk_label_new("Decimation Frequencies (HZ): ");
  gtk_grid_attach(GTK_GRID(mainGrid), decimationFrequenciesLabel, 0, 11, 4, 1);

  decimationFrequenciesTextview = gtk_text_view_new();
  gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(decimationFrequenciesTextview)), "20", -1); 
  gtk_grid_attach(GTK_GRID(mainGrid), decimationFrequenciesTextview, 4, 11, 2, 1);
  
}

void max_model_features_text_view_setting(){
  GtkWidget *maxModelFeaturesLabel = gtk_label_new("Max Model Features: ");
  gtk_grid_attach(GTK_GRID(mainGrid), maxModelFeaturesLabel, 0, 12, 4, 1);

  maxModelFeaturesTextview = gtk_text_view_new();
  gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(maxModelFeaturesTextview)), "60", -1); 
  gtk_grid_attach(GTK_GRID(mainGrid), maxModelFeaturesTextview, 4, 12, 2, 1);
   
} 

void spatial_filtter_combo_box_setting(){

  GtkWidget *spatialFiltterLabel = gtk_label_new("Spatial Filtter: ");
  gtk_grid_attach(GTK_GRID(mainGrid), spatialFiltterLabel, 0, 8, 3, 1);

  spatialFiltterCombobox = gtk_combo_box_text_new();
  char *itemLabels[] = {"Raw Only", "Raw & CAR", "CAR Only"};
  for (int i=0; i<G_N_ELEMENTS(itemLabels); i++){
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(spatialFiltterCombobox), itemLabels[i]);
  }
  gtk_combo_box_set_active(GTK_COMBO_BOX(spatialFiltterCombobox), 0);
  gtk_grid_attach(GTK_GRID(mainGrid), spatialFiltterCombobox, 3, 8, 3, 1);
}

void lowpass_combo_box_setting(){

  GtkWidget *lowpassLabel = gtk_label_new("Lowpass: ");
  gtk_grid_attach(GTK_GRID(mainGrid), lowpassLabel, 0, 9, 3, 1);

  lowpassCombobox = gtk_combo_box_text_new();
  char *itemLabels[] = {"None", "10", "20", "30", "40", "50"};
  for (int i=0; i<G_N_ELEMENTS(itemLabels); i++){
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(lowpassCombobox), itemLabels[i]);
  }
  gtk_combo_box_set_active(GTK_COMBO_BOX(lowpassCombobox), 0);
  gtk_grid_attach(GTK_GRID(mainGrid), lowpassCombobox, 3, 9, 3, 1);
}

void highpass_combo_box_setting(){

  GtkWidget *highpassLabel = gtk_label_new("Highpass: ");
  gtk_grid_attach(GTK_GRID(mainGrid), highpassLabel, 0, 10, 3, 1);

  highpassCombobox = gtk_combo_box_text_new();
  char *itemLabels[] = {"None", "0.25", "0.5", "1.0"};
  for (int i=0; i<G_N_ELEMENTS(itemLabels); i++){
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(highpassCombobox), itemLabels[i]);
  }
  gtk_combo_box_set_active(GTK_COMBO_BOX(highpassCombobox), 0);
  gtk_grid_attach(GTK_GRID(mainGrid), highpassCombobox, 3, 10, 3, 1);
}

void random_sample_for_training_setting(){

  GtkWidget *randomSampleLabel = gtk_label_new("% Random Sample for Training: ");
  gtk_grid_attach(GTK_GRID(mainGrid), randomSampleLabel, 0, 7, 4, 1);

  randomSampleTextview = gtk_text_view_new();
  gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(randomSampleTextview)), "100", -1); 
    gtk_grid_attach(GTK_GRID(mainGrid), randomSampleTextview, 4, 7, 2, 1);
}

void resp_window_text_box_setting(){

  GtkWidget *respWindowLabel = gtk_label_new("Resp. Window [begin end] (ms): ");
  gtk_grid_attach(GTK_GRID(mainGrid), respWindowLabel, 0, 6, 4, 1);

  respWindowTextview = gtk_text_view_new();
  gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(respWindowTextview)), "0 800", -1); 
    gtk_grid_attach(GTK_GRID(mainGrid), respWindowTextview, 4, 6, 2, 1);
}

void regression_method_combo_box_setting(){

  GtkWidget *regressionMethodLabel = gtk_label_new("Regression Method: ");
  gtk_grid_attach(GTK_GRID(mainGrid), regressionMethodLabel, 0, 5, 3, 1);

  regressionCombobox = gtk_combo_box_text_new();
  char *itemLabels[] = {"SWLDA(SW)", "Least Squares(LS)", "Logistic(LG)"};
  for (int i=0; i<G_N_ELEMENTS(itemLabels); i++){
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(regressionCombobox), itemLabels[i]);
  }
  gtk_combo_box_set_active(GTK_COMBO_BOX(regressionCombobox), 0);
  gtk_grid_attach(GTK_GRID(mainGrid), regressionCombobox, 3, 5, 3, 1);
}

void widget_destroyer(GtkWidget *target){
  if (target == NULL) {
    return;
  }else{
    gtk_widget_destroy(target);
    return;
  }
}

void number_of_sequences_setting(char** num){
  widget_destroyer(gtk_grid_get_child_at(GTK_GRID(mainGrid), 0, 4));
  char** label = concatenate_two_strings("# Sequences: ", num);
  GtkWidget *indicator = gtk_label_new(label); 
  gtk_grid_attach(GTK_GRID(mainGrid), indicator, 0, 4, 6, 1);
}

void number_of_channels_setting(char** num){
  widget_destroyer(gtk_grid_get_child_at(GTK_GRID(mainGrid), 0, 3));
  char** label = concatenate_two_strings("# Channels: ", num);
  GtkWidget *indicator = gtk_label_new(label); 
  gtk_grid_attach(GTK_GRID(mainGrid), indicator, 0, 3, 6, 1);
}

void no_training_data_label_setting(int *flag){
  widget_destroyer(gtk_grid_get_child_at(GTK_GRID(mainGrid), 0, 1));
  if(flag == 1){
    noTrainingDataLabel = gtk_label_new("No Training Data Selected");
    gtk_grid_attach(GTK_GRID(mainGrid), noTrainingDataLabel, 0, 1, 6, 1);
  }else{
    noTrainingDataLabel = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(mainGrid), noTrainingDataLabel, 0, 1, 6, 1);
  }
}

int concatenate_two_strings(char** item1, char* item2){

  char* label = malloc(strlen(item1) + strlen(item2) + 1);
  strcpy(label, item1);
  strcat(label, item2);
  return label;

}

void sampling_rate_label_setting(char** num){
  widget_destroyer(gtk_grid_get_child_at(GTK_GRID(mainGrid), 0, 2));
  char* label = concatenate_two_strings("Sampling Rate: ", num);
  GtkWidget *indicator = gtk_label_new(label); 
  gtk_grid_attach(GTK_GRID(mainGrid), indicator, 0, 2, 6, 1);
}
