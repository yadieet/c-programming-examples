#include <gtk/gtk.h>

static GtkWidget *mainframe = NULL;

static void widget_destroy (GtkWidget *widget, gpointer data)
{
    //...
}

static gboolean mf_req_close (GtkWidget *widget, GdkEvent *event, gpointer data )
{
    return FALSE;
}

static void app_startup (GtkApplication* app, gpointer user_data)
{
    mainframe = gtk_application_window_new( app );
    gtk_window_set_title( GTK_WINDOW(mainframe), "C GTK First Application" );
    gtk_window_set_default_size( GTK_WINDOW(mainframe), 640, 480 );
    gtk_window_set_position( GTK_WINDOW(mainframe), GTK_WIN_POS_CENTER );
    g_signal_connect( mainframe, "delete-event", G_CALLBACK(mf_req_close), NULL );
    g_signal_connect( mainframe, "destroy", G_CALLBACK(widget_destroy), NULL );
    gtk_widget_show_all( mainframe );
}

static void app_activate (GtkApplication* app, gpointer user_data)
{
    gtk_window_present( GTK_WINDOW(mainframe) );
}

static void app_shutdown (GtkApplication* app, gpointer user_data)
{
    //...
}


int main (int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new( "org.gtk_first_app", G_APPLICATION_FLAGS_NONE );
    g_signal_connect( app, "startup" , G_CALLBACK(app_startup) , NULL );
    g_signal_connect( app, "activate", G_CALLBACK(app_activate), NULL );
    g_signal_connect( app, "shutdown", G_CALLBACK(app_shutdown), NULL );

    int status = g_application_run( G_APPLICATION(app), argc, argv );
    g_object_unref( app );

    return status;
}
