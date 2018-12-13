#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define dtambah 1
#define dkurang 2
#define dkali 3
#define dbagi 4

GtkWidget *slabel=NULL;
double hasil=0;
int ubah=0;
int operasiku=0;
char tanda[10];

static char tombol[16][5]={"AC", "C", "<=", "+", "1", "2", "3", "-", "4", "5", "6", ":", "7", "8", "9", "x"};
GtkWidget *win=NULL;

static void dialog_tentang( gchar *s){
GtkWidget *dialog = NULL;
  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Dibuat oleh Gerimisya Stela Rida");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

int tambah_angka(char *angka){
char s[50]="";
int pj=0;
    if(gtk_label_get_text(GTK_LABEL(slabel))){
        strcpy(s, gtk_label_get_text(GTK_LABEL(slabel)));
        pj=strlen(s)<10;
        if(pj>0 && pj<10){
            if((s[0]=='0' && s[1]!=',') || ubah!=0)s[0]=0;
            strcat(s, angka);
            ubah=0;
            gtk_label_set_label(GTK_LABEL(slabel), s);
        }
    }
    return 0;
}

int tombol_keyboard(GtkWidget *wid, GdkEventKey *evt, gpointer user_data){
char s[50];
    if(evt->keyval>='0' && evt->keyval<='9'){
        sprintf(s, "%d", evt->keyval-'0');
        tambah_angka(s);
    }
    return 0;
}

int hilangkan_nol(char *s){
int pos;
    pos=strlen(s);
    while(pos>2){
        pos--;
        if(s[pos]=='0')s[pos]=0;
    };

    pos=strlen(s)-1;
    if(s[pos]==tanda[0]){
        s[pos]=0;
    }

    return 0;
}

int hitung(GtkWidget *wid, int operasi){
char tmp[50]="0";
int n;
    if(gtk_label_get_text(GTK_LABEL(slabel)) && ubah==0){
        switch(operasi){
            case dtambah:
                hasil+=atof(gtk_label_get_text(GTK_LABEL(slabel)));
                break;
            case dkurang:
                hasil-=atof(gtk_label_get_text(GTK_LABEL(slabel)));
                break;
            case dbagi:
                n=atof(gtk_label_get_text(GTK_LABEL(slabel)));
                if(n!=0){
                    hasil/=n;
                }else{
                    hasil=0;
                }
                break;
            case dkali:
                hasil*=atof(gtk_label_get_text(GTK_LABEL(slabel)));
                break;
            default:
                hasil=atof(gtk_label_get_text(GTK_LABEL(slabel)));
        }
        sprintf(tmp, "%.10f", hasil);
        hilangkan_nol(tmp);
        gtk_label_set_text(GTK_LABEL(slabel), tmp);
        ubah=1;
    }
    return 0;
}

static void sama_dengan (GtkWidget *wid, GtkWidget *win){
    hitung(wid, operasiku);
    ubah=1;
    operasiku=0;
}

static void kali (GtkWidget *wid, GtkWidget *win){
    hitung(wid, operasiku);
    operasiku=dkali;
}

static void bagi (GtkWidget *wid, GtkWidget *win){
    hitung(wid, operasiku);
    operasiku=dbagi;
}

static void kurang (GtkWidget *wid, GtkWidget *win){
    hitung(wid, operasiku);
    operasiku=dkurang;
}

static void tambah (GtkWidget *wid, GtkWidget *win){
    hitung(wid, operasiku);
    operasiku=dtambah;
}

static void ganti_tanda (GtkWidget *wid, GtkWidget *win){
char tmp1[100], tmp2[100];
    strcpy(tmp1, gtk_label_get_text(GTK_LABEL(slabel)));
    if(tmp1[0]!='0'){
        if(tmp1[0]!='-'){
            strcpy(tmp2, "-");
            strcat(tmp2, tmp1);
            gtk_label_set_text(GTK_LABEL(slabel), tmp2);
        }else{
            strcpy(tmp2, tmp1+1);
            gtk_label_set_text(GTK_LABEL(slabel), tmp2);
        }
    }
}

static void bersihkan (GtkWidget *wid, GtkWidget *win){
    gtk_label_set_text(GTK_LABEL(slabel), "0");
    hasil=0;
    operasiku=0;
}

static void hapus_semua (GtkWidget *wid, GtkWidget *win){
    gtk_label_set_text(GTK_LABEL(slabel), "0");
}

static void hapus_angka (GtkWidget *wid, GtkWidget *win){
char s[100], tmp[100]="";
int pj=0;
  if(gtk_label_get_text(GTK_LABEL(slabel))){
    strcpy(s, gtk_label_get_label(GTK_LABEL(slabel)));
    pj=strlen(s);
    strcpy(tmp, s);
    if(s[0]!='0'){
        if(pj==1)tmp[0]='0';
        else tmp[pj-1]=0;
    }
    gtk_label_set_text(GTK_LABEL(slabel), tmp);
  }
}

static void isi_angka (GtkWidget *wid, GtkWidget *win){
char s[100]="";
    if(gtk_button_get_label(GTK_LABEL(wid))){
        strcpy(s, gtk_button_get_label(GTK_LABEL(wid)));
        tambah_angka(s);
    }
}

static void isi_koma (GtkWidget *wid, GtkWidget *win){
char s[100], tmp[100]="";
    strcpy(s, gtk_label_get_text(GTK_LABEL(slabel)));
    if(gtk_label_get_label(GTK_LABEL(slabel))){
        strcpy(tmp, s);
        if(s[strlen(s)-1]!=tanda[0]){
            strcat(tmp, tanda);
        }
        gtk_label_set_label(GTK_LABEL(slabel), tmp);
    }
}

int main (int argc, char *argv[]){
    GtkWidget *button = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;
    GtkWidget *menu=NULL;
    GtkWidget *menu_bar=NULL;
    GtkWidget *menu_item=NULL;
    GtkWidget *root_menu=NULL;
    char buf[128]="Dibuat oleh Gerimisya Stela Rida";
    char *s=NULL;
    int i;

    /* Initialize GTK+ */
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init (&argc, &argv);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    /* Create the main window */
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 2);
    gtk_window_set_title (GTK_WINDOW (win), "Kalkulator");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);

    menu_bar=gtk_menu_bar_new();

    root_menu = gtk_menu_item_new_with_label ("Bantuan");
    gtk_widget_show (root_menu);
    menu=gtk_menu_new();
    menu_item = gtk_menu_item_new_with_label ("Tentang");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
    gtk_menu_item_set_submenu(root_menu, menu);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
    gtk_widget_show (menu_bar);

    g_signal_connect_swapped (menu_item, "activate", G_CALLBACK (dialog_tentang), (gpointer) g_strdup (buf));

    /* Create a vertical box with buttons */
    vbox = gtk_vbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    gtk_box_pack_start (GTK_BOX (vbox), menu_bar, FALSE, FALSE, 2);
    gtk_widget_show (menu_bar);

    hbox = gtk_hbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER(vbox), hbox);
    slabel = gtk_label_new("0");
    gtk_box_pack_start (GTK_BOX (hbox), slabel, TRUE, TRUE, 0);

    //atas
    for(i=0;i<16;i++){
        if((i%4) == 0){
            hbox = gtk_hbox_new (TRUE, 6);
            gtk_container_add (GTK_CONTAINER(vbox), hbox);
        }

        s=tombol[i];
        button = gtk_button_new_with_label(s);
        switch(s[0]){
            case 'A' :
                g_signal_connect (button, "clicked", G_CALLBACK (bersihkan), NULL);
                break;
            case 'C' :
                g_signal_connect (button, "clicked", G_CALLBACK (hapus_semua), NULL);
                break;
            case '<' :
                g_signal_connect (button, "clicked", G_CALLBACK (hapus_angka), NULL);
                break;
            case '+' :
                g_signal_connect (button, "clicked", G_CALLBACK (tambah), NULL);
                break;
            case '-' :
                g_signal_connect (button, "clicked", G_CALLBACK (kurang), NULL);
                break;
            case 'x' :
                g_signal_connect (button, "clicked", G_CALLBACK (kali), NULL);
                break;
            case ':' :
                g_signal_connect (button, "clicked", G_CALLBACK (bagi), NULL);
                break;
            default :
                g_signal_connect (button, "clicked", G_CALLBACK (isi_angka), NULL);
        }
        gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);
    }

    //bawah
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER(vbox), hbox);

    button = gtk_button_new_with_label("+/-");
    g_signal_connect (button, "clicked", G_CALLBACK (ganti_tanda), NULL);
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);

    sprintf(tanda, "%.1f", 0.1);
    tanda[0]=tanda[1];
    tanda[1]=0;
    button = gtk_button_new_with_label(tanda);
    g_signal_connect (button, "clicked", G_CALLBACK (isi_koma), NULL);
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);

    button = gtk_button_new_with_label("0");
    g_signal_connect (button, "clicked", G_CALLBACK (isi_angka), NULL);
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);

    button = gtk_button_new_with_label("=");
    g_signal_connect (button, "clicked", G_CALLBACK (sama_dengan), NULL);
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);

    g_signal_connect (G_OBJECT(win), "key_press_event", G_CALLBACK (tombol_keyboard), NULL);

    /* Enter the main loop */
    gtk_widget_set_usize(vbox, 240, 240);
    gtk_widget_show_all (win);
    gtk_main ();
    return 0;
}
