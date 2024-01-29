#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <vector>

/*

*/

std::string gameExecutable = "game.jar";

int running = 1;

GtkWidget *window;
GtkWidget *box;
GtkWidget *header_box;

GtkWidget *welcome_content_box;
GtkWidget *start_content_box;
GtkWidget *load_content_box;
GtkWidget *settings_content_box;

GtkWidget *buttonStart;
GtkWidget *buttonLoad;


void startGame() {
	/*pid_t pid = fork();
	if(pid==0) {
		char *args[5]={"/usr/bin/java", "-jar", "game.jar", "-PstartMode=NEWGAME", "-PgraphicsBackend=AWT"};
		printf("PATH2: %s\n", args[1]);
		execv("/usr/bin/java",
			  "/usr/bin/java",
			  "-jar",
			  "game.jar",
			  "-PstartMode=NEWGAME",
			  "-PgraphicsBackend=AWT",
			  NULL);
		//execv("/usr/bin/java", args, NULL);

		//gtk_close_window(window);
		//gtk_widget_hide(window);

		exit(127);
	} else {
		waitpid(pid, 0, 0);
	}
		gtk_widget_set_visible(window, false);*/

	std::vector<std::string> args = {"-PstartMode=NEWGAME", "-PgraphicsBackend=AWT"};

	std::string command = "java -jar " + gameExecutable;

	for(std::string s : args) {
		command += " " + s;
	}

	system("java -jar game.jar -PstartMode=NEWGAME -PgraphicsBackend=AWT & exit");
	exit(0);
}

void set_start_state() {
	gtk_widget_set_visible(welcome_content_box, false);
	gtk_widget_set_visible(start_content_box, true);
}

void set_settings_state() {
	gtk_widget_set_visible(welcome_content_box, false);
	gtk_widget_set_visible(settings_content_box, true);
}

void show_gui() {
	GtkWidget *header_label = gtk_label_new("Nsuluofuo");
	gtk_label_set_markup(GTK_LABEL(header_label), "<span font_desc=\"serif 40\">Nsuluofuo</span>");
	gtk_label_set_justify(GTK_LABEL(header_label), GTK_JUSTIFY_CENTER);

	GtkWidget *header2_label = gtk_label_new("- Java Edition -");
	gtk_label_set_markup(GTK_LABEL(header2_label), "<span font_desc=\"serif 20\">- Java Edition -</span>");
	gtk_label_set_justify(GTK_LABEL(header2_label), GTK_JUSTIFY_CENTER);

	gtk_box_append(GTK_BOX(header_box), header_label);
	gtk_box_append(GTK_BOX(header_box), header2_label);

	gtk_box_append(GTK_BOX(box), header_box);

	welcome_content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(welcome_content_box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(welcome_content_box, GTK_ALIGN_CENTER);

		gtk_box_append(GTK_BOX(box), welcome_content_box);

	settings_content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(settings_content_box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(settings_content_box, GTK_ALIGN_CENTER);

		gtk_box_append(GTK_BOX(box), settings_content_box);


	start_content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(start_content_box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(start_content_box, GTK_ALIGN_CENTER);

		gtk_box_append(GTK_BOX(box), start_content_box);


	GtkWidget *start_button = gtk_button_new_with_label("Start");
	g_signal_connect(start_button,"clicked", G_CALLBACK(set_start_state), NULL);
	gtk_box_append(GTK_BOX(welcome_content_box), start_button);

	GtkWidget *settings_button = gtk_button_new_with_label("Settings");
	g_signal_connect(settings_button,"clicked", G_CALLBACK(set_settings_state), NULL);
	gtk_box_append(GTK_BOX(welcome_content_box), settings_button);

	GtkWidget *star_button = gtk_button_new_with_label("Start");
	g_signal_connect(star_button,"clicked", G_CALLBACK(startGame), NULL);
	gtk_box_append(GTK_BOX(start_content_box), star_button);

	GtkWidget *setting_button = gtk_button_new_with_label("BACK");
	g_signal_connect(setting_button,"clicked", G_CALLBACK(set_settings_state), NULL);
	gtk_box_append(GTK_BOX(start_content_box), setting_button);
}

static void activate(GtkApplication *app, gpointer user_data) {
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Nsuluofuo Launcher");
	gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
	//gtk_container-set_border_width(GTK_CONTAINER(window), 10);

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

	header_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(header_box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(header_box, GTK_ALIGN_CENTER);


	gtk_window_set_child(GTK_WINDOW(window), box);

	show_gui();


	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.cofezuwo.nsuluofuo.launcher", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}